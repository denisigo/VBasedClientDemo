package com.gromaudio.vbased;

/**
 *  AIDL file must match the interface defined in IVBaseCameraService.h
 **/
interface IVBaseCameraService {
    int countCameras();
    int startCameraStream(int idx);
    int stopCameraStream();
}