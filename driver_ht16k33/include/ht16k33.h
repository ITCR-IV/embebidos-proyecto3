#ifndef IV_JZ_LED_MATRIX_DRIVER_HT16K33
#define IV_JZ_LED_MATRIX_DRIVER_HT16K33

// API inspirado por
// https://github.com/Seeed-Studio/Grove_LED_Matrix_Driver_HT16K33

#include <stdint.h>
#define HT16K33_DEFAULT_I2C_ADDR 0x70
// 8*48 means this buffer can store 48 pictures, if you
// need more space, please make sure MAX_BIG_BUFFER_SIZE
// is a multiple of 8.
#define MAX_BIG_BUFFER_SIZE (8 * 20)

enum orientation_type_t {
  DISPLAY_ROTATE_0 = 0,
  DISPLAY_ROTATE_90,
  DISPLAY_ROTATE_180,
  DISPLAY_ROTATE_270,
};

enum action_type_t {
  ACTION_SCROLLING = 0,
  ACTION_SHIFT,
};

enum blink_type_t {
  BLINK_OFF = 0,
  BLINK_2HZ,
  BLINK_1HZ,
};

void ht16k33_init(uint8_t addr);

// Same as calling ht16k33_init with HT16K33_DEFAULT_I2C_ADDR
void ht16k33_init_default();

/*************************************************************
    Description
     Setting the blink rate of matrix
    Parameter
     blink_type: BLINK_OFF, BLINK_2HZ, BLINK_1HZ
    Return
     Null.
*************************************************************/
void ht16k33_set_blink_rate(blink_type_t blink_type);

/*************************************************************
    Description
     Setting the brightness of matrix
    Parameter
     brightness: 0-15
    Return
     Null.
*************************************************************/
void ht16k33_set_brightness(uint8_t brightness);

/*************************************************************
    Description
     Setting the display offset of x-axis and y-axis.
     This function will activate after call display().
    Parameter
     x: The display offset value of horizontal x-axis, range from -8 to 8.
     y: The display offset value of horizontal y-axis, range from -8 to 8.
    Return
     Null.
*************************************************************/
void matrix_set_display_offset(int8_t x, int8_t y);

/*************************************************************
    Description
     Setting the display orientation.
     This function will activate after call writeXXX().
    Parameter
     orientation: DISPLAY_ROTATE_0, DISPLAY_ROTATE_90, DISPLAY_ROTATE_180,
    DISPLAY_ROTATE_270, which means the display will rotate 0°, 90°,180° or
270°. Return Null.
*************************************************************/
void matrix_set_display_orientation(uint8_t orientation);

/*************************************************************
    Description
     Display the pixels stored in display buffer on 8x8 matrix.
     This function should be called after writeXXX(). And this
     function will block until all the data is shown. For example,
     if I call writeString("hello", 1000, ACTION_SCROLLING) and
     display(), then the program will block for 5 seconds(5*1000ms)
     before it goes to the next sentense.
    Parameter
     Null.
    Return
     Null.
*************************************************************/
void matrix_display();

/*************************************************************
    Description
     Clear the display buffer.
     This function will display nothing on 8x8 Matrix after call display().
    Parameter
     Null.
    Return
     Null.
*************************************************************/
void matrix_clear();

/*************************************************************
    Description
     Set a pixel ON(default) or OFF in display buffer.
     Call display() to show display buffer.
    Parameter
     x: the x-axis position of the pixel
     y: the y-axis position of the pixel
     set_on: Set the pixel ON(default) or OFF.
    Return
     Null.
*************************************************************/
void matrix_write_pixel(uint8_t x, uint16_t y, bool set_on = true);

// -------- DE AQUÍ EN ADELANTE NO VOY A IMPLEMENTAR --------
//
// /*************************************************************
//     Description
//      Write a bar in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      bar: 0 - 32. 0 is blank and 32 is full.
//     Return
//      Null.
// *************************************************************/
// void matrix_write_bar(uint8_t bar);
//
// /*************************************************************
//     Description
//      Write an icon in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      num: 0 - 28.
//      0  full screen   1  arrow_up       2  arrow_down      3  arrow_right
//      4  arrow_left    5  triangle_up    6  triangle_down   7  triangle_right
//      8  triangel_left 9  smile_face_1   10 smile_face_2    11 hearts
//      12 diamonds      13 clubs          14 spades          15 circle1
//      16 circle2       17 circle3        18 circle4         19 man
//      20 woman         21 musical_note_1 22 musical_note_2  23 snow
//      24 up_down       25 double_!       26 left_right      27 house
//      28 glasses
//     Return
//      Null.
// *************************************************************/
// void matrix_write_icon(uint8_t num);
//
// /*************************************************************
//     Description
//      Write a number(from -2147483648 to 2147483647) in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      number: Set the number you want to display on LED matrix. Number(except
// 0-9) will scroll horizontally, the shorter you set the ms_per_digit, the
// faster it scrolls. The number range from -2147483648 to 2147483647, if you
// want to display larger number, please use writeString(). ms_per_digit: Set
// the display time(ms) of per digit. Return Null.
// *************************************************************/
// void matrix_write_number(int32_t number, uint16_t ms_per_digit);
//
// /*************************************************************
//     Description
//      Write a String in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      s: A string. The string size should be less than
//      (MAX_BIG_BUFFER_SIZE/8),
//         the excess part will be ignored.
//      ms_per_letter: Set the display time(ms) of per letter.
//      mode:  ACTION_SCROLLING: If the size of string is more than 1, scroll
//      the
// string on the matrix; ACTION_SHIFT: If the size of string is more than 1,
// display the letter 1 by 1 on the matrix; Return Null.
// *************************************************************/
// void matrix_write_string(const char *s, uint16_t ms_per_letter,
//                          action_type_t mode);
//
// /*************************************************************
//     Description
//      Write a picture in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      pic: A pointer of a uint8_t picture array.
//     Return
//      Null.
// *************************************************************/
// void matrix_write_one_picture(const uint8_t *pic);
//
// /*************************************************************
//     Description
//      Write a picture in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      pic: A uint64_t type 8x8 matrix picture, you can make it at
//           https://xantorohara.github.io/led-matrix-editor/#
//     Return
//      Null.
// *************************************************************/
// void matrix_write_one_picture_64(const uint64_t pic);
//
// /*************************************************************
//     Description
//      Write many pictures in display buffer.
//      Call display() to show display buffer.
//     Parameter
//      pic: A pointer
//      pic_number: The number of pictures, should be less than
// (MAX_BIG_BUFFER_SIZE/8), the excess part will be ignored. ms_per_pic: Set the
// display time(ms) of per picture. mode:  ACTION_SCROLLING: Scroll the pictures
// on the matrix; ACTION_SHIFT: Display the pictures 1 by 1 on the matrix;
//
//     Return
//      Null.
// *************************************************************/
// void matrix_write_pictures(const uint8_t *pic, uint8_t pic_number,
//                            uint16_t ms_per_pic, action_type_t mode);
// void matrix_write_pictures_64(const uint64_t *pic, uint8_t pic_number,
//                               uint16_t ms_per_pic, action_type_t mode);

#endif //IV_JZ_LED_MATRIX_DRIVER_HT16K33
