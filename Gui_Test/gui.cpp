#include <TTGO.h>

#define LV_COLOR_WBLUE LV_COLOR_MAKE(0x00, 0x50, 0xA0)
#define LV_COLOR_WBORA LV_COLOR_MAKE(0xF6, 0x92, 0x00)

LV_IMG_DECLARE(gui_hdr);
LV_IMG_DECLARE(gui_close);
LV_IMG_DECLARE(gui_bwd);
LV_IMG_DECLARE(gui_fwd);
LV_FONT_DECLARE(Topaz_16);

static lv_color_t c0;
static lv_color_t c1;
static lv_color_t c2;
static lv_color_t c3;

float sdeg = 0, mdeg = 0, hdeg = 0;
float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
uint16_t osx = 74, osy = 74, omx = 120, omy = 120, ohx = 120, ohy = 120; // Saved H, M, S x & y coords
boolean initial = 1;

void drawFastHLine(lv_obj_t canvas, uint8_t x0, uint8_t y0, uint8_t dlen, lv_color_t color){
  for (int i = 0; i < dlen; i++){
    lv_canvas_set_px(&canvas,x0+i,y0,color);
  }
  
}

void drawFastVLine(lv_obj_t canvas, uint8_t x0, uint8_t y0, uint8_t dlen, lv_color_t color){
  for (int i = 0; i < dlen; i++){
    lv_canvas_set_px(&canvas,x0,y0+i,color);
  }
  
}

void drawLine(lv_obj_t canvas, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, lv_color_t color){
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
  swap_coord(x0, y0);
    swap_coord(x1, y1);
  }

  if (x0 > x1) {
    swap_coord(x0, x1);
    swap_coord(y0, y1);
  }

  int32_t dx = x1 - x0, dy = abs(y1 - y0);;

  int32_t err = dx >> 1, ystep = -1, xs = x0, dlen = 0;

  if (y0 < y1) ystep = 1;
  
  // Split into steep and not steep for FastH/V separation
  if (steep) {
    for (; x0 <= x1; x0++) {
      dlen++;
      err -= dy;
      if (err < 0) {
        err += dx;
        if (dlen == 1) lv_canvas_set_px(&canvas, y0, xs, color);
        else drawFastVLine(canvas, y0, xs, dlen, color);
        dlen = 0;
        y0 += ystep; xs = x0 + 1;
      }
    }
    if (dlen) drawFastVLine(canvas, y0, xs, dlen, color);
  }
  else
  {
    for (; x0 <= x1; x0++) {
      dlen++;
      err -= dy;
      if (err < 0) {
        err += dx;
        if (dlen == 1) lv_canvas_set_px(&canvas, xs, y0, color);
        else drawFastHLine(canvas, xs, y0, dlen, color);
        dlen = 0;
        y0 += ystep; xs = x0 + 1;
      }
    }
    if (dlen) drawFastHLine(canvas, xs, y0, dlen, color);
  }
  
}

void drawClock(lv_obj_t canvas, uint8_t ss){
  uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
  //uint8_t ss = 42;
  uint8_t hh = 20, mm = 5;

  // Seconds first - start by undrawing old seconds line
  drawLine(canvas, osx, osy, 75,75, c1);
  sdeg = ss * 6;                // 0-59 -> 0-354
  mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
  hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds
  hx = cos((hdeg - 90) * 0.0174532925);
  hy = sin((hdeg - 90) * 0.0174532925);
  mx = cos((mdeg - 90) * 0.0174532925);
  my = sin((mdeg - 90) * 0.0174532925);
  sx = cos((sdeg - 90) * 0.0174532925);
  sy = sin((sdeg - 90) * 0.0174532925);

  if (ss == 0 || initial) {
      initial = 0;
      // Erase hour and minute hand positions every minute
      drawLine(canvas, ohx, ohy, 120, 121, c1);
      ohx = hx * 37 + 75;
      ohy = hy * 37 + 75;
      drawLine(canvas, omx, omy, 120, 121, c1);
      omx = mx * 59 + 75;
      omy = my * 59 + 75;
  }
  drawLine(canvas, osx, osy, 120, 121, c1);
  osx = sx * 65 + 75;
  osy = sy * 65 + 75;
  // draw new seconds line
  drawLine(canvas, osx, osy, 75, 75, c3);
  drawLine(canvas, ohx, ohy, 75, 75, c2);
  drawLine(canvas, omx, omy, 75, 75, c2);
}

void setupGui(){
    // Base style and screen setup
    static lv_style_t base_style;
    lv_style_copy(&base_style, &lv_style_scr);
    base_style.body.main_color = LV_COLOR_WBLUE;
    base_style.body.grad_color = LV_COLOR_WBLUE;  
    base_style.text.color = LV_COLOR_WHITE;
    base_style.text.font = &Topaz_16;

    lv_obj_t * scr = lv_scr_act();
    lv_obj_set_style(scr, &base_style);

    // Window style
    static lv_style_t win_style;
    lv_style_copy(&win_style, &base_style);
    win_style.body.main_color = LV_COLOR_WBLUE;
    win_style.body.grad_color = LV_COLOR_WBLUE;
    win_style.body.border.color = LV_COLOR_WHITE;
    win_style.body.border.width = 2;
    win_style.body.border.opa = LV_OPA_100;
    win_style.body.border.part = LV_BORDER_FULL;
    win_style.body.padding.left = 4;
    win_style.body.padding.right = 4;
    win_style.body.padding.top = 4;
    win_style.body.padding.bottom = 4;
    win_style.text.color = LV_COLOR_WHITE;
    win_style.text.font = &Topaz_16;
  
    // Header style
    static lv_style_t hdr_style;
    lv_style_copy(&hdr_style, &lv_style_plain);
    hdr_style.body.main_color = LV_COLOR_WHITE;
    hdr_style.body.grad_color = LV_COLOR_WHITE;
    hdr_style.body.border.opa = LV_OPA_0;
    //hdr_style.body.padding.left = 4;
    hdr_style.body.padding.top = 0;
    hdr_style.body.padding.bottom = 2;
    hdr_style.text.font  = &Topaz_16;
    hdr_style.text.color = LV_COLOR_WBLUE;
    hdr_style.image.color = LV_COLOR_WBLUE;

    //pressed button style
    static lv_style_t style_pr;
    lv_style_copy(&style_pr, &hdr_style);
    style_pr.image.color = LV_COLOR_BLACK;
    style_pr.image.intense = LV_OPA_50;
    style_pr.text.color = lv_color_hex3(0xaaa);
  
    // Header control object
    lv_obj_t * w_hdr;
    w_hdr = lv_obj_create(scr, NULL);
    lv_obj_set_size(w_hdr, 240, 23);
    lv_obj_set_style(w_hdr, &hdr_style);
    lv_obj_align(w_hdr, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Window separator line
    static lv_point_t line_points[] = { {0, 19}, {240, 19}};
    static lv_style_t style_separator;
    lv_style_copy(&style_separator, &hdr_style);
    style_separator.line.color = LV_COLOR_WBLUE;
    style_separator.line.width = 2;
    lv_obj_t * w_separator;
    w_separator = lv_line_create(w_hdr, NULL);
    lv_line_set_points(w_separator, line_points, 2);     /*Set the points*/
    lv_line_set_style(w_separator, LV_LINE_STYLE_MAIN, &style_separator);
    lv_obj_align(w_separator, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    //Close Button - not needed for root window
    lv_obj_t * h_cl_btn = lv_imgbtn_create(w_hdr, NULL);
    lv_imgbtn_set_src(h_cl_btn, LV_BTN_STATE_REL, &gui_close);
    lv_imgbtn_set_src(h_cl_btn, LV_BTN_STATE_PR, &gui_close);
    lv_imgbtn_set_src(h_cl_btn, LV_BTN_STATE_TGL_REL, &gui_close);
    lv_imgbtn_set_src(h_cl_btn, LV_BTN_STATE_TGL_PR, &gui_close);
    lv_imgbtn_set_style(h_cl_btn, LV_BTN_STATE_PR, &style_pr);
    lv_imgbtn_set_style(h_cl_btn, LV_BTN_STATE_TGL_PR, &style_pr);
    lv_imgbtn_set_toggle(h_cl_btn, true);
    lv_obj_align(h_cl_btn, w_hdr, LV_ALIGN_IN_TOP_LEFT, 4, 0);

    //Create a label on the Close button
    lv_obj_t * h_cl_label = lv_label_create(h_cl_btn, NULL);
    lv_label_set_text(h_cl_label, " ");

    // Screen (window header) title label
    lv_obj_t * w_hdr_title;
    w_hdr_title = lv_label_create(w_hdr, NULL);
    lv_label_set_text(w_hdr_title, "WB Release.");
    lv_obj_align(w_hdr_title, h_cl_btn, LV_ALIGN_IN_TOP_LEFT, 32, 2);

    /*Gui Fwd Button*/
    lv_obj_t * h_fw_btn = lv_imgbtn_create(w_hdr, NULL);
    lv_imgbtn_set_src(h_fw_btn, LV_BTN_STATE_REL, &gui_fwd);
    lv_imgbtn_set_src(h_fw_btn, LV_BTN_STATE_PR, &gui_fwd);
    lv_imgbtn_set_src(h_fw_btn, LV_BTN_STATE_TGL_REL, &gui_fwd);
    lv_imgbtn_set_src(h_fw_btn, LV_BTN_STATE_TGL_PR, &gui_fwd);
    lv_imgbtn_set_style(h_fw_btn, LV_BTN_STATE_PR, &style_pr);        /*Use the darker style in the pressed state*/
    lv_imgbtn_set_style(h_fw_btn, LV_BTN_STATE_TGL_PR, &style_pr);
    lv_imgbtn_set_toggle(h_fw_btn, true);
    lv_obj_align(h_fw_btn, w_hdr, LV_ALIGN_IN_TOP_RIGHT, -4, 0);

    /*Create a label on the Fwd button*/
    lv_obj_t * h_fw_label = lv_label_create(h_fw_btn, NULL);
    lv_label_set_text(h_fw_label, " ");    

    /*Gui Bwd Button*/
    lv_obj_t * h_bw_btn = lv_imgbtn_create(w_hdr, NULL);
    lv_imgbtn_set_src(h_bw_btn, LV_BTN_STATE_REL, &gui_bwd);
    lv_imgbtn_set_src(h_bw_btn, LV_BTN_STATE_PR, &gui_bwd);
    lv_imgbtn_set_src(h_bw_btn, LV_BTN_STATE_TGL_REL, &gui_bwd);
    lv_imgbtn_set_src(h_bw_btn, LV_BTN_STATE_TGL_PR, &gui_bwd);
    lv_imgbtn_set_style(h_bw_btn, LV_BTN_STATE_PR, &style_pr);        /*Use the darker style in the pressed state*/
    lv_imgbtn_set_style(h_bw_btn, LV_BTN_STATE_TGL_PR, &style_pr);
    lv_imgbtn_set_toggle(h_bw_btn, true);
    lv_obj_align(h_bw_btn, w_hdr, LV_ALIGN_IN_TOP_RIGHT, -28, 0);

    /*Create a label on the Bwd button*/
    lv_obj_t * h_bw_label = lv_label_create(h_bw_btn, NULL);
    lv_label_set_text(h_bw_label, " "); 

    // Main Window
    lv_obj_t * win = lv_win_create(scr, NULL);
    lv_obj_set_size(win, 240, 218);
    lv_obj_set_pos(win, 0, 22);
    lv_win_set_style(win,LV_WIN_STYLE_HEADER, &hdr_style);
    lv_win_set_style(win,LV_WIN_STYLE_CONTENT, &win_style);
    lv_win_set_btn_size(win,20);
    lv_win_set_title(win, "Aclock V0.3");                        /*Set the title*/

    lv_obj_t * close_btn = lv_win_add_btn(win, &gui_fwd);           /*Add close button and use built-in close action*/
    lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);
    lv_win_add_btn(win, &gui_bwd);

    //Canvas for drawing clock
    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_2BIT(150, 150)];
    lv_obj_t * canvas = lv_canvas_create(win, NULL);
    lv_canvas_set_buffer(canvas, cbuf, 150, 150, LV_IMG_CF_INDEXED_2BIT);
    lv_canvas_set_palette(canvas,0,LV_COLOR_BLUE);
    lv_canvas_set_palette(canvas,1,LV_COLOR_WHITE);
    lv_canvas_set_palette(canvas,2,LV_COLOR_BLACK);
    lv_canvas_set_palette(canvas,3,LV_COLOR_WBORA);
    c0.full = 0;
    c1.full = 1;
    c2.full = 2;
    c3.full = 3;
    lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_canvas_fill_bg(canvas, c1);
    
    uint32_t x;
    uint32_t y;
    uint8_t ss;
    drawLine(*canvas,20,20,150,150,c2);
    ss = 12;
    drawClock(*canvas, ss);
    for( y = 10; y < 30; y++) {
        for( x = 5; x < 20; x++) {
            lv_canvas_set_px(canvas, x, y, c3);
        }
    }

    //Create filled circle arc
    /*
    static lv_style_t clockface;
    lv_style_copy(&clockface, &lv_style_plain);
    clockface.body.main_color = LV_COLOR_WHITE;
    clockface.body.opa = LV_OPA_TRANSP;
    clockface.line.color = LV_COLOR_BLACK;           //Arc color
    clockface.line.width = 8;                       //Arc width
  
    lv_obj_t * arc = lv_arc_create(win, NULL);
    lv_arc_set_angles(arc, 180, 179);
    lv_obj_set_size(arc, 150, 150);
    lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &clockface);
    lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);*/

    //Create a style for the seconds meter
    static lv_style_t style_smeter;
    lv_style_copy(&style_smeter, &win_style);
    style_smeter.line.width = 1;
    style_smeter.line.color = LV_COLOR_BLACK;
    style_smeter.body.main_color = LV_COLOR_BLACK;         /*Light blue*/
    style_smeter.body.grad_color = LV_COLOR_BLACK;         /*Dark blue*/
    style_smeter.body.padding.left = 4;                           /*Line length*/

    //Create a line meter
    /*lv_obj_t * smeter;
    smeter = lv_lmeter_create(win, NULL);
    lv_lmeter_set_range(smeter, 0, 60);                   //Set the range
    lv_lmeter_set_value(smeter, 60);                       //Set the current value
    lv_lmeter_set_scale(smeter, 360, 60);                  //Set the angle and number of lines
    lv_lmeter_set_style(smeter, LV_LMETER_STYLE_MAIN, &style_smeter);           //Apply the new style
    lv_obj_set_size(smeter, 150, 150);
    lv_obj_align(smeter, NULL, LV_ALIGN_CENTER, 0, 0); */   

    // Text Example
    /*lv_obj_t * txt = lv_label_create(win, NULL);
    lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(txt, 232, 218);
    lv_label_set_text(txt, "This is the content of the window\n\n"
                           "You can add control buttons to\n"
                           "the window header\n\n"
                           "The content area becomes\n"
                           "automatically scrollable is it's \n"
                           "large enough.\n\n"
                           " You can scroll the content\n"
                           "See the scroll bar on the right!");*/
    

    // Bottom separator line
    /*static lv_point_t line_b_points[] = { {0, 180}, {238, 180}};
    static lv_style_t style_b_separator;
    lv_style_copy(&style_b_separator, &style_separator);
    style_b_separator.line.color = LV_COLOR_WHITE;
    lv_obj_t * b_separator;
    b_separator = lv_line_create(win, NULL);
    lv_line_set_points(b_separator, line_b_points, 2);     
    lv_line_set_style(b_separator, LV_LINE_STYLE_MAIN, &style_b_separator);
    lv_obj_align(b_separator, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0); */   

    /* Original Button code
    //button
    lv_obj_t *label;
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_toggle(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");*/

}
