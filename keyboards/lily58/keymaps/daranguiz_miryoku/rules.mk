# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku
# generated -*- buffer-read-only: t -*-

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift
SPLIT_KEYBOARD = yes

OLED_ENABLE = yes
WPM_ENABLE = yes
LTO_ENABLE = yes

SRC += daranguiz_miryoku.c # keymap

# SRC +=  /lib/rgb_state_reader.c \
#         ./lib/layer_state_reader.c \
#         ./lib/logo_reader.c \
#         ./lib/keylogger.c \
#         # ./lib/mode_icon_reader.c \
#         # ./lib/host_led_state_reader.c \
#         # ./lib/timelogger.c \

SRC +=  ./lib/layer_state_reader.c \
        ./lib/keylogger.c \
		# ./lib/logo_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

# alternative layouts:

# alphas
ifneq ($(strip $(MIRYOKU_ALPHAS)),)
  OPT_DEFS += -DMIRYOKU_ALPHAS_$(MIRYOKU_ALPHAS)
endif

# nav
ifneq ($(strip $(MIRYOKU_NAV)),)
  OPT_DEFS += -DMIRYOKU_NAV_$(MIRYOKU_NAV)
endif

# clipboard
ifneq ($(strip $(MIRYOKU_CLIPBOARD)),)
  OPT_DEFS += -DMIRYOKU_CLIPBOARD_$(MIRYOKU_CLIPBOARD)
endif

# layers
ifneq ($(strip $(MIRYOKU_LAYERS)),)
  OPT_DEFS += -DMIRYOKU_LAYERS_$(MIRYOKU_LAYERS)
endif

# subset mappings
ifneq ($(strip $(MIRYOKU_MAPPING)),)
  OPT_DEFS += -DMIRYOKU_MAPPING_$(MIRYOKU_MAPPING)
endif
