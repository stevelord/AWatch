#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef TOPAZ_16
#define TOPAZ_16 1
#endif

#if TOPAZ_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0x66, 0xff, 0xff, 0x66, 0x66, 0x0, 0x66,

    /* U+22 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+23 "#" */
    0x6c, 0xd9, 0xb3, 0x6f, 0xff, 0xdb, 0x36, 0xff,
    0xfd, 0xb3, 0x66, 0xcd, 0x80,

    /* U+24 "$" */
    0x30, 0xc7, 0xdf, 0xc3, 0x7, 0x9e, 0xc, 0x3f,
    0xbe, 0x30, 0xc0,

    /* U+25 "%" */
    0xc7, 0x8f, 0x36, 0x61, 0x83, 0xc, 0x18, 0x66,
    0xcf, 0x1e, 0x30,

    /* U+26 "&" */
    0x38, 0x71, 0xb3, 0x66, 0x8d, 0x1d, 0xbb, 0xdd,
    0xbb, 0x36, 0x67, 0x6e, 0xc0,

    /* U+27 "'" */
    0x6d, 0xbd, 0x80,

    /* U+28 "(" */
    0x33, 0x66, 0xcc, 0xcc, 0xcc, 0x66, 0x33,

    /* U+29 ")" */
    0xcc, 0x66, 0x33, 0x33, 0x33, 0x66, 0xcc,

    /* U+2A "*" */
    0x66, 0x66, 0x3c, 0x3c, 0xff, 0xff, 0x3c, 0x3c,
    0x66, 0x66,

    /* U+2B "+" */
    0x30, 0xc3, 0xc, 0xff, 0xf3, 0xc, 0x30, 0xc0,

    /* U+2C "," */
    0x6d, 0xbd, 0x80,

    /* U+2D "-" */
    0xff, 0xf0,

    /* U+2E "." */
    0xff,

    /* U+2F "/" */
    0x3, 0x3, 0x6, 0x6, 0xc, 0xc, 0x18, 0x18,
    0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0,

    /* U+30 "0" */
    0x79, 0xec, 0xf3, 0xdf, 0x7f, 0xff, 0xef, 0xbc,
    0xf3, 0x79, 0xe0,

    /* U+31 "1" */
    0x30, 0xc7, 0x1c, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0xff, 0xf0,

    /* U+32 "2" */
    0x79, 0xec, 0xf3, 0xc, 0x33, 0x8e, 0x61, 0x8c,
    0xf3, 0xff, 0xf0,

    /* U+33 "3" */
    0x79, 0xec, 0xf3, 0xc, 0x33, 0x8e, 0xc, 0x3c,
    0xf3, 0x79, 0xe0,

    /* U+34 "4" */
    0x1c, 0x38, 0xf1, 0xe6, 0xcd, 0xb3, 0x66, 0xff,
    0xfc, 0x30, 0x61, 0xe3, 0xc0,

    /* U+35 "5" */
    0xff, 0xfc, 0x30, 0xfb, 0xe0, 0xc3, 0xc, 0x3c,
    0xf3, 0x79, 0xe0,

    /* U+36 "6" */
    0x38, 0xe6, 0x18, 0xc3, 0xf, 0xbe, 0xcf, 0x3c,
    0xf3, 0x79, 0xe0,

    /* U+37 "7" */
    0xff, 0xfc, 0xf3, 0xc, 0x31, 0x86, 0x30, 0xc3,
    0xc, 0x30, 0xc0,

    /* U+38 "8" */
    0x79, 0xec, 0xf3, 0xcf, 0x37, 0x9e, 0xcf, 0x3c,
    0xf3, 0x79, 0xe0,

    /* U+39 "9" */
    0x79, 0xec, 0xf3, 0xcf, 0x37, 0xdf, 0xc, 0x31,
    0x86, 0x71, 0xc0,

    /* U+3A ":" */
    0xff, 0x0, 0xff,

    /* U+3B ";" */
    0x6d, 0xb0, 0x0, 0x6d, 0xbd, 0x80,

    /* U+3C "<" */
    0x18, 0xcc, 0x66, 0x33, 0x18, 0x63, 0xc, 0x61,
    0x8c,

    /* U+3D "=" */
    0xff, 0xf0, 0x0, 0x0, 0xf, 0xff,

    /* U+3E ">" */
    0xc6, 0x18, 0xc3, 0x18, 0x63, 0x31, 0x98, 0xcc,
    0x60,

    /* U+3F "?" */
    0x79, 0xec, 0xf3, 0xc, 0x31, 0x86, 0x30, 0xc0,
    0x0, 0x30, 0xc0,

    /* U+40 "@" */
    0x7c, 0xfb, 0x1e, 0x3d, 0xfb, 0xf7, 0xef, 0xdf,
    0xbf, 0x6, 0x7, 0x8f, 0x0,

    /* U+41 "A" */
    0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x3c, 0x66, 0x66,
    0x7e, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+42 "B" */
    0xfd, 0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x3e, 0x66,
    0xcd, 0x9b, 0x3f, 0xdf, 0x80,

    /* U+43 "C" */
    0x3c, 0x79, 0x9b, 0x3c, 0x18, 0x30, 0x60, 0xc1,
    0x81, 0x9b, 0x33, 0xc7, 0x80,

    /* U+44 "D" */
    0xf9, 0xf1, 0xb3, 0x66, 0x6c, 0xd9, 0xb3, 0x66,
    0xcd, 0xb3, 0x6f, 0x9f, 0x0,

    /* U+45 "E" */
    0xff, 0xfd, 0x9b, 0x36, 0xc, 0x1e, 0x3c, 0x60,
    0xc1, 0x9b, 0x3f, 0xff, 0xc0,

    /* U+46 "F" */
    0xff, 0xfd, 0x9b, 0x36, 0xc, 0x1e, 0x3c, 0x60,
    0xc1, 0x83, 0xf, 0x1e, 0x0,

    /* U+47 "G" */
    0x3c, 0x79, 0x9b, 0x3c, 0x18, 0x33, 0xe7, 0xc7,
    0x8d, 0x9b, 0x33, 0xe7, 0xc0,

    /* U+48 "H" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xff, 0xcf, 0x3c,
    0xf3, 0xcf, 0x30,

    /* U+49 "I" */
    0xff, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0xff, 0xf0,

    /* U+4A "J" */
    0x1c, 0x70, 0xc3, 0xc, 0x30, 0xc3, 0xcf, 0x3c,
    0xf3, 0x79, 0xe0,

    /* U+4B "K" */
    0xe7, 0xcd, 0x9b, 0x36, 0xcd, 0x9e, 0x3c, 0x6c,
    0xd9, 0x9b, 0x3e, 0x7c, 0xc0,

    /* U+4C "L" */
    0xf1, 0xe1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x62,
    0xc5, 0x9b, 0x3f, 0xff, 0xc0,

    /* U+4D "M" */
    0x83, 0x7, 0x1e, 0x3e, 0xfd, 0xff, 0xff, 0xd7,
    0xaf, 0x1e, 0x3c, 0x78, 0xc0,

    /* U+4E "N" */
    0xc7, 0x8f, 0x9f, 0x3f, 0x7e, 0xf7, 0xef, 0xcf,
    0x9f, 0x1e, 0x3c, 0x78, 0xc0,

    /* U+4F "O" */
    0x38, 0x71, 0xb3, 0x6c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8d, 0xb3, 0x63, 0x87, 0x0,

    /* U+50 "P" */
    0xfd, 0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x3e, 0x60,
    0xc1, 0x83, 0xf, 0x1e, 0x0,

    /* U+51 "Q" */
    0x38, 0x71, 0xb3, 0x6c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8d, 0xb3, 0x63, 0xc7, 0x81, 0x83,

    /* U+52 "R" */
    0xfc, 0xfc, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x7c,
    0x6c, 0x6c, 0x66, 0x66, 0xe3, 0xe3,

    /* U+53 "S" */
    0x79, 0xec, 0xf3, 0xe3, 0x87, 0x1c, 0x1c, 0x7c,
    0xf3, 0x79, 0xe0,

    /* U+54 "T" */
    0xff, 0xfb, 0x6d, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0x79, 0xe0,

    /* U+55 "U" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0x7d, 0xf0,

    /* U+56 "V" */
    0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x66, 0x66,
    0x3c, 0x3c, 0x3c, 0x3c, 0x18, 0x18,

    /* U+57 "W" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf5, 0xeb, 0xff,
    0xff, 0xbf, 0x7c, 0x78, 0xc0,

    /* U+58 "X" */
    0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18,
    0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3,

    /* U+59 "Y" */
    0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x3c,
    0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c,

    /* U+5A "Z" */
    0xff, 0xff, 0x1e, 0x38, 0xd1, 0x86, 0xc, 0x32,
    0x65, 0x9b, 0x3f, 0xff, 0xc0,

    /* U+5B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+5C "\\" */
    0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18,
    0xc, 0xc, 0x6, 0x6, 0x3, 0x3,

    /* U+5D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff,

    /* U+5E "^" */
    0x10, 0x20, 0xe1, 0xc6, 0xcd, 0xb1, 0xe3,

    /* U+5F "_" */
    0xff, 0xfc,

    /* U+60 "`" */
    0xdb, 0x66, 0xc0,

    /* U+61 "a" */
    0x78, 0xf0, 0x30, 0x63, 0xc7, 0xb3, 0x66, 0x76,
    0xec,

    /* U+62 "b" */
    0xe1, 0xc1, 0x83, 0x6, 0xcd, 0x9d, 0xbb, 0x66,
    0xcd, 0x9b, 0x33, 0xc7, 0x80,

    /* U+63 "c" */
    0x79, 0xec, 0xf3, 0xc3, 0xc, 0xf3, 0x79, 0xe0,

    /* U+64 "d" */
    0x1c, 0x38, 0x30, 0x66, 0xcd, 0xb7, 0x6e, 0xcd,
    0x9b, 0x36, 0x67, 0x6e, 0xc0,

    /* U+65 "e" */
    0x79, 0xec, 0xf3, 0xff, 0xfc, 0x30, 0x79, 0xe0,

    /* U+66 "f" */
    0x38, 0xe6, 0xdb, 0x61, 0x8f, 0x3c, 0x61, 0x86,
    0x18, 0xf3, 0xc0,

    /* U+67 "g" */
    0x3b, 0x3b, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x3c,
    0xc6, 0xc6, 0x7c, 0x7c,

    /* U+68 "h" */
    0xe1, 0xc1, 0x83, 0x6, 0xcd, 0x9d, 0xbb, 0x66,
    0xcd, 0x9b, 0x3e, 0x7c, 0xc0,

    /* U+69 "i" */
    0x66, 0x0, 0xee, 0x66, 0x66, 0x66, 0xff,

    /* U+6A "j" */
    0xc, 0x30, 0x0, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0xcf, 0x37, 0x9e,

    /* U+6B "k" */
    0xe1, 0xc1, 0x83, 0x6, 0x6c, 0xdb, 0x36, 0x78,
    0xf1, 0xb3, 0x6e, 0x7c, 0xc0,

    /* U+6C "l" */
    0xee, 0x66, 0x66, 0x66, 0x66, 0x66, 0xff,

    /* U+6D "m" */
    0xcd, 0x9b, 0xbf, 0x7d, 0x7a, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+6E "n" */
    0xfb, 0xec, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+6F "o" */
    0x79, 0xec, 0xf3, 0xcf, 0x3c, 0xf3, 0x79, 0xe0,

    /* U+70 "p" */
    0xdd, 0xb9, 0x9b, 0x36, 0x6c, 0xdf, 0x3e, 0x60,
    0xc3, 0xc7, 0x80,

    /* U+71 "q" */
    0x7a, 0xf7, 0x36, 0x6c, 0xd9, 0x9f, 0x3e, 0xc,
    0x18, 0x38, 0x70,

    /* U+72 "r" */
    0xed, 0xd9, 0xdb, 0xb6, 0x6c, 0xd8, 0x30, 0xf1,
    0xe0,

    /* U+73 "s" */
    0x7d, 0xfc, 0x30, 0x79, 0xe0, 0xc3, 0xfb, 0xe0,

    /* U+74 "t" */
    0x21, 0x18, 0xcf, 0xfd, 0x8c, 0x63, 0x1a, 0xd3,
    0x18,

    /* U+75 "u" */
    0xcd, 0x9b, 0x36, 0x6c, 0xd9, 0xb3, 0x66, 0x76,
    0xec,

    /* U+76 "v" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0x9e, 0x30, 0xc0,

    /* U+77 "w" */
    0xc7, 0x8f, 0x5e, 0xbd, 0x7a, 0xdb, 0x36, 0x6c,
    0xd8,

    /* U+78 "x" */
    0xc7, 0x8d, 0xb3, 0x63, 0x87, 0x1b, 0x36, 0xc7,
    0x8c,

    /* U+79 "y" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0x9e, 0x30, 0xce,
    0x38,

    /* U+7A "z" */
    0xff, 0xf9, 0xa6, 0x30, 0xc6, 0x59, 0xff, 0xf0,

    /* U+7B "{" */
    0x1c, 0x73, 0xc, 0x30, 0xce, 0x38, 0x30, 0xc3,
    0xc, 0x1c, 0x70,

    /* U+7C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+7D "}" */
    0xe3, 0x83, 0xc, 0x30, 0xc1, 0xc7, 0x30, 0xc3,
    0xc, 0xe3, 0x80,

    /* U+7E "~" */
    0x72, 0xe6, 0x74, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 8, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 11, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 24, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 35, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 46, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 59, .adv_w = 128, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 62, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 86, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 94, .adv_w = 128, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 128, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 99, .adv_w = 128, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 100, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 114, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 125, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 136, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 147, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 158, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 171, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 182, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 193, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 204, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 215, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 226, .adv_w = 128, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 229, .adv_w = 128, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 128, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 244, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 250, .adv_w = 128, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 259, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 270, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 283, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 297, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 310, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 323, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 336, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 349, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 362, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 375, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 386, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 397, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 408, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 421, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 434, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 447, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 460, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 473, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 486, .adv_w = 128, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 514, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 525, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 536, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 547, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 561, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 574, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 588, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 602, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 615, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 622, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 636, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 643, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 650, .adv_w = 128, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 128, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 655, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 664, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 677, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 685, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 698, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 706, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 717, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 742, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 749, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 774, .adv_w = 128, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 781, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 790, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 798, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 806, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 837, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 845, .adv_w = 128, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 854, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 863, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 871, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 880, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 889, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 906, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 917, .adv_w = 128, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 921, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 932, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 12}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t Topaz_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if TOPAZ_16*/

