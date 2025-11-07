BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
OLED_ENABLE = yes
SPLIT_KEYBOARD = yes
NKRO_ENABLE = yes           # Enable N-Key Rollover

COMBO_ENABLE = no  # TODO: Re-enable after fixing introspection errors
LTO_ENABLE = yes

SRC += ./mods.c
# TODO: Re-enable caps_word after build is working
# SRC += ./features/caps_word.c
