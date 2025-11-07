# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## QMK Firmware Overview

This is a keyboard firmware based on the TMK keyboard firmware. QMK supports 840+ keyboards including the OLKB product line, ErgoDox EZ, Clueboard, and many community keyboards.

Official documentation: https://docs.qmk.fm

## Build Commands

### Compilation

Compile a specific keyboard and keymap:
```bash
make <keyboard>:<keymap>
# Example: make boardsource/lulu/rp2040:dario
# Example: make planck/rev6:default
```

Or use the QMK CLI (if set up):
```bash
qmk compile -kb <keyboard> -km <keymap>
# Example: qmk compile -kb boardsource/lulu/rp2040 -km dario
```

### Flash Firmware

Flash compiled firmware to keyboard:
```bash
make <keyboard>:<keymap>:flash
# Or: qmk flash -kb <keyboard> -km <keymap>
```

### Clean Build

Remove build artifacts:
```bash
make clean              # Remove .build/ directory
make distclean          # Also remove *.bin, *.hex, *.uf2 files
```

### List Commands

```bash
make list-keyboards                    # List all supported keyboards
make <keyboard>:list-keymaps          # List keymaps for a specific keyboard
```

### Testing

Run unit tests:
```bash
make test:all          # Run all tests
make test:<name>       # Run specific test
```

### Build System Format

The make command follows this pattern:
```
make <keyboard_folder>:<keymap_folder>[:target]
```

Where:
- `keyboard_folder` is the path relative to `keyboards/` (e.g., `planck/rev6`)
- `keymap_folder` is the name of the keymap under that board's `keymaps/` directory
- `target` is optional (e.g., `flash`, `clean`)

## Architecture Overview

### Directory Structure

- **keyboards/** - Hardware definitions organized by manufacturer (840+ keyboards)
  - Each keyboard has: `config.h`, `info.json`, `rules.mk`, `<keyboard>.c`, `keymaps/`
  - Keyboards can be nested up to 5 levels deep for variants (e.g., `planck/rev6`)

- **quantum/** - QMK-specific features and high-level abstractions
  - Core files: `quantum.c`, `action.c`, `keyboard.c`, `action_layer.c`, `action_tapping.c`
  - **process_keycode/** - Feature processors (auto-shift, combos, audio, RGB, etc.)
  - **audio/**, **rgblight/**, **rgb_matrix/** - Visual and audio effects
  - **split_common/** - Split keyboard communication
  - **debounce/** - Matrix debouncing algorithms
  - **keymap_extras/** - International keyboard layouts (113 layouts)

- **tmk_core/** - Core keyboard firmware layer from TMK project
  - Protocol handlers (USB HID, MIDI, etc.)
  - Host communication layer
  - Lower-level than quantum/ layer

- **platforms/** - Platform-specific code
  - `avr/` - Atmega32u4 and other AVR MCUs
  - `chibios/` - ARM microcontrollers (STM32, GD32, RP2040, etc.)
  - `arm_atsam/` - SAMD21 and similar
  - `test/` - Unit test platform

- **drivers/** - Hardware drivers (LED, OLED, haptic, Bluetooth, sensors)

- **builddefs/** - Build system makefiles
  - `build_keyboard.mk` - Main keyboard build orchestrator
  - `common_features.mk` - Feature source file mappings
  - `common_rules.mk` - Compilation rules and linker config
  - `mcu_selection.mk` - MCU-specific configurations (30+ MCU types)
  - `bootloader.mk` - Bootloader selection and flashing

- **lib/** - External libraries (ChibiOS, LUFA, V-USB, Pico SDK)

- **layouts/** - Community-shared keyboard layouts that work across multiple keyboards

### Keyboard Configuration Files

Each keyboard directory contains:

1. **info.json** - Primary keyboard metadata
   - Keyboard name, manufacturer, VID/PID
   - Layout definitions with physical key positions
   - Feature configuration
   - Processed at build time to generate `info_rules.mk`

2. **rules.mk** - Build configuration
   - MCU selection
   - Feature enable/disable flags (AUDIO_ENABLE, BACKLIGHT_ENABLE, RGB_MATRIX_ENABLE, etc.)
   - Platform-specific settings

3. **config.h** - C configuration
   - Hardware-specific defines
   - Pin mappings
   - Timing parameters

4. **[keyboard].c** - Main keyboard implementation code

5. **keymaps/** - User-defined key layouts
   - Each keymap is a subdirectory containing `keymap.c`
   - Optional `rules.mk` for keymap-specific features
   - Common keymaps: `default`, `via`

### Configuration Hierarchy and Merging

The build system merges configuration files hierarchically (later overrides earlier):

1. Parent keyboard folders (shallowest)
2. Vendor folders
3. Keyboard folders
4. Hardware variant folders
5. Keymap folders (deepest - highest priority)

Example for `boardsource/lulu/rp2040:dario`:
```
keyboards/boardsource/rules.mk                          # 1. If exists
keyboards/boardsource/lulu/rules.mk                    # 2. Base keyboard
keyboards/boardsource/lulu/rp2040/rules.mk            # 3. Hardware variant
keyboards/boardsource/lulu/keymaps/dario/rules.mk     # 4. Keymap overrides
```

This allows hardware variants to share common code while overriding specifics.

### Build System Flow

When you run `make planck/rev6:default`:

1. **Makefile** (root) parses `keyboard:keymap:target` syntax
2. **PARSE_RULE** macro identifies keyboard and keymap
3. **build_keyboard.mk** executes:
   - Includes all `rules.mk` files from keyboard folder hierarchy (5 levels)
   - Generates `info_rules.mk` from `info.json` via QMK CLI
   - Locates keymap in hierarchy or falls back to community layouts
   - Includes keymap-level `rules.mk`
4. **mcu_selection.mk** determines MCU and platform (AVR, ChibiOS, etc.)
5. **common_features.mk** adds source files for enabled features
6. **common_rules.mk** compiles C/C++/ASM and links firmware
7. Output: `.build/obj_<keyboard>_<keymap>/<keyboard>_<keymap>.[hex|bin|uf2]`

### Software Architecture Layers

```
User Keymap (keymap.c)
    ↓
QMK Quantum Layer (quantum/)
├─ quantum.c - Initialization
├─ keyboard.c - Matrix scanning, debouncing, main task loop
├─ action.c - Keycode to action conversion
├─ process_keycode/* - Feature processors
│   └─ process_record_quantum() - Central dispatcher
└─ Features (audio, RGB, encoders, etc.)
    ↓
TMK Core Layer (tmk_core/)
├─ protocol/host.c - USB/Bluetooth communication
├─ protocol/report.c - HID report generation
└─ Protocol implementations (USB HID, MIDI, etc.)
    ↓
Platform Layer (platforms/)
├─ avr/ - AVR microcontrollers
├─ chibios/ - ARM microcontrollers
└─ arm_atsam/ - SAMD microcontrollers
    ↓
Hardware (Matrix scanning, GPIO, USB stack)
```

### Data Flow: Keypress to USB

1. Matrix scan detects key press (platform-specific in `matrix.c`)
2. `keyboard_task()` reads matrix and creates `keyrecord_t` struct
3. `process_record()` → `process_record_quantum()` dispatches to feature processors
4. Feature processors execute (audio, RGB, combos, etc.) and can consume keypress
5. `action_exec()` converts keycode to HID action
6. `process_record_user()` allows user customization in keymap
7. `host_keyboard_send()` (tmk_core) sends USB HID report to host computer

### Creating a New Keymap

1. Create directory: `keyboards/<keyboard>/keymaps/<your_name>/`
2. Create `keymap.c` with your layout
3. Optionally create `rules.mk` to enable features
4. Compile: `make <keyboard>:<your_name>`

### Common Feature Flags (rules.mk)

```makefile
AUDIO_ENABLE = yes              # Audio output
BACKLIGHT_ENABLE = yes          # Keyboard backlight
BOOTMAGIC_ENABLE = yes          # Hold keys at boot for options
COMBO_ENABLE = yes              # Key combinations
CONSOLE_ENABLE = yes            # Debug console
ENCODER_ENABLE = yes            # Rotary encoders
EXTRAKEY_ENABLE = yes           # Media keys
MOUSEKEY_ENABLE = yes           # Mouse keys
NKRO_ENABLE = yes               # N-key rollover
OLED_ENABLE = yes               # OLED display
RGB_MATRIX_ENABLE = yes         # RGB matrix lighting
RGBLIGHT_ENABLE = yes           # RGB underglow
SPLIT_KEYBOARD = yes            # Split keyboard support
TAP_DANCE_ENABLE = yes          # Tap dance keys
```

### Debugging

Enable debug console in keymap's `rules.mk`:
```makefile
CONSOLE_ENABLE = yes
```

Then use `hid_listen` to view debug output, or add to `keymap.c`:
```c
#include "print.h"
uprintf("Debug message: %d\n", value);
```

### Important Files for Understanding QMK

Core architecture files:
- [Makefile](Makefile:1-460) - Build entry point and rule parsing
- [builddefs/build_keyboard.mk](builddefs/build_keyboard.mk:1-300) - Keyboard build logic
- [quantum/keyboard.c](quantum/keyboard.c:1-600) - Main task loop
- [quantum/action.c](quantum/action.c:1-800) - Action processing and dispatcher
- [quantum/quantum.h](quantum/quantum.h:1-150) - Main QMK API header
- [paths.mk](paths.mk:1-34) - Path definitions for all components

### Working with Submodules

QMK uses git submodules for external libraries (ChibiOS, LUFA, etc.):

```bash
# Initialize all submodules
make git-submodule

# Update specific library
git submodule update --init lib/chibios
```

The Makefile automatically checks and initializes required submodules during build.

## Active Technologies
- C99 (QMK firmware), Make build system, Git 2.x + QMK build system (make), avr-gcc/arm-none-eabi-gcc (MCU toolchains), gi (001-migrate-chordal-hold)
- Git repository (local branches, remote upstream) (001-migrate-chordal-hold)

## Recent Changes
- 001-migrate-chordal-hold: Added C99 (QMK firmware), Make build system, Git 2.x + QMK build system (make), avr-gcc/arm-none-eabi-gcc (MCU toolchains), gi
