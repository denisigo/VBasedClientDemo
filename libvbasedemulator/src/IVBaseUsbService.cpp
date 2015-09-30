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

#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include "IVBaseUsbService.h"

namespace android
{


class BpVBaseUsbService : public BpInterface<IVBaseUsbService>
{
public:
  BpVBaseUsbService( const sp<IBinder>& impl )
    : BpInterface<IVBaseUsbService>( impl ) {}

    virtual size_t countDevices()
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      remote()->transact( COUNT_DEVICES, data, &reply );
      return reply.readInt32();
    }

    virtual String16 getDevicePath( size_t idx )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( idx );
      remote()->transact( GET_DEVICE_PATH, data, &reply );
      return reply.readString16();
    }

    virtual UsbDeviceType getDeviceType( size_t idx )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( idx );
      remote()->transact( GET_DEVICE_TYPE, data, &reply );
      return (UsbDeviceType)reply.readInt32();
    }

    virtual status_t activateAAuto( bool state )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( state ? 1 : 0 );
      remote()->transact( ACTIVATE_ANDROID_AUTO, data, &reply );
      return reply.readInt32();
    }

    virtual status_t activateCarplay( bool state )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( state ? 1 : 0 );
      remote()->transact( ACTIVATE_APPLE_CARPLAY, data, &reply );
      return reply.readInt32();
    }

    virtual status_t execCmdAAuto( UsbDeviceCmd cmd )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( (int32_t)cmd );
      remote()->transact( EXEC_CMD_ANDROID_AUTO, data, &reply );
      return reply.readInt32();
    }

    virtual status_t execCmdCarplay( UsbDeviceCmd cmd )
    {
      Parcel data, reply;
      data.writeInterfaceToken( IVBaseUsbService::getInterfaceDescriptor() );
      data.writeInt32( (int32_t)cmd );
      remote()->transact( EXEC_CMD_APPLE_CARPLAY, data, &reply );
      return reply.readInt32();
    }
};


IMPLEMENT_META_INTERFACE( VBaseUsbService, "com.example.vbased_client_demo.IVBaseUsbService" );

status_t BnVBaseUsbService::onTransact( uint32_t  code,
                                        const     Parcel& data,
                                        Parcel*   reply,
                                        uint32_t  flags )
{
  switch( code )
  {
    case COUNT_DEVICES:
    {
      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      reply->writeNoException();
      reply->writeInt32( countDevices() );
      return NO_ERROR;
    }break;

    case GET_DEVICE_PATH:
    {
      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      reply->writeNoException();
      reply->writeString16( getDevicePath( data.readInt32() ) );
      return NO_ERROR;
    }break;

    case GET_DEVICE_TYPE:
    {
      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      reply->writeNoException();
      reply->writeInt32( (int32_t)getDeviceType( data.readInt32() ) );
      return NO_ERROR;
    }break;

    case ACTIVATE_ANDROID_AUTO:
    {
      bool state;

      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      state = ( ( data.readInt32() == 1 ) ? true : false );
      reply->writeNoException();
      reply->writeInt32( activateAAuto( state ) );
      return NO_ERROR;
    }break;

    case ACTIVATE_APPLE_CARPLAY:
    {
      bool state;

      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      state = ( ( data.readInt32() == 1 ) ? true : false );
      reply->writeNoException();
      reply->writeInt32( activateCarplay( state ) );
      return NO_ERROR;
    }break;

    case EXEC_CMD_ANDROID_AUTO:
    {
      UsbDeviceCmd cmd;

      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      cmd = (UsbDeviceCmd)data.readInt32();
      reply->writeNoException();
      reply->writeInt32( execCmdAAuto( cmd ) );
      return NO_ERROR;
    }break;

    case EXEC_CMD_APPLE_CARPLAY:
    {
      UsbDeviceCmd cmd;

      CHECK_INTERFACE( IVBaseUsbService, data, reply );
      cmd = (UsbDeviceCmd)data.readInt32();
      reply->writeNoException();
      reply->writeInt32( execCmdCarplay( cmd ) );
      return NO_ERROR;
    }break;
  }
  return BBinder::onTransact( code, data, reply, flags );
};

// ----------------------------------------------------------------------------

}; // namespace android
