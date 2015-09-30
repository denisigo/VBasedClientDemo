#define LOG_TAG "VBasedEmulator"

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <stdlib.h>
#include <getopt.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "VBaseUsbService.h"

using namespace android;

int main(int argc, char *argv[])
{
	sp<VBaseUsbService> usb_service = new VBaseUsbService();
    usb_service->publish();


	android::ProcessState::self()->startThreadPool();

	ALOGI("ready");

	android::IPCThreadState::self()->joinThreadPool();
	return(0);
}

