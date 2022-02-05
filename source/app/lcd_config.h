#ifndef __LCD_CONFIG_H
#define __LCD_CONFIG_H

#define MENU_OPTIONS_NUM              (6)
#define LASER_CTRL_OPTIONS_NUM        (3)
#define LASER_CTRL_MODE_SET_NUM       (2)
#define LASER_CTRL_STATE_SET_NUM      (2)


#define COVER_MODE (0)
#define UCOVER_MODE (1)
#define LCD_X1 (0)
#define LCD_Y1 (0)
#define LCD_X2 (280)
#define LCD_Y2 (240)

#define SHOW_WORD_X       (30)
#define SHOW_WORD_Y       (0)
#define SHOW_WORD_SIZE       (16)

#define PRESS_KEY_X    (50)
#define PRESS_KEY_Y    (185)
#define PRESS_KEY_SIZE (24)

#define ASTRONAUT_IMAGE_X1 (235)
#define ASTRONAUT_IMAGE_Y1 (200)
#define ASTRONAUT_IMAGE_X_SIZE (45)
#define ASTRONAUT_IMAGE_Y_SIZE (38)

#define TITLE_SIZE (24)
#define MENU_TITLE_X (116)
#define MENU_TITLE_Y (0)
#define LASER_CTRL_TITLE_X (62)
#define LASER_CTRL_TITLE_Y (0)

#define CURSOR_X  (30)
#define CURSOR_Y  (TITLE_SIZE)
#define CURSOR_SIZE  (16)
#define MAIN_WORD_X (CURSOR_X+CURSOR_SIZE)
#define MAIN_WORD_Y (TITLE_SIZE)
#define MAIN_WORD_SIZE (16)

#define BELONG_WORD_X (115)
#define BELONG_WORD_Y (TITLE_SIZE)
#define BELONG_WORD_SIZE (MAIN_WORD_SIZE)

#define SET_RECTANGLE_X1  (180)
#define SET_RECTANGLE_Y1  (TITLE_SIZE+6)
#define SET_RECTANGLE_X2  (275)
#define SET_RECTANGLE_Y2  (180)

#define SET_LINE_X1  (SET_RECTANGLE_X1)
#define SET_LINE_Y1  (SET_RECTANGLE_Y1+30)
#define SET_LINE_X2  (SET_RECTANGLE_X2)
#define SET_LINE_Y2  (SET_RECTANGLE_Y1+30)

#define SET_CURSOR_X  (SET_RECTANGLE_X1+5)
#define SET_CURSOR_Y  (SET_LINE_Y1+5)
#define SET_CURSOR_SIZE  (16)
#define SET_WORD_X (SET_CURSOR_X+SET_CURSOR_SIZE)
#define SET_WORD_Y (SET_CURSOR_Y)
#define SET_WORD_SIZE (16)

#endif 
