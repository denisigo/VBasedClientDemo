/* Authors: Ivan Zaitsev <ivan.zaitsev@gmail.com>
 *
 * Copyright (C) 2015 X-Media tech, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "VBaseUsb"

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <utils/Log.h>
#include <sys/stat.h>
#include <binder/IServiceManager.h>
#include "VBaseUsbService.h"

namespace android
{

//-------------------------------------------------------------------------------------------------
VBaseUsbService::VBaseUsbService()
{
}

VBaseUsbService::~VBaseUsbService()
{

}

//-------------------------------------------------------------------------------------------------
void VBaseUsbService::publish()
{
  defaultServiceManager()->addService( String16( "vbased.usb" ), this );
}

//-------------------------------------------------------------------------------------------------
void VBaseUsbService::tick()
{
}

//-------------------------------------------------------------------------------------------------

status_t VBaseUsbService::addListener(
                                const sp<IVBaseUsbServiceListener>& listener) {

    // TODO: make threadsafe?

    Vector<sp<IVBaseUsbServiceListener> >::iterator it, end;
    for (it = mListenerList.begin(); it != mListenerList.end(); ++it) {
        if ((*it)->asBinder() == listener->asBinder()) {
            return ALREADY_EXISTS;
        }
    }

    mListenerList.push_back(listener);

    return OK;
}

status_t VBaseUsbService::removeListener(
                                const sp<IVBaseUsbServiceListener>& listener) {

    // TODO: make threadsafe?

    Vector<sp<IVBaseUsbServiceListener> >::iterator it;
    for (it = mListenerList.begin(); it != mListenerList.end(); ++it) {
        if ((*it)->asBinder() == listener->asBinder()) {
            mListenerList.erase(it);
            return OK;
        }
    }

    return BAD_VALUE;
}

size_t VBaseUsbService::countDevices()
{
  printf("countDevices(): 10\n");
  return 10;
}

String8 VBaseUsbService::getDevicePath( size_t idx )
{
  printf("getDevicePath(%u): some_device_path\n", idx);
  return String8( "some_device_path" );
}

UsbDeviceType VBaseUsbService::getDeviceType( size_t idx )
{
  printf("getDeviceType(%u): USB_DEVICE_ANDROID_AUTO\n", idx);
  return USB_DEVICE_ANDROID_AUTO;
}

status_t VBaseUsbService::activateAAuto( bool state )
{
  printf("activateAAuto(%s): OK\n", state ? "true" : "false");
  return OK;
}

status_t VBaseUsbService::activateCarplay( bool state )
{
  printf("activateCarplay(%s): OK\n", state ? "true" : "false");
  return OK;
}

status_t VBaseUsbService::execCmdAAuto( UsbDeviceCmd cmd )
{
  printf("execCmdAAuto(%u): OK\n", cmd);
  return OK;
}

status_t VBaseUsbService::execCmdCarplay( UsbDeviceCmd cmd )
{
  printf("execCmdCarplay(%u): OK\n", cmd);

  // TODO: remove
  // Test notify listeners
  notifyStateChanged(42);

  return OK;
}

void VBaseUsbService::notifyStateChanged(int32_t state){
    Vector<sp<IVBaseUsbServiceListener> >::const_iterator it;
    for (it = mListenerList.begin(); it != mListenerList.end(); ++it) {
      (*it)->onStateChanged(state);
    }
}

}
