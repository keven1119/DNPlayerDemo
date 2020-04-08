package com.keven.dnplayerdemo;

public class DNPlayer {

    static {
        System.loadLibrary("native-lib");
    }


    public void start(){}
    public void stop(){}
    public void release(){}

    public void onError(int errorCode){}

    public native void prepare(String dataSource);

}
