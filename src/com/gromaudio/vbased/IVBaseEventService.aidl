package com.gromaudio.vbased;

/**
 *  AIDL file must match the interface defined in IVBaseEventService.h
 **/
interface IVBaseEventService {
    void startAndroidEvents();
    void stopAndroidEvents();
    String getAndroidDevPath();
    String getNativeDevPath();
}