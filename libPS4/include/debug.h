#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include "libc.h"
#include "network.h"
#include "types.h"

extern int DEBUG_SOCK;

#define printf_socket(...)                                                      \
  if (DEBUG_SOCK >= 0) {                                                        \
    do {                                                                        \
      char sock_message[512] = {0};                                             \
      int size = snprintf_s(sock_message, sizeof(sock_message), ##__VA_ARGS__); \
      SckSend(DEBUG_SOCK, sock_message, size);                                  \
    } while (0);                                                                \
  }

#endif
