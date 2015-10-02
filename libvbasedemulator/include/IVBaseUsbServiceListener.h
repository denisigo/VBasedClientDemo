#ifndef __VBASE_USB_SERVICE_LISTENER_H__
#define __VBASE_USB_SERVICE_LISTENER_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

class IVBaseUsbServiceListener: public IInterface
{
    /**
     * Keep up-to-date with IVBaseUsbServiceListener.aidl
     */
public:
    DECLARE_META_INTERFACE(VBaseUsbServiceListener);

    virtual void            onStateChanged(int32_t status) = 0;
};


class BnVBaseUsbServiceListener: public BnInterface<IVBaseUsbServiceListener>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}; // namespace android

#endif
