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

#ifndef __VBASE_USB_SERVICE_H__
#define __VBASE_USB_SERVICE_H__

#include <utils/RefBase.h>
#include <utils/String16.h>
#include <IVBaseUsbService.h>

namespace android
{

class VBaseUsbService : public BnVBaseUsbService
{
public:
  VBaseUsbService();
  ~VBaseUsbService();

  void tick();
  void publish();

private:
  virtual size_t        countDevices();
  virtual String16      getDevicePath( size_t idx );
  virtual UsbDeviceType getDeviceType( size_t idx );
  virtual status_t      activateAAuto( bool state );
  virtual status_t      activateCarplay( bool state );
  virtual status_t      execCmdAAuto( UsbDeviceCmd cmd );
  virtual status_t      execCmdCarplay( UsbDeviceCmd cmd );
};

}
#endif // __VBASE_USB_SERVICE_H__
