#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include "DNFFmpeg.h"

DNFFmpeg *dnfFmpeg = 0;
JavaVM *javaVm = 0;
ANativeWindow *window = 0;
pthread_mutex_t mutex;

int JNI_OnLoad(JavaVM *vm,void *r){
    javaVm = vm;
    return JNI_VERSION_1_6;
}


void render(uint8_t *data, int lineszie, int w, int h){
    pthread_mutex_lock(&mutex);
    if(!window){
        pthread_mutex_unlock(&mutex);
        return;
    }

    ANativeWindow_setBuffersGeometry(window,w, h, WINDOW_FORMAT_RGBA_8888);

    ANativeWindow_Buffer windowBuffer;
    if(ANativeWindow_lock(window, &windowBuffer, 0)){
        ANativeWindow_release(window);
        window = 0;
        pthread_mutex_unlock(&mutex);
        return;
    }

    uint8_t  *dst_data = static_cast<uint8_t *>(windowBuffer.bits);
    int dst_linesize = windowBuffer.stride * 4;

    for (int i = 0; i < windowBuffer.height; ++i) {

        memcpy(dst_data + i* dst_linesize, data + i*lineszie, dst_linesize);
    }

    ANativeWindow_unlockAndPost(window);
    pthread_mutex_unlock(&mutex);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_keven_dnplayerdemo_DNPlayer_native_1prepare(JNIEnv *env, jobject thiz,
                                                     jstring data_source) {
    const char *dataSource = env->GetStringUTFChars(data_source, 0);
    JavaCallHelper *helper = new JavaCallHelper(javaVm, env, thiz);

    dnfFmpeg = new DNFFmpeg(helper, dataSource);
    dnfFmpeg->setRenderFrameCallback(render);
    dnfFmpeg->_prepare();

    env->ReleaseStringUTFChars(data_source,dataSource);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_keven_dnplayerdemo_DNPlayer_native_1start(JNIEnv *env, jobject thiz) {
    dnfFmpeg->start();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_keven_dnplayerdemo_DNPlayer_native_1setSurface(JNIEnv *env, jobject thiz,
                                                        jobject surface) {
    pthread_mutex_lock(&mutex);
    if (window) {
        //把老的释放
        ANativeWindow_release(window);
        window = 0;
    }
    window = ANativeWindow_fromSurface(env, surface);
    pthread_mutex_unlock(&mutex);
}