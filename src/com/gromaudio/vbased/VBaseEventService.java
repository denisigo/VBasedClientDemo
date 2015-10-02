package com.gromaudio.vbased;

import android.os.IBinder;
import android.os.RemoteException;

/**
 * Interface proxy to Events service of VBase daemon
 */
public class VBaseEventService {
    private static final String SERVICE_NAME = "vbased.events";

    private final IVBaseEventService mService;

    /**
     * Create instance of service interface proxy.
     * Must call close() when proxy is not needed anymore.
     * @throws RemoteException
     */
    public VBaseEventService() throws RemoteException {
        IBinder binder = Utils.getService(SERVICE_NAME);
        if (binder == null)
            throw new IllegalStateException("Unable to get service " + SERVICE_NAME);

        mService = IVBaseEventService.Stub.asInterface(binder);
    }

    public void close(){
    }

    public void startAndroidEvents() throws RemoteException {
        mService.startAndroidEvents();
    }

    public void stopAndroidEvents() throws RemoteException {
        mService.stopAndroidEvents();
    }

    public String getAndroidDevPath() throws RemoteException {
        return mService.getAndroidDevPath();
    }

    public String getNativeDevPath() throws RemoteException {
        return mService.getNativeDevPath();
    }
}
