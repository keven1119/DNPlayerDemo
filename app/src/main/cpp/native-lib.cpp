#include <jni.h>
#include <string>
#include "DNFFmpeg.h"

DNFFmpeg *dnfFmpeg = 0;

JavaVM *javaVm = 0;

int JNI_OnLoad(JavaVM *vm,void *r){
    javaVm = vm;
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_keven_dnplayerdemo_DNPlayer_prepare(JNIEnv *env,jobject  obj, jstring dataSource_) {

    char *datasource = const_cast<char *>(env->GetStringUTFChars(dataSource_, 0));

    dnfFmpeg = new DNFFmpeg(new JavaCallHelper(javaVm, env, obj), datasource);

    dnfFmpeg->_prepare();

    env->ReleaseStringUTFChars(dataSource_,datasource);
}