#include "kernel.h"
#include "module.h"
#include "sysutil.h"

int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);
int (*sceSystemServiceLaunchWebBrowser)(const char *uri, void *);

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