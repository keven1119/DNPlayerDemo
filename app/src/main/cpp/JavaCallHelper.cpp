//
// Created by yons on 2020-04-08.
//

#include "JavaCallHelper.h"
#include "macro.h"


JavaCallHelper::JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject instance) {
    this->vm = vm;
    this->env = env;

    this->instance = env->NewGlobalRef(instance);


    jclass  clazz = env->GetObjectClass(instance);
    onErrorId = env->GetMethodID(clazz,"onError","(I)V");
}


JavaCallHelper::~JavaCallHelper() {

    this->env->DeleteGlobalRef(this->instance);
}

void JavaCallHelper::onError(int thread, int errorCode) {
    if(thread == THREAD_MAIN){
        env->CallVoidMethod(instance, onErrorId, errorCode);
    } else{
        JNIEnv *curEnv;
        vm->AttachCurrentThread(&curEnv, 0);
        curEnv->CallVoidMethod(instance,onErrorId, errorCode);
        vm->DetachCurrentThread();
    }
}
