# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku
# generated -*- buffer-read-only: t -*-

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift
SPLIT_KEYBOARD = yes

COMBO_ENABLE = no  # TODO: Re-enable after fixing introspection errors
LTO_ENABLE = yes

SRC += ./mods.c
# TODO: Re-enable caps_word after build is working
# SRC += ./features/caps_word.c

# MCU name (Elite-C uses ATmega32U4)
MCU = atmega32u4

# Bootloader selection (Elite-C uses atmel-dfu)
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes

AUDIO_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
RGBLIGHT_SUPPORTED = no

LAYOUTS = split_3x5_3

