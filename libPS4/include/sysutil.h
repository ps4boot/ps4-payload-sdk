#pragma once

#include "libc.h"

#define SCE_USER_SERVICE_MAX_LOGIN_USERS 4
#define SCE_USER_SERVICE_MAX_USER_NAME_LENGTH 16

extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);

typedef struct SceUserServiceLoginUserIdList {
	int32_t userId[SCE_USER_SERVICE_MAX_LOGIN_USERS];
} SceUserServiceLoginUserIdList;


void initSysUtil(void);
void systemMessage(char* msg);
void openBrowser(char* uri);
SceUserServiceLoginUserIdList getUserIDList();
int32_t getUserID();
char *getUserName(int32_t userId);
int32_t getInitialUser();