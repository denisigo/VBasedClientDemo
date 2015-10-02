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

#ifndef __IVBASE_USB_SERVICE_H__
#define __IVBASE_USB_SERVICE_H__

#include <binder/IInterface.h>
#include <batteryservice/IBatteryPropertiesListener.h>

namespace android {

class IVBaseUsbServiceListener;

enum UsbDeviceType {
  USB_DEVICE_NONE               = 0,
  USB_DEVICE_ANDROID_ACCESSORY  = 1,
  USB_DEVICE_ANDROID_AUTO       = 2,
  USB_DEVICE_APPLE_IAP1         = 3,
  USB_DEVICE_APPLE_IAP2         = 4,
};

enum UsbDeviceCmd {
  USB_DEVICE_DISCONNECT         = 0,
  USB_DEVICE_ENABLE             = 1,
  USB_DEVICE_DISABLE            = 2,
};

enum {
  ADD_LISTENER = IBinder::FIRST_CALL_TRANSACTION,
  REMOVE_LISTENER,

  COUNT_DEVICES,
  GET_DEVICE_PATH,
  GET_DEVICE_TYPE,
  ACTIVATE_ANDROID_AUTO,
  ACTIVATE_APPLE_CARPLAY,
  EXEC_CMD_ANDROID_AUTO,
  EXEC_CMD_APPLE_CARPLAY,
};

class IVBaseUsbService : public IInterface
{
public:
  DECLARE_META_INTERFACE( VBaseUsbService );

  virtual status_t      addListener(const sp<IVBaseUsbServiceListener>& listener) = 0;
  virtual status_t      removeListener(const sp<IVBaseUsbServiceListener>& listener) = 0;

  virtual size_t        countDevices()                      = 0;
  virtual String8       getDevicePath( size_t idx )         = 0;
  virtual UsbDeviceType getDeviceType( size_t idx )         = 0;
  virtual status_t      activateAAuto( bool state )         = 0;
  virtual status_t      activateCarplay( bool state )       = 0;
  virtual status_t      execCmdAAuto( UsbDeviceCmd cmd )    = 0;
  virtual status_t      execCmdCarplay( UsbDeviceCmd cmd )  = 0;
};

class BnVBaseUsbService : public BnInterface<IVBaseUsbService>
{
public:
  virtual status_t onTransact( uint32_t       code,
                               const Parcel&  data,
                               Parcel*        reply,
                               uint32_t       flags = 0 );
};

}; // namespace android

#endif // __IVBASE_USB_SERVICE_H__
