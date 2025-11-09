#!/bin/bash
set -e

KEYBOARD="${1:-boardsource/lulu/rp2040}"
KEYMAP="${2:-dario}"
OUTPUT_DIR="docs/keymaps"
CONFIG="${HOME}/.config/keymap-drawer/config.yaml"
KEYMAP_BIN="${HOME}/Library/Python/3.10/bin/keymap"

mkdir -p "$OUTPUT_DIR"

echo "Generating keymap diagram for $KEYBOARD:$KEYMAP..."

# Convert keymap to JSON, parse, and generate SVG
qmk c2json -kb "$KEYBOARD" -km "$KEYMAP" --no-cpp | \
  "$KEYMAP_BIN" parse -c "$CONFIG" | \
  "$KEYMAP_BIN" draw -c "$CONFIG" - > "$OUTPUT_DIR/${KEYBOARD//\//_}_${KEYMAP}.svg"

echo "✓ Generated: $OUTPUT_DIR/${KEYBOARD//\//_}_${KEYMAP}.svg"
