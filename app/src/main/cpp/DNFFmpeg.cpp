//
// Created by yons on 2020-04-08.
//

#include "DNFFmpeg.h"
#include "VideoChannel.h"
#include "macro.h"
#include <cstring>



void *task_prepare(void *arg){

    char *ds = static_cast<char *>(arg);

    return 0;

}

DNFFmpeg::DNFFmpeg(JavaCallHelper *javaCallHelper,const char *datasource) {
    this->javaCallHelper = javaCallHelper;
    this->dataSource = new char[strlen(datasource)];
    strcpy(this->dataSource, datasource);

}

DNFFmpeg::~DNFFmpeg() {
    delete this->dataSource;
    dataSource = 0;
    DELETE(javaCallHelper)
}

void DNFFmpeg::prepare() {
    pthread_create(&pid,0, task_prepare,dataSource);
}


void DNFFmpeg::_prepare() {

    avformat_network_init();


    AVFormatContext *formatContext = 0;
    int ret = avformat_open_input(&formatContext, dataSource,0,0);

    if(ret!=0){
        javaCallHelper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }

    ret = avformat_find_stream_info(formatContext, 0);

    if(ret<0){
        javaCallHelper->onError(THREAD_CHILD,FFMPEG_CAN_NOT_FIND_STREAMS);

        return;
    }

    for (int i = 0; i < formatContext->nb_streams; ++i) {
        AVStream *stream = formatContext->streams[i];

        AVCodecParameters *codecParameters = stream->codecpar;

        if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO){

        } else if(codecParameters->codec_type==AVMEDIA_TYPE_VIDEO){

        }

    }
}
