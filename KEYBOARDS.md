# Personal Keyboards Inventory

## Active Keyboards

### Boardsource Lulu (RP2040)
- **Path**: keyboards/boardsource/lulu/keymaps/dario/
- **Hardware**: RP2040 variant
- **Keys**: 58 keys (split 3x6+4 layout)
- **Build**: `make boardsource/lulu/rp2040:dario` or `./build_lulu.sh`
- **Status**: Active
- **Features**: OLED, split keyboard, NKRO, chordal hold
- **Last Updated**: 2025-11-07

### Lily58
- **Path**: keyboards/lily58/keymaps/daranguiz_miryoku/
- **Hardware**: Standard lily58
- **Keys**: 58 keys (split 3x6+4 layout)
- **Build**: `make lily58:daranguiz_miryoku`
- **Status**: Active (migrated from lily58/miryoku-bilateral-combinations branch)
- **Features**: OLED, WPM display, split keyboard, miryoku layout, chordal hold
- **Last Updated**: 2025-11-07

### Bastard Keyboards Skeletyl
- **Path**: keyboards/bastardkb/skeletyl/keymaps/daranguiz_miryoku/
- **Hardware**: Skeletyl (36-key) with Pro Micro
- **Keys**: 36 keys (split 3x5+3 layout)
- **Build**: `make bastardkb/skeletyl/promicro:daranguiz_miryoku`
- **Status**: Active (migrated from lily58 branch)
- **Features**: Split keyboard, miryoku layout, chordal hold
- **Last Updated**: 2025-11-07

---

## Configuration Notes

All keyboards use:
- **Chordal Hold**: Native QMK feature for opposite-hands tap-hold behavior
- **Permissive Hold**: Required companion setting for chordal hold
- **Miryoku Layout**: 36-key base layout (extended on 58-key boards)
- **Home Row Mods**: GACS (GUI/ALT/CTL/SFT) on home row

Combos and caps_word are temporarily disabled pending QMK 0.30.x compatibility fixes.

---

**Last Inventory Update**: 2025-11-07
