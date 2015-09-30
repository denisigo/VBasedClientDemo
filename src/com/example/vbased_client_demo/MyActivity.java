package com.example.vbased_client_demo;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class MyActivity extends Activity{

    private TextView mLogView;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        mLogView = (TextView) findViewById(R.id.log);
        mLogView.setText("start\n");


        // Get ServiceManager.getService method via reflection
        Method method = null;
        try {
            method = Class.forName("android.os.ServiceManager").getMethod("getService", String.class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        
        // Get vbased.usb service binder
        IBinder binder = null;
        try {
            binder = (IBinder) method.invoke(null, "vbased.usb");
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        // Create interface from binder
        IVBaseUsbService usbService = IVBaseUsbService.Stub.asInterface(binder);
        toLogView("connected to service: vbased.usb");

        // Test methods
        try {
            int countDevices = usbService.countDevices();
            toLogView("countDevices(): " + countDevices);

            CharSequence devicePath = usbService.getDevicePath(1);
            toLogView("getDevicePath(1): " + devicePath);

            int deviceType = usbService.getDeviceType(1);
            toLogView("getDeviceType(1): " + deviceType);

            int activateAAuto = usbService.activateAAuto(1);
            toLogView("activateAAuto(1): " + activateAAuto);

            int activateCarplay = usbService.activateCarplay(1);
            toLogView("activateCarplay(1): " + activateCarplay);

            int execCmdAAuto = usbService.execCmdAAuto(1);
            toLogView("execCmdAAuto(1): " + execCmdAAuto);

            int execCmdCarplay = usbService.execCmdCarplay(1);
            toLogView("execCmdCarplay(1): " + execCmdCarplay);
        } catch (RemoteException e) {
        }
    }

    private void toLogView(String message){
        mLogView.append(message + "\n");
    }
}
