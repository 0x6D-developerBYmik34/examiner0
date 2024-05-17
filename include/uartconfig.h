#pragma once

#include <string.h>
#include <avr/io.h>

#define BAUDRATE 4800
// #define BD_DIVIDER (((F_CPU) / (16 * (BAUDRATE))) - 1)
#define LN (0x0D)

void uart_init() {
  // set freq (for baud=9600 and freq=4Mgz)
  UBRRH = 0;
  UBRRL = 0x33;

  UCSRA = 0;
  
  // in out, no interrupts
  UCSRB = (1 << RXEN) | (1 << TXEN) | (0 << RXCIE) | (0 << TXCIE) | (0 << UDRIE);

  // 8-битовая посылка, 1 стоп бита
  UCSRC = (1 << URSEL) | (0 << USBS) | (1 << UCSZ0) | (1 << UCSZ1);
}

void uart_send_blocking(char data) {
  while(!(UCSRA & (1 << UDRE))); // ждем готовности - флага UDRE
  UDR = data;
}

char uart_recv_blocking() {
  while(!(UCSRA & (1 << RXC))); // Ждем флага прихода байта
  char data = UDR;
  return data;
}

void uart_send_str_blocking(char * data) {
  for (uint8_t i = 0; i < strlen(data); i++) {
    uart_send_blocking(data[i]);
  }
}
