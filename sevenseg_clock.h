#pragma once

#include "esphome/core/color.h"
#include "esphome/components/light/addressable_light.h"
#include <stdint.h>

namespace sevenseg {

using esphome::Color;
using esphome::light::AddressableLight;

/*
Segmente (7-Segment):               ---a---     
index 0 = a (top)                  f       b 
index 1 = b (top right)            |       |       
index 2 = c (bottom right)         |---g---|           
index 3 = d (bottom)               e       c     
index 4 = e (bottom left)          |       |         
index 5 = f (top left)              ---d---        
index 6 = g (middle)                   
*/

/*

      _ 19 _ _ _ 18 _        _ 5 _ _ _ 4 _                          _ 55 _ _ _ 54 _        _ 49 _ _ _ 48 _
     |               |      |               |   _            _    |                |      |               |
    20              17      6               3  |1|          |60| 59               53     50              47
     |               |      |               |   -            -    |                |      |               |
     |               |      |               |          _          |                |      |               |
    21              16      7               2         |0|        58               52     51              46
     |               |      |               |          -          |                |      |               |
     |               |      |               |                     |                |      |               |
      - 22 - - - 23 -        - 8 - - - 9  -                       - 57 - - - 56 -         - 44 - - - 45 -
     |               |      |               |                     |                |      |               |
    24              15     13              10          _         33               37     38              43
     |               |      |               |         |31|        |                |      |               |
     |               |      |               |          -          |                |      |               |
    25              14     12              11                    32               36     39              42
     |               |      |               |   _                 |                |      |               |
     |               |      |               |  |30|               |                |      |               |
      - 26 - - - 27 -        - 28 - - - 29 -    -                  - 34 - - - 35 -        - 40 - - - 41 -
*/

/*
SEG_LEDS[digit_index][segment_index][k]
digit_index: 0..3
segment_index: 0..6 (a..g)
*/
static const uint8_t SEG_LEDS[4][7][2] = {
  { // digit 0
    {19, 18},  // a
    {17, 16},  // b
    {15, 14},  // c
    {26, 27},  // d
    {25, 24},  // e
    {20, 21},  // f
    {22, 23}   // g
  },
  { // digit 1
    {5, 4},    // a
    {3, 2},    // b
    {10, 11},  // c
    {28, 29},  // d
    {13, 12},  // e
    {6, 7},    // f
    {8, 9}     // g
  },
  { // digit 2
    {55, 54},  // a
    {53, 52},  // b
    {37, 36},  // c
    {34, 35},  // d
    {33, 32},  // e
    {59, 58},  // f
    {57, 56}   // g
  },
  { // digit 3
    {49, 48},  // a
    {47, 46},  // b
    {43, 42},  // c
    {40, 41},  // d
    {38, 39},  // e
    {50, 51},  // f
    {44, 45}   // g
  }
};

/* ============================
 *  Digit → Segment (0–9)
 *  same logic for all 4 digits
 * ============================ */
/*
order [a,b,c,d,e,f,g]
*/
static const bool DIGIT_SEG_ENABLED[10][7] = {
  // a     b      c      d      e      f      g
  { true,  true,  true,  true,  true,  true,  false }, // 0
  { false, true,  true,  false, false, false, false }, // 1
  { true,  true,  false, true,  true,  false, true  }, // 2
  { true,  true,  true,  true,  false, false, true  }, // 3
  { false, true,  true,  false, false, true,  true  }, // 4
  { true,  false, true,  true,  false, true,  true  }, // 5
  { true,  false, true,  true,  true,  true,  true  }, // 6
  { true,  true,  true,  false, false, false, false }, // 7
  { true,  true,  true,  true,  true,  true,  true  }, // 8
  { true,  true,  true,  true,  false, true,  true  }  // 9
};

/* ============================
 *  Helperfunctions
 * ============================ */


inline void clear_all(AddressableLight &it) {
  it.all() = Color::BLACK;
}

inline void draw_digit(AddressableLight &it,
                       int digit_index,
                       int value,
                       const Color &color) {
  if (digit_index < 0 || digit_index > 3) return;
  if (value < 0 || value > 9) return;

  const bool *pattern = DIGIT_SEG_ENABLED[value];

  for (int seg = 0; seg < 7; seg++) {
    if (!pattern[seg]) continue;

    const uint8_t *led_list = SEG_LEDS[digit_index][seg];
    for (int k = 0; k < 2; k++) {
      uint8_t led = led_list[k];
      if (led == 255) break;
      it[led] = color;
    }
  }
}


inline void draw_colon(AddressableLight &it, const Color &color) {
  it[0]  = color;
  it[31] = color;
}

// degree in digit 4
inline void draw_degree(AddressableLight &it, const Color &color) {
  const uint8_t leds[] = {
    44,45,46,47,48,49,50,51,255
  };

  for (int i = 0; i < 9; i++) {
    uint8_t idx = leds[i];
    if (idx == 255) break;
    it[idx] = color;
  }
}

}  // namespace sevenseg
