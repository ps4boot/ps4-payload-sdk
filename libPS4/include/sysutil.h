#pragma once

#ifndef SYSUTIL_H
#define SYSUTIL_H

#include "debug.h"
#include "libc.h"
#include "network.h"
#include "types.h"

#define SCE_USER_SERVICE_MAX_LOGIN_USERS 4
#define SCE_USER_SERVICE_MAX_USER_NAME_LENGTH 16

extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char *message);

typedef struct SceUserServiceLoginUserIdList {
  int32_t userId[SCE_USER_SERVICE_MAX_LOGIN_USERS];
} SceUserServiceLoginUserIdList;

void initSysUtil(void);
void openBrowser(char *uri);
int getUserIDList(SceUserServiceLoginUserIdList *userIdList);
int32_t getUserID();
char *getUserName(int32_t userId);
int32_t getInitialUser();
void reboot();
void shutdown();

#define printf_notification(...)                                   \
  do {                                                             \
    char noti_message[512] = {0};                                  \
    snprintf_s(noti_message, sizeof(noti_message), ##__VA_ARGS__); \
    sceSysUtilSendSystemNotificationWithText(0xDE, noti_message);  \
    if (DEBUG_SOCK >= 0) {                                         \
      printf_socket("%s", noti_message);                           \
      printf_socket("\n");                                         \
    }                                                              \
  } while (0)

#endif
