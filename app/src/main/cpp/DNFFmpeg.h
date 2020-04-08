//
// Created by yons on 2020-04-08.
//

#include <sys/types.h>
#include <pthread.h>
#include "JavaCallHelper.h"

extern "C" {
#include <libavformat/avformat.h>
}


#ifndef DNPLAYERDEMO_DNPLAYER_H
#define DNPLAYERDEMO_DNPLAYER_H

class DNFFmpeg{
public:
    DNFFmpeg(JavaCallHelper* javaCallHelper, const char* datasource);
    ~DNFFmpeg();

    void _prepare();
    void prepare();


private:
    char *dataSource = 0;
    pthread_t pid;
    AVFormatContext *formatContext;
    JavaCallHelper *javaCallHelper;


};


#endif //DNPLAYERDEMO_DNPLAYER_H

