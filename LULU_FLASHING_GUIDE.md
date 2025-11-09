# Flashing Guide: Boardsource Lulu (RP2040)

## Quick Steps

### 1. Build the Firmware
```bash
make boardsource/lulu/rp2040:dario
```
Output file: `boardsource_lulu_rp2040_dario.uf2`

### 2. Enter Bootloader Mode (DFU)
The Lulu (RP2040) uses USB bootloader mode. There are two ways to enter it:

**Option A: Using Bootmagic (Easiest - No Tools Required)**
- Unplug the keyboard
- **Hold the upper-left physical key** (the key in the top-left corner of the entire keyboard)
- Plug in the USB cable while holding that key
- Release the key after the keyboard is connected
- Your computer should detect a new USB mass storage device named `RPI-RP2`

**Option B: Using DIP Switch (Requires Opening Case)**
- Unplug the keyboard
- Unscrew the case and open it
- Locate the DIP switch on the bottom of the PCB (opposite side from the OLED screen)
- Flip the DIP switch to enter DFU mode
- Plug in the USB cable
- Your computer should detect the `RPI-RP2` drive
- After flashing, remember to flip the DIP switch back

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

## Flashing Both Halves (Usually Not Needed)

**Important**: For keymap changes, you typically **only need to flash one half** (the left/master half that connects to USB). The firmware contains the configuration for both halves.

However, if you need to flash both halves (e.g., after a major firmware update):

1. Flash the left half using the steps above
2. Unplug the TRRS cable connecting the two halves
3. Unplug the left half from USB
4. Enter bootloader mode on the right half (using bootmagic or DIP switch)
5. Drag the **same .uf2 file** onto the `RPI-RP2` drive
6. Reconnect the TRRS cable
7. Plug the left half back into USB

Both halves use the same firmware file. The keyboard automatically detects which half it's running on.

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
