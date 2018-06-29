#include "kernel.h"
#include "module.h"

#include "sysutil.h"

int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char* message);

void initSysUtil(void) {
	int sysUtilHandle = sceKernelLoadStartModule("/system/common/lib/libSceSysUtil.sprx", 0, NULL, 0, 0, 0);

	RESOLVE(sysUtilHandle, sceSysUtilSendSystemNotificationWithText);
}

void systemMessage(char* msg) {
 	char buffer[512]; 
 	sprintf(buffer, "%s\n\n\n\n\n\n\n", msg);
 	sceSysUtilSendSystemNotificationWithText(0x81, buffer);
}

