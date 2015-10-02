package com.gromaudio.vbased;

import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

/**
 * Interface proxy to USB service of VBase daemon
 */
public class VBaseUsbService {
    private static final String SERVICE_NAME = "vbased.usb";

    // Constants must match ones defined in IVBaseUsbService.h
    public static final int USB_DEVICE_NONE                 = 0;
    public static final int USB_DEVICE_ANDROID_ACCESSORY    = 1;
    public static final int USB_DEVICE_ANDROID_AUTO         = 2;
    public static final int USB_DEVICE_APPLE_IAP1           = 3;
    public static final int USB_DEVICE_APPLE_IAP2           = 4;

    public static final int USB_DEVICE_DISCONNECT           = 0;
    public static final int USB_DEVICE_ENABLE               = 1;
    public static final int USB_DEVICE_DISABLE              = 2;

    private final IVBaseUsbService mService;
    private IVBaseUsbServiceListener mServiceListener;
    private Listener mListener;

    public interface Listener{
        void onStateChanged(int state);
    }

    /**
     * Create instance of service interface proxy.
     * Must call close() when proxy is not needed anymore.
     * @param listener Listener instance
     * @throws RemoteException
     */
    public VBaseUsbService(Listener listener) throws RemoteException {
        if (listener == null)
            throw new IllegalArgumentException("Listener must not be null");

        IBinder binder = Utils.getService(SERVICE_NAME);
        if (binder == null)
            throw new IllegalStateException("Unable to get service " + SERVICE_NAME);

        mService = IVBaseUsbService.Stub.asInterface(binder);

        mListener = listener;
        mServiceListener = new VBaseUsbServiceListener();
        mService.addListener(mServiceListener);
    }

    /**
     * Remove listeners and free resources. Don't use object after calling this method.
     */
    public void close(){
        mListener = null;
        if (mServiceListener != null)
            try {
                mService.removeListener(mServiceListener);
            } catch (RemoteException e){
                e.printStackTrace();
            }
        mServiceListener = null;
    }

    private class VBaseUsbServiceListener extends IVBaseUsbServiceListener.Stub {

        private static final String TAG = "VBaseUsbServiceListener";

        @Override
        public IBinder asBinder() {
            return this;
        }

        @Override
        public void onStateChanged(int state) throws RemoteException {
            if (mListener != null)
                mListener.onStateChanged(state);
        }
    }

    public int countDevices() throws RemoteException {
        return mService.countDevices();
    }

    public String getDevicePath(int idx) throws RemoteException {
        return mService.getDevicePath(idx);
    }

    public int getDeviceType(int idx) throws RemoteException {
        return mService.getDeviceType(idx);
    }

    public int activateAAuto(boolean state) throws RemoteException {
        return mService.activateAAuto(state ? 1 : 0);
    }

    public int activateCarplay(boolean state) throws RemoteException {
        return mService.activateCarplay(state ? 1 : 0);
    }

    public int execCmdAAuto(int cmd) throws RemoteException {
        return mService.execCmdAAuto(cmd);
    }

    public int execCmdCarplay(int cmd) throws RemoteException {
        return mService.execCmdCarplay(cmd);
    }
}
