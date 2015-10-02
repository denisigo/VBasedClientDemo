package com.gromaudio.vbased;

import com.gromaudio.vbased.IVBaseUsbServiceListener;

/**
 *  AIDL file must match the interface defined in IVBaseUsbService.h
 **/
interface IVBaseUsbService {
    int addListener(IVBaseUsbServiceListener listener);
    int removeListener(IVBaseUsbServiceListener listener);

    int countDevices();
    String getDevicePath(int idx);
    int getDeviceType(int idx);
    int activateAAuto(int state);
    int activateCarplay(int state);
    int execCmdAAuto(int cmd);
    int execCmdCarplay(int cmd);
}
