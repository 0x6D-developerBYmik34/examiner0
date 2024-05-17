#define F_CPU 4000000

#define BUTYES PA0
#define BUTNO PA1

#define CHAR_FOR_GIVE_LOGS 'l'

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "lcd_lib_2.h"
#include "random16.h"
#include "questions.h"
#include "uartconfig.h"
#include "tests_logger.h"
#include "utils.h"

typedef enum {
  WAIT_START,
  RUNNING,
  WAIT_ANSWER
} type_state_examinator;

typedef struct {
  type_state_examinator state_examinator;
  uint8_t answer_counter;
  test_question current_test[LEN_TEST];
  uint8_t curent_num_q;
} system_state_type;

void startDispInit() {
  // dispaly methods
  LCD_Clear();
  LCD_SendStr("Nachat test?");
}

void drawEndsTest() {
  LCD_Clear();
  LCD_SendStr("!TEST ZAVERSHYON!");
  _delay_ms(1800);
}

void drawLoading() {
  // dispaly methods
  LCD_Clear();
  LCD_SendStr("......");
}

uint8_t printNextQuestion(r16_seed_carrier * sc) {
  uint8_t num_q = r16_get_with_max(sc, MAX_QUESTIONS - 1);

  char buf_list[strlen_P(mystrs[num_q]) + 1];
  strcpy_P(buf_list, mystrs[num_q]); 

  // dispaly methods
  LCD_Clear();
  LCD_SendStr(buf_list);
  
  return num_q;
}

void acceptAnswer(system_state_type * sys_s, uint8_t is_right) {
  drawLoading();
  _delay_ms(250); // for debounce

  test_question qq = {sys_s->curent_num_q, is_right};
  sys_s->current_test[sys_s->answer_counter] = qq;
          
  uart_send_str_blocking("clicked answer");
  uart_send_blocking(LN);
        
  sys_s->answer_counter++;
  sys_s->state_examinator = RUNNING;
}

int main() {
  // buttons input pullup init
  DDRA &= ~((1 << BUTYES) | (1 << BUTNO));
  PORTA |= (1 << BUTYES) | (1 << BUTNO);
  
  // init uart and test
  uart_init();
  
  // dispaly methods
  LCD_Init();
  LCD_Clear();
  LCD_SendStr("Starting...");

  // init test eeprom logger 
  logger_init();

  // recv logs on request
  uart_send_str_blocking("what do you see saved tests(press l)?");
  uart_send_blocking(LN);
  if(uart_recv_blocking() == CHAR_FOR_GIVE_LOGS) {
    give_test_log_on_uart();
  }

  // random init
  r16_seed_carrier cur_seed_c;
  r16_setSeed(&cur_seed_c, INIT_KEY * logger_get_nums_of_test());

  // init system state
  system_state_type system_state = {
    .state_examinator = WAIT_START,
    .answer_counter = 0,
    .curent_num_q = 0
  };

  startDispInit();
  uart_send_str_blocking("start examinator");
  uart_send_blocking(LN);
  
  for (;;)
  {
    switch (system_state.state_examinator)
    {
      case WAIT_START:
        if (!(PINA & (1 << BUTYES)))
        {
          drawLoading();
          _delay_ms(250);

          uart_send_str_blocking("start test");
          uart_send_blocking(LN);

          system_state.state_examinator = RUNNING;
        }
        break;
      case RUNNING:
        if (system_state.answer_counter == LEN_TEST) {
          logger_save_crrnt_test(system_state.current_test);

          uart_send_str_blocking("test saved and end");
          uart_send_blocking(LN);

          drawEndsTest();

          system_state.answer_counter = 0;
          system_state.state_examinator = WAIT_START;

          startDispInit();
        } 
        else {
          system_state.curent_num_q = printNextQuestion(&cur_seed_c);
          system_state.state_examinator = WAIT_ANSWER;

          uart_send_str_blocking("print question");
          uart_send_blocking(LN);
        }
        break;
      case WAIT_ANSWER: 
        {
          uint8_t is_right;
          uint8_t is_press = 0;

          if (!(PINA & (1 << BUTYES))) {
            is_right = 1; 
            is_press = 1;
          }
          else if (!(PINA & (1 << BUTNO))) {
            is_right = 0;
            is_press = 1;
          }

          if (is_press) acceptAnswer(&system_state, is_right);
        }
        break;
    }
  }

}
