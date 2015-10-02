package com.gromaudio.vbased;

import android.os.IBinder;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Utils {

    /**
     * Get service binder from ServiceManager
     * @param serviceName
     * @return IBinder
     */
    public static IBinder getService(String serviceName){
        Method method = null;
        // Get ServiceManager.getService method via reflection since it is hidden
        try {
            method = Class.forName("android.os.ServiceManager").getMethod("getService", String.class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
            return null;
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return null;
        }

        try {
            return (IBinder) method.invoke(null, serviceName);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
            return null;
        } catch (InvocationTargetException e) {
            e.printStackTrace();
            return null;
        }
    }
}
