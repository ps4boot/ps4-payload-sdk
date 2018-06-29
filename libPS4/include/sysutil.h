#pragma once

#include "libc.h"

extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);

void initSysUtil(void);

void systemMessage(char* msg);

