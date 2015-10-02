package com.gromaudio.vbased;

/**
 *  AIDL file must match the interface defined in IVBaseUsbServiceListener.h
 **/
interface IVBaseUsbServiceListener {
    void onStateChanged(int state);
}
