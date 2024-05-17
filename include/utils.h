#pragma once

#include <avr/io.h>
#include <stdlib.h>
#include "uartconfig.h"
#include "tests_logger.h"

uint8_t randik[] = {
  15, 4, 16, 25, 21, 1, 24, 5, 7, 6, 22, 14, 28, 
  20, 0, 3, 26, 8, 18, 2, 23, 11, 13, 17, 10, 12, 27, 29, 19, 9
};

void give_test_log_on_uart() {
	uint8_t amount_tests = logger_get_nums_of_test();

    if(amount_tests != 0) {

      for(uint8_t t = 1; t <= amount_tests; t++) {
        test_question current_test[LEN_TEST];
        logger_give_saved_test(t, current_test);

		char jjjj[10];
		itoa(t, jjjj, 10);

        uart_send_str_blocking("TEST ");
        uart_send_str_blocking(jjjj);
        uart_send_str_blocking(": ");
        uart_send_blocking(LN);

        for (uint8_t q = 0; q < LEN_TEST; q++) {
		  char lll[10];
		  itoa(current_test[q].number_question, lll, 10);

          uart_send_str_blocking("question ");
          uart_send_str_blocking(lll);
          uart_send_str_blocking(": ");
          uart_send_blocking(
            current_test[q].is_right ? 'Y' : 'N'
          );
		  uart_send_blocking(LN);
        }

      }

    }
    else {
      uart_send_str_blocking("no saved tests!");
      uart_send_blocking(LN);
    }
}
