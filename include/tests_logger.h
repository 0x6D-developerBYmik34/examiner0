#pragma once

#include <avr/eeprom.h>

#define INIT_KEY 47
#define LEN_TEST 10

#define INIT_ADDR (uint8_t *)0  
#define NUMS_OF_TESTS_ADDR (uint8_t *)1
#define OFFSET_FOT_TEST_ADDR 2


typedef struct {
  uint8_t number_question;
  uint8_t is_right;
} test_question; //sizeof = 2 bytes


void logger_init() {
  if(eeprom_read_byte(INIT_ADDR) != INIT_KEY) {
    eeprom_write_byte(INIT_ADDR, INIT_KEY);

    eeprom_write_byte(NUMS_OF_TESTS_ADDR, 0);
  }
}

void logger_save_crrnt_test(test_question * crrnt_test) {
  uint8_t crr_num_tests = eeprom_read_byte(NUMS_OF_TESTS_ADDR);
  eeprom_write_byte(NUMS_OF_TESTS_ADDR, crr_num_tests + 1);

  uint8_t start_addr_new_note_test = crr_num_tests * LEN_TEST * sizeof(test_question);

  // sizeof 2*10 = 20 b
  eeprom_write_block(
    (void*)crrnt_test, 
    (void*)(start_addr_new_note_test + OFFSET_FOT_TEST_ADDR), 
    (LEN_TEST * sizeof(test_question))
  );
}

uint8_t logger_get_nums_of_test() {
  return eeprom_read_byte(NUMS_OF_TESTS_ADDR);
}

void logger_give_saved_test(uint8_t number_test, test_question * crrnt_test) {
  uint8_t start_addr_new_note_test = (number_test - 1) * LEN_TEST * sizeof(test_question);

  eeprom_read_block( 
    (void*)crrnt_test,
    (void*)(start_addr_new_note_test + OFFSET_FOT_TEST_ADDR),
    (LEN_TEST * sizeof(test_question))
  );
}

