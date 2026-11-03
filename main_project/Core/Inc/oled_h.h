#ifndef oled_h
#define oled_h
#include "main.h"












#define OLEDAddr		0x3c

HAL_StatusTypeDef oled_send_command(uint8_t command);
void oled_setup(void);
void oled_draw(uint8_t x, uint8_t y);
void oled_fill(void);
void oled_erase_all(void);
void oled_display_char(uint8_t *numbers);












#endif
