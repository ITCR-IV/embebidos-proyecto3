#include "ht16k33.h"

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int ret;

  struct ht16k33_chip *chip =
      ht16k33_open(HT16K33_DEFAULT_I2C_ADDR, "/dev/i2c-1");

  if (chip == NULL) {
    err(errno, "Error opening i2c-1 device\n");
  }

  ht16k33_set_brightness(chip, 15);

  struct ht16k33_matrix *matrix = get_matrix(chip);

  printf("Turn all lights on\n");
  for (size_t x = 0; x < 8; x++) {
    for (size_t y = 0; y < 8; y++) {
      matrix_write_pixel(matrix, x, y, 1);
      matrix_display(matrix);
      // Durar 2s en total
      usleep(2000000 / 8 * 8);
    }
  }

  usleep(200000); // 0.2s
  printf("Variar brillo\n");
  for (uint8_t brightness = 0; brightness < 16; brightness++) {
    ht16k33_set_brightness(chip, 15 - brightness);
    usleep(1500000 / 8 * 8); // 1.5s en total
  }

  for (uint8_t brightness = 0; brightness < 16; brightness++) {
    ht16k33_set_brightness(chip, brightness);
    usleep(1500000 / 8 * 8); // 1.5s en total
  }

  usleep(200000); // 0.2s
  printf("Blinking\n");
  ht16k33_set_blink_rate(chip, BLINK_1HZ);
  usleep(4000000); // 4s
  ht16k33_set_blink_rate(chip, BLINK_2HZ);
  usleep(3000000); // 3s

  ht16k33_set_blink_rate(chip, BLINK_OFF);
  usleep(1000000); // 1s

  printf("Clear\n");
  matrix_clear(matrix);
  matrix_display(matrix);

  // clang-format off
	bool check_img[8*8] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
  // clang-format on

  usleep(1000000); // 1.0s
  printf("Mostrar check\n");
  for (size_t x = 0; x < 8; x++) {
    for (size_t y = 0; y < 8; y++) {
      matrix_write_pixel(matrix, x, y, check_img[y * 8 + x]);
    }
  }
  matrix_display(matrix);

  release_matrix(matrix);
  ret = ht16k33_close(chip);
  if (ret) {
    err(errno, "Error closing i2c-1 device\n");
  }

  return 0;
}
