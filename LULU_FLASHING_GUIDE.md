# Flashing Guide: Boardsource Lulu (RP2040)

## Quick Steps

### 1. Build the Firmware
```bash
make boardsource/lulu/rp2040:dario
```
Output file: `boardsource_lulu_rp2040_dario.uf2`

### 2. Enter Bootloader Mode
The Lulu (RP2040) uses USB bootloader mode. To enter it:

**Option A: Using Bootmagic (Recommended)**
- Unplug the keyboard
- Hold down the BOOTSEL button (on the main PCB, usually near the USB connector)
- Plug in the USB cable while holding BOOTSEL
- Release BOOTSEL after the keyboard is connected
- Your computer should detect a new USB mass storage device named `RPI-RP2`

**Option B: Using QMK Command (if already flashed)**
- If your keyboard is already running QMK firmware, you can press the reset key defined in your keymap
- Or use: `qmk flash -kb boardsource/lulu/rp2040 -km dario` (this will prompt you to enter bootloader mode)

### 3. Copy Firmware to Keyboard
Once you see the `RPI-RP2` mass storage device:

**Option A: Drag & Drop (Easiest)**
- Open Finder (or file manager)
- Locate the `RPI-RP2` drive
- Drag `boardsource_lulu_rp2040_dario.uf2` onto the drive
- The file will copy, then the keyboard will automatically reboot and disconnect

**Option B: Command Line**
```bash
# Mount point varies by system, typically:
cp boardsource_lulu_rp2040_dario.uf2 /Volumes/RPI-RP2/
# Keyboard will reboot automatically
```

### 4. Verify
The keyboard should disconnect and reconnect automatically. You're done!

## Troubleshooting

**Keyboard not entering bootloader mode:**
- Make sure you're holding BOOTSEL before plugging in
- Try different USB cables
- Check if BOOTSEL button is soldered correctly (if DIY)

**`RPI-RP2` drive not appearing:**
- Try a different USB port
- Try a different USB cable
- Wait 2-3 seconds after plugging in

**Firmware won't copy:**
- Try dragging again
- On Mac: Eject the drive first with Cmd+E, then try again
- Check file size: `boardsource_lulu_rp2040_dario.uf2` should be ~86KB

**Keyboard not responding after flashing:**
- Unplug and plug back in
- If still not working, re-enter bootloader and reflash
- Check that keymap compiled without errors

## One-Command Flash

After initial setup, you can build and flash in one go:
```bash
make boardsource/lulu/rp2040:dario:flash
```
This will prompt you to enter bootloader mode when ready.

## Build Script
You can also use the included build script:
```bash
./build_lulu.sh
```
