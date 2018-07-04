#include "kernel.h"
#include "module.h"
#include "sysutil.h"

int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);
int (*sceSystemServiceLaunchWebBrowser)(const char *uri, void *);
int (*sceUserServiceInitialize)(void *);
int (*sceUserServiceGetLoginUserIdList)(SceUserServiceLoginUserIdList *);
int (*sceUserServiceGetUserName)(SceUserServiceUserId userId, char *userName, const size_t size);
int (*sceUserServiceTerminate)();


void initSysUtil(void) {
	int sysUtilHandle = sceKernelLoadStartModule("/system/common/lib/libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
	int libSceSystemService = sceKernelLoadStartModule("/system/common/lib/libSceSystemService.sprx", 0, NULL, 0, 0, 0);
	RESOLVE(sysUtilHandle, sceSysUtilSendSystemNotificationWithText);
	RESOLVE(libSceSystemService, sceSystemServiceLaunchWebBrowser);
}

void systemMessage(char* msg) {
 	char buffer[512]; 
 	sprintf(buffer, "%s\n\n\n\n\n\n\n", msg);
 	sceSysUtilSendSystemNotificationWithText(0x81, buffer);
}

void openBrowser(char* uri) {
 	sceSystemServiceLaunchWebBrowser(uri, NULL);
}

SceUserServiceLoginUserIdList getUserIDList()
{
	int ret;
    SceUserServiceLoginUserIdList userIdList;
	int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
    RESOLVE(libSceUserService, sceUserServiceInitialize);
	RESOLVE(libSceUserService, sceUserServiceGetLoginUserIdList);
	RESOLVE(libSceUserService, sceUserServiceTerminate);
    ret = sceUserServiceInitialize(NULL);
	if (ret == 0) 
	{
		ret = sceUserServiceGetLoginUserIdList(&userIdList);
		if (ret == 0) 
		{
			sceUserServiceTerminate();
			return userIdList;
		}
	}
	return userIdList;
}

int32_t getUserID()
{
	int ret;
    SceUserServiceLoginUserIdList userIdList;
	int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
    RESOLVE(libSceUserService, sceUserServiceInitialize);
	RESOLVE(libSceUserService, sceUserServiceGetLoginUserIdList);
	RESOLVE(libSceUserService, sceUserServiceTerminate);
    ret = sceUserServiceInitialize(NULL);
	if (ret == 0) 
	{
		ret = sceUserServiceGetLoginUserIdList(&userIdList);
		if (ret == 0) 
		{
			for (int i = 0; i < 1; i ++) 
			{
				if (userIdList.userId[i] != -1) 
				{
					sceUserServiceTerminate();
					return userIdList.userId[i];
				}
			}
		}
	}
	return -1;
}

char *getUserName(SceUserServiceUserId userId)
{
	int ret;
	char *retval = malloc(SCE_USER_SERVICE_MAX_USER_NAME_LENGTH);
	int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
    RESOLVE(libSceUserService, sceUserServiceInitialize);
	RESOLVE(libSceUserService, sceUserServiceGetUserName);
	RESOLVE(libSceUserService, sceUserServiceTerminate);
    ret = sceUserServiceInitialize(NULL);
	if (ret == 0) 
	{
		char username[SCE_USER_SERVICE_MAX_USER_NAME_LENGTH + 1];
        ret = sceUserServiceGetUserName(userId, username, sizeof(username));
		if (ret == 0) 
		{ 
	        strcpy(retval, username);
			sceUserServiceTerminate();
            return retval;
		}
	}
	return NULL;
}
