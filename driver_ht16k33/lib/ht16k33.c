#include "ht16k33.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/* General use I2C buffers */
#define I2C_BUFSIZE 256
char sendBuf[I2C_BUFSIZE];
char recvBuf[I2C_BUFSIZE];

/* General use I2C functions */
int i2c_set_slave_address(int fd, uint8_t addr) {
  int ret = ioctl(fd, I2C_SLAVE, addr);
  if (ret < 0) {
    return ret;
  }
  return 0;
}

int i2c_write_bytes(int fd, uint8_t dev_addr, uint8_t reg_addr, uint8_t length,
                    uint8_t *data) {
  int ret = i2c_set_slave_address(fd, dev_addr);
  if (ret < 0) {
    return ret;
  }

  sendBuf[0] = reg_addr;

  for (size_t i = 0; i < length; i++) {
    sendBuf[i + 1] = data[i];
  }

  // +1 length for register byte
  if ((ret = write(fd, sendBuf, 1 + length)) < 0) {
    return ret;
  }

  return 0;
}

/* HT16K33 device info */
struct ht16k33_chip {
  uint8_t address;
  int fd;
  const char *device_filename;
};

/* HT16K33 functions */
struct ht16k33_chip *ht16k33_open(uint8_t addr, const char *device_file) {

  int file;

  // open device driver file
  file = open(device_file, O_RDWR);
  if (file < 0) {
    return NULL;
  }

  // allocate and init struct fields
  struct ht16k33_chip *chip = malloc(sizeof(struct ht16k33_chip));
  chip->fd = file;
  chip->address = addr;
  chip->device_filename = malloc(strlen(device_file) + 2);
  strcpy((char *)chip->device_filename, device_file);

  // turn on oscillator
  i2c_write_bytes(chip->fd, chip->address, 0x21, 0, NULL);

	ht16k33_set_blink_rate(chip, BLINK_OFF);

  return chip;
}

int ht16k33_close(struct ht16k33_chip *chip) {

  int ret = close(chip->fd);
  if (ret < 0) {
    return ret;
  }

  free((void *)chip->device_filename);
  free(chip);
  return 0;
}

void ht16k33_set_blink_rate(struct ht16k33_chip *chip,
                            enum ht16k33_blink_mode blink_mode) {
  i2c_write_bytes(chip->fd, chip->address, (0x80 | 0x01 | (blink_mode << 1)), 0,
                  NULL);
}

void ht16k33_set_brightness(struct ht16k33_chip *chip, uint8_t brightness) {
  i2c_write_bytes(chip->fd, chip->address, (0xE0 | brightness), 0, NULL);
}

/* 8x8 Matrix device info */
#define DISPLAY_SIZE 8 * 8
struct ht16k33_matrix {
  struct ht16k33_chip *chip;
  bool display_buffer[DISPLAY_SIZE];
};

/* 8x8 Matrix functions */
struct ht16k33_matrix *get_matrix(struct ht16k33_chip *chip) {
  struct ht16k33_matrix *matrix = malloc(sizeof(struct ht16k33_matrix));
  matrix->chip = chip;
  memset(matrix->display_buffer, 0, sizeof(bool) * DISPLAY_SIZE);

  return matrix;
}

void release_matrix(struct ht16k33_matrix *matrix) { free(matrix); }

void matrix_display(struct ht16k33_matrix *matrix) {
  // Por algún motivo solo se setean los valores pares (?)
  static uint8_t chip_buffer[16] = {0};

  for (size_t row = 0; row < 8; row++) {
    chip_buffer[2 * row] = 0;
    chip_buffer[2 * row + 1] = 0;

    for (size_t col = 0; col < 8; col++) {
      if (matrix->display_buffer[row * 8 + col]) {
        chip_buffer[2 * row] |= (1 << col);
      }
    }
  }

  i2c_write_bytes(matrix->chip->fd, matrix->chip->address, 0x00, 16,
                  chip_buffer);
}

void matrix_clear(struct ht16k33_matrix *matrix) {
  memset(matrix->display_buffer, 0, sizeof(bool) * DISPLAY_SIZE);
}

void matrix_write_pixel(struct ht16k33_matrix *matrix, uint8_t x, uint8_t y,
                        bool set_on) {

  if ((x > 7) || (y > 7)) {
    return;
  }

  // wrap around the x
  x += 7;
  x %= 8;

  matrix->display_buffer[y * 8 + x] = set_on;
}
