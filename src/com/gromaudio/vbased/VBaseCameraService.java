package com.gromaudio.vbased;

import android.os.IBinder;
import android.os.RemoteException;

/**
 * Interface proxy to Camera service of VBase daemon
 */
public class VBaseCameraService {
    private static final String SERVICE_NAME = "vbased.camera";

    private final IVBaseCameraService mService;

    /**
     * Create instance of service interface proxy.
     * Must call close() when proxy is not needed anymore.
     * @throws RemoteException
     */
    public VBaseCameraService() throws RemoteException {
        IBinder binder = Utils.getService(SERVICE_NAME);
        if (binder == null)
            throw new IllegalStateException("Unable to get service " + SERVICE_NAME);

        mService = IVBaseCameraService.Stub.asInterface(binder);
    }

    public void close(){
    }

    public int countCameras() throws RemoteException {
        return mService.countCameras();
    }

    public int startCameraStream(int idx) throws RemoteException {
        return mService.startCameraStream(idx);
    }

    public int stopCameraStream() throws RemoteException {
        return mService.stopCameraStream();
    }
}
