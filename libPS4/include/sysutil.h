#pragma once

#include "libc.h"

extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);
extern int (*sceSystemServiceLaunchWebBrowser)(const char *uri, void *);

void initSysUtil(void);
void systemMessage(char* msg);
void openBrowser(char* uri);