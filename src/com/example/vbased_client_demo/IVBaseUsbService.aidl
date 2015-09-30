package com.example.vbased_client_demo;

/**
 *  AIDL file must match the interface defined in IVBaseUsbService.h
 **/
interface IVBaseUsbService {
    // TODO: define constants from IVBaseUsbService somewhere since aidl doesn't allow it

    int countDevices();
    String getDevicePath(int idx);
    int getDeviceType(int idx);
    int activateAAuto(int state);
    int activateCarplay(int state);
    int execCmdAAuto(int cmd);
    int execCmdCarplay(int cmd);
}
