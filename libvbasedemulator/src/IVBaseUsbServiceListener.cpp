#include <utils/Log.h>
#include <stdint.h>
#include <sys/types.h>
#include "IVBaseUsbServiceListener.h"

namespace android {

enum {
    ON_STATE_CHANGED = IBinder::FIRST_CALL_TRANSACTION
};

class BpVBaseUsbServiceListener: public BpInterface<IVBaseUsbServiceListener>
{
public:
    BpVBaseUsbServiceListener(const sp<IBinder>& impl)
        : BpInterface<IVBaseUsbServiceListener>(impl)
    {
    }

    void onStateChanged(int32_t status)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IVBaseUsbServiceListener::getInterfaceDescriptor());
        data.writeInt32(status);
        remote()->transact(ON_STATE_CHANGED, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(VBaseUsbServiceListener, "com.gromaudio.vbased.IVBaseUsbServiceListener");

// ----------------------------------------------------------------------

status_t BnVBaseUsbServiceListener::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ON_STATE_CHANGED: {
            CHECK_INTERFACE(IVBaseUsbServiceListener, data, reply);
            int32_t state = data.readInt32();
            onStateChanged(state);
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

// ----------------------------------------------------------------------------

}; // namespace android

