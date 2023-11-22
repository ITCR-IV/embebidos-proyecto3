#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct arguments {
  bool specified_port;
  uint16_t port;
  FILE *conf_file;
};

struct configuration {
  uint16_t port;
  const char *log_path;
};

struct arguments parse_args(int argc, char **argv);
struct configuration parse_conf(struct arguments args);

#endif
