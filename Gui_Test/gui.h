#ifndef __GUI_H
#define __GUI_H


void drawFastHLine(uint8_t x0, uint8_t y0, uint8_t dlen, lv_color_t color);
void drawFastVLine(uint8_t x0, uint8_t y0, uint8_t dlen, lv_color_t color);
void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, lv_color_t color);
void setupGui();
#endif /*__GUI_H */
