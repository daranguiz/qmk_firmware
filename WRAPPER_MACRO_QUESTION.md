# QMK Keymap Wrapper Macro Design Question

## Context

I'm refactoring my QMK keymaps to use a shared base layout across multiple keyboards with different physical layouts:

- **Skeletyl**: 36 keys (3x5+3 split layout) - native `LAYOUT_split_3x5_3` support
- **Lulu**: 58 keys (includes number row, outer columns, encoder positions)
- **Lily58**: 58 keys (similar to Lulu)

## Goal

Create a single source of truth for the core 3x5+3 layout (36 keys) that can be:
1. Used directly on 36-key keyboards (Skeletyl)
2. Wrapped/extended on larger keyboards (Lulu, Lily58)
3. Optionally enhanced with extra keys on a **per-layer basis** on larger keyboards

## Current Keymap Structure

Here's an example layer from my current keymaps (confirmed identical across Lulu and Skeletyl):

```c
[NAV] = LAYOUT_split_3x5_3(
  U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  U_UND,   U_CUT,   U_CPY,   U_PST,   U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
  U_NA,    U_NA,    U_NA,    KC_DEL,  KC_ENT,  KC_BSPC
),
```

This is 36 keycodes arranged as:
- 10 keys per hand on rows 1-3 (30 keys)
- 3 thumb keys per hand (6 keys)
- Total: 36 keys

## Planned Architecture

### Shared Layer Definitions (`users/dario/layers.h`)

```c
#define LAYER_NAV \
    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, \
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
    U_UND,   U_CUT,   U_CPY,   U_PST,   U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END, \
    U_NA,    U_NA,    U_NA,    KC_DEL,  KC_ENT,  KC_BSPC

// ... LAYER_BASE, LAYER_NUM, LAYER_SYM, etc.
```

### Skeletyl Keymap (36-key native - easy case)

```c
#include "dario.h"
#include "layers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NAV] = LAYOUT_split_3x5_3(LAYER_NAV),
    // Works perfectly - no wrapper needed
};
```

### Lulu Keymap (58-key - needs wrapper)

Lulu's physical layout:

```
┌───┬───┬───┬───┬───┬───┐     ┌───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │     │   │   │   │   │   │   │  <- Row 0 (number row)
├───┼───┼───┼───┼───┼───┤     ├───┼───┼───┼───┼───┼───┤
│   │ 0 │ 1 │ 2 │ 3 │ 4 │     │ 5 │ 6 │ 7 │ 8 │ 9 │   │  <- Row 1 (core 5 + outer)
├───┼───┼───┼───┼───┼───┤     ├───┼───┼───┼───┼───┼───┤
│   │10 │11 │12 │13 │14 │     │15 │16 │17 │18 │19 │   │  <- Row 2 (core 5 + outer)
├───┼───┼───┼───┼───┼───┼───┐ ┌───┼───┼───┼───┼───┼───┼───┤
│   │20 │21 │22 │23 │24 │   │ │   │25 │26 │27 │28 │29 │   │  <- Row 3 (core 5 + outer + encoder)
└───┴───┴───┼───┼───┼───┤   │ │   ├───┼───┼───┼───┴───┴───┘
            │   │32 │33 │34 │ │35 │36 │37 │   │              <- Row 4 (core 3 + extra)
            └───┴───┴───┴───┘ └───┴───┴───┴───┘
```

Core 36-key positions shown as numbers (0-37, skipping 30-31).

## The Problem

I need a clean C preprocessor macro system that allows me to:

1. **Use the shared layer on Lulu** with most extra keys as `KC_NO`
2. **Selectively add real keycodes to extra positions on specific layers**

For example:
- **NAV layer**: All extras are `KC_NO` (use standard wrapper)
- **NUM layer**: Number row (top row) has actual numbers `KC_1`, `KC_2`, etc., but other extras are still `KC_NO`
- **Future GAMING layer**: Number row + outer columns + all extras populated

## The Question

**What's the cleanest way to define wrapper macros that allow per-layer customization of extra keys?**

### Requirements

1. Core 36 keys always come from `users/dario/layers.h` (single source of truth)
2. Easy to use the "default" case (all extras as `KC_NO`)
3. Easy to override extras on specific layers
4. Maintainable - not too many layers of macro indirection
5. Compatible with QMK's build system (standard C preprocessor, no external tools)

## Three Proposed Approaches

### Approach 1: Layer-Specific Wrappers

Define different wrapper macros for different use cases:

```c
// keyboards/boardsource/lulu/keymaps/dario/keymap_config.h

#define XXX KC_NO

// Standard wrapper: all extras are KC_NO
#define LAYOUT_split_3x5_3( /* 36 params */ ) \
LAYOUT( \
    XXX, XXX, XXX, XXX, XXX, XXX,    XXX, XXX, XXX, XXX, XXX, XXX, \
    XXX, K00, K01, K02, K03, K04,    K05, K06, K07, K08, K09, XXX, \
    /* ... core 36 keys mapped, extras as XXX ... */ \
)

// Gaming/number row wrapper: adds number row
#define LAYOUT_split_3x5_3_WITH_NUMROW( /* 36 params */ ) \
LAYOUT( \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, \
    KC_TAB, K00, K01, K02, K03, K04,    K05, K06, K07, K08, K09, KC_BSLS, \
    /* ... */ \
)
```

Usage:
```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NAV]    = LAYOUT_split_3x5_3(LAYER_NAV),
    [NUM]    = LAYOUT_split_3x5_3(LAYER_NUM),
    [GAMING] = LAYOUT_split_3x5_3_WITH_NUMROW(LAYER_GAMING),
};
```

**Pros**: Self-documenting, clean separation per use case
**Cons**: Need multiple wrapper definitions

---

### Approach 2: Parameterized Wrapper with Extras

Single wrapper that accepts both core keys and extra keys as parameters:

```c
#define LAYOUT_split_3x5_3_EXT( \
    /* Core 36 keys */ \
    K00, K01, /* ... */, K37, \
    /* Extra keys: top row (12), outer cols (4), encoder (2), bottom (2) */ \
    T00, T01, T02, T03, T04, T05,    T06, T07, T08, T09, T10, T11, \
    OL0, OL1, OL2, OR0, OR1, OR2, \
    E00, E01, \
    B00, B01 \
) \
LAYOUT( /* map all params to physical layout */ )

// Convenience: default all extras to XXX
#define LAYOUT_split_3x5_3(CORE) \
    LAYOUT_split_3x5_3_EXT(CORE, XXX, XXX, /* ... 20 XXXs ... */)
```

Usage:
```c
[NAV] = LAYOUT_split_3x5_3(LAYER_NAV),

[NUM] = LAYOUT_split_3x5_3_EXT(
    LAYER_NUM,
    // Number row extras:
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,    KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
    // Other extras: still XXX
    XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX,
    XXX, XXX
),
```

**Pros**: Single wrapper definition, per-layer control
**Cons**: Verbose when using extras, easy to miscount parameters

---

### Approach 3: Separate Local Layer Definitions

Keep shared layers pure, define full Lulu-specific layers locally for layers with extras:

```c
// users/dario/layers.h - only 36-key layers
#define LAYER_NAV /* 36 keys */

// keyboards/boardsource/lulu/keymaps/dario/layers_lulu.h
#define LAYER_NUM_LULU /* all 58 keys including extras */
```

Usage:
```c
[NAV] = LAYOUT_split_3x5_3(LAYER_NAV),      // Shared
[NUM] = LAYOUT(LAYER_NUM_LULU),             // Lulu-specific
```

**Pros**: Most explicit, no complex macros
**Cons**: Violates DRY, must update Lulu layer if core changes

---

## Additional Context

- I have 8 layers total: BASE, NAV, MOUSE, MEDIA, NUM, SYM, FUN, BUTTON
- Most layers will use the standard wrapper (no extras)
- Only 1-2 layers (like NUM or future GAMING) need extras
- This is C preprocessor only - QMK build system doesn't support external code generation

## What I'm Looking For

- Which approach would you recommend and why?
- Are there other approaches I haven't considered?
- Are there gotchas with C preprocessor macro expansion I should watch out for?
- How do other QMK users solve this problem?

Any guidance or alternative approaches would be greatly appreciated!
