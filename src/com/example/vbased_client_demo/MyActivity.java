package com.example.vbased_client_demo;

import android.app.Activity;
import android.os.Bundle;
import android.os.RemoteException;
import android.widget.TextView;
import com.gromaudio.vbased.VBaseCameraService;
import com.gromaudio.vbased.VBaseEventService;
import com.gromaudio.vbased.VBaseUsbService;

public class MyActivity extends Activity{

    private TextView mLogView;
    VBaseUsbService mUsbService;
    VBaseEventService mEventService;
    VBaseCameraService mCameraService;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        mLogView = (TextView) findViewById(R.id.log);

        // Test USB service
        toLogView("******** vbased.usb ********");
        try {
            mUsbService = new VBaseUsbService(new VBaseUsbService.Listener() {
                @Override
                public void onStateChanged(int state) {
                    toLogView("Listener: onStateChanged: " + state);
                }
            });
        } catch (RemoteException e) {
            toLogView("Can't connect to service: vbased.usb");
            e.printStackTrace();
            return;
        }
        toLogView("connected to service: vbased.usb");

        try {
            int countDevices = mUsbService.countDevices();
            toLogView("countDevices(): " + countDevices);

            CharSequence devicePath = mUsbService.getDevicePath(1);
            toLogView("getDevicePath(1): " + devicePath);

            int deviceType = mUsbService.getDeviceType(1);
            toLogView("getDeviceType(1): " + deviceType);

            int activateAAuto = mUsbService.activateAAuto(true);
            toLogView("activateAAuto(1): " + activateAAuto);

            int activateCarplay = mUsbService.activateCarplay(true);
            toLogView("activateCarplay(1): " + activateCarplay);

            int execCmdAAuto = mUsbService.execCmdAAuto(1);
            toLogView("execCmdAAuto(1): " + execCmdAAuto);

            int execCmdCarplay = mUsbService.execCmdCarplay(1);
            toLogView("execCmdCarplay(1): " + execCmdCarplay);
        } catch (RemoteException e) {
        }


        // Test Event service
        toLogView("\n******** vbased.events ********");
        try {
            mEventService = new VBaseEventService();
        } catch (RemoteException e) {
            toLogView("Can't connect to service: vbased.events");
            e.printStackTrace();
            return;
        }
        toLogView("connected to service: vbased.events");

        try {
            mEventService.startAndroidEvents();
            toLogView("startAndroidEvents(): void");

            mEventService.stopAndroidEvents();
            toLogView("stopAndroidEvents(): void");

            String getAndroidDevPath = mEventService.getAndroidDevPath();
            toLogView("getAndroidDevPath(): " + getAndroidDevPath);

            String getNativeDevPath = mEventService.getNativeDevPath();
            toLogView("getNativeDevPath(): " + getNativeDevPath);
        } catch (RemoteException e) {
        }

        // Test Camera service
        toLogView("\n******** vbased.camera ********");
        try {
            mCameraService = new VBaseCameraService();
        } catch (RemoteException e) {
            toLogView("Can't connect to service: vbased.camera");
            e.printStackTrace();
            return;
        }
        toLogView("connected to service: vbased.camera");

        try {
            int countCameras = mCameraService.countCameras();
            toLogView("countCameras(): " + countCameras);

            int startCameraStream = mCameraService.startCameraStream(1);
            toLogView("startCameraStream(1): " + startCameraStream);

            int stopCameraStream = mCameraService.stopCameraStream();
            toLogView("stopCameraStream(): " + stopCameraStream);
        } catch (RemoteException e) {
        }
    }

    @Override
    protected void onDestroy() {
        mUsbService.close();
        mEventService.close();
        mCameraService.close();

        super.onDestroy();
    }

    private void toLogView(String message){
        mLogView.append(message + "\n");
    }
}
