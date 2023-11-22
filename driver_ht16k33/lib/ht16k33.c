#include "ht16k33.h"

#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// TODO: Eventualmente borrar este macro
#define UNUSED(x) (void)x;

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

int i2c_write_bytes(int fd, uint8_t dev_addr, uint8_t reg_addr, size_t length,
                    uint8_t *data) {
  int ret = i2c_set_slave_address(fd, dev_addr);
  if (ret < 0) {
    return ret;
  }

  length += 1; // Para tomar en cuenta byte de registro
  sendBuf[0] = reg_addr;
  size_t packet;
  size_t total_packets = (length / (I2C_BUFSIZE - 1)) + 1;

  for (packet = 0; packet < total_packets; packet++) {
    size_t bytes;
    if (packet < total_packets - 1) {
      bytes = I2C_BUFSIZE - 1;
    } else {
      // Último paquete (no es necesario si length % 255 == 0)
      bytes = length % (I2C_BUFSIZE - 1);
      if (bytes == 0) {
        break;
      }
    }

    for (size_t i = 0; i < bytes; i++) {
      sendBuf[i + 1] = data[i + (packet * (I2C_BUFSIZE - 1))];
    }

    if ((ret = write(fd, sendBuf, bytes)) < 0) {
      return ret;
    }
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
  chip->device_filename = malloc(strlen(device_file) + 1);
  strcpy((char *)chip->device_filename, device_file);

  // turn on oscillator
  i2c_write_bytes(chip->fd, chip->address, 0x21, 0, NULL);

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
struct ht16k33_matrix {
  struct ht16k33_chip *chip;
};

/* 8x8 Matrix functions */
struct ht16k33_matrix *get_matrix(struct ht16k33_chip *chip) {
  struct ht16k33_matrix *matrix = malloc(sizeof(struct ht16k33_matrix));
  matrix->chip = chip;

  return matrix;
}

void release_matrix(struct ht16k33_matrix *matrix) { free(matrix); }

void matrix_display(struct ht16k33_matrix matrix) { UNUSED(matrix) }

void matrix_clear(struct ht16k33_matrix matrix) { UNUSED(matrix) }

void matrix_write_pixel(struct ht16k33_matrix matrix, uint8_t x, uint16_t y,
                        bool set_on) {
  UNUSED(matrix)
  UNUSED(x)
  UNUSED(y)
  UNUSED(set_on)
}
