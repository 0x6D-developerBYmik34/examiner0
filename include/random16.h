#pragma once

#include <avr/io.h>

typedef struct {
  uint16_t _seed;
} r16_seed_carrier;

void r16_setSeed(r16_seed_carrier * curr_carrier, uint16_t seed) {
    curr_carrier->_seed = seed;
}

uint16_t r16_get(r16_seed_carrier * curr_carrier) {
    curr_carrier->_seed = (curr_carrier->_seed * 2053ul) + 13849;
    return curr_carrier->_seed;
}

uint16_t r16_get_with_max(r16_seed_carrier * curr_carrier, uint16_t max) {
    return ((uint32_t)max * r16_get(curr_carrier)) >> 16;
}

uint16_t r16_get_with_constr(r16_seed_carrier * curr_carrier, uint16_t min, uint16_t max) {
    return (r16_get_with_max(curr_carrier, max - min) + min);
}
