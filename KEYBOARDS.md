# Personal Keyboard Inventory

This document tracks all keyboards configured in this QMK fork with personal keymaps.

## Active Keyboards

### Boardsource Lulu (RP2040)

**Keyboard**: Boardsource Lulu
**Hardware Variant**: RP2040
**Key Count**: 58 keys (split keyboard with extra columns)
**Keymap Path**: `keyboards/boardsource/lulu/keymaps/dario/`
**Build Command**: `make boardsource/lulu/rp2040:dario` or `./build_lulu.sh`
**Status**: ✅ Active
**Notes**:
- Primary 58-key split keyboard
- Includes core 36-key layout plus additional outer columns
- Planned: Gaming layer for QWERTY support
- RGB underglow and per-key RGB support

---

## Configuration Notes

### Core Layout

All keyboards share the same core 36-key layout (3x5 matrix + 3 thumb keys per hand):
- Base layer: Colemak-DH with home row mods
- Layers: NAV, MOUSE, MEDIA, NUM, SYM, FUN, BUTTON
- Home row mods: GUI/A, ALT/R, CTL/S, SFT/T pattern

### Adding a New Keyboard

When adding a new keyboard to this inventory:

1. Create keymap directory: `keyboards/<manufacturer>/<model>/keymaps/dario/`
2. Implement core 36-key layout matching existing keyboards
3. Add entry to this document with all required fields
4. Create build script (optional): `build_<keyboard>.sh`
5. Add visual layer documentation in keymap directory
6. Commit all changes together

### Build Scripts

Quick build scripts in repository root:
- `build_lulu.sh` - Build Lulu RP2040 variant

## Maintenance Log

| Date | Keyboard | Action | Notes |
|------|----------|--------|-------|
| 2025-11-07 | Lulu RP2040 | Added to inventory | Initial KEYBOARDS.md creation |
