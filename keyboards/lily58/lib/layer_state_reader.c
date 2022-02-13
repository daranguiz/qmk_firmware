
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_BUTTON (1 << 1)
#define L_MEDIA (1 << 2)
#define L_NAV (1 << 3)
#define L_MOUSE (1 << 4)
#define L_SYM (1 << 5)
#define L_NUM (1 << 6)
#define L_FUN (1 << 7)
#define L_GAME (1 << 8)

char layer_state_str[24];

const char *read_layer_state(void) {
//   switch (layer_state)
//   {
//   case L_BASE:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
//     break;
//   case L_BUTTON:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Button");
//     break;
//   case L_MEDIA:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Media");
//     break;
//   case L_NAV:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Navigation");
//     break;
//   case L_MOUSE:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Mouse");
//     break;
//   case L_SYM:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbol");
//     break;
//   case L_NUM:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Number");
//     break;
//   case L_FUN:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Function");
//     break;
//   case L_GAME:
//     snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Gaming");
//     break;
//   default:
//     break;
//   }

  switch (layer_state)
  {
  case L_BASE:
    return "Layer: Default";
    break;
  case L_BUTTON:
    return "Layer: Button";
    break;
  case L_MEDIA:
    return "Layer: Media";
    break;
  case L_NAV:
    return "Layer: Navigation";
    break;
  case L_MOUSE:
    return "Layer: Mouse";
    break;
  case L_SYM:
    return "Layer: Symbol";
    break;
  case L_NUM:
    return "Layer: Number";
    break;
  case L_FUN:
    return "Layer: Function";
    break;
  case L_GAME:
    return "Layer: Gaming";
    break;
  default:
    break;
  }

  return NULL;
}
