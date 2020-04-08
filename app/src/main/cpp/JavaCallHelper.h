//
// Created by yons on 2020-04-08.
//

#ifndef DNPLAYERDEMO_JAVACALLHELPER_H
#define DNPLAYERDEMO_JAVACALLHELPER_H

#include <jni.h>
class JavaCallHelper {

public:
    JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject instance);

    ~JavaCallHelper();

    void onError(int thread, int errorCode);

private:
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;

    jmethodID onErrorId;
};

#endif //DNPLAYERDEMO_JAVACALLHELPER_H


