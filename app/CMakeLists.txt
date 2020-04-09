cmake_minimum_required(VERSION 3.4.1)

# 创建一个变量 source_file 它的值就是src/main/cpp/ 所有的.cpp文件
file(GLOB source_file src/main/cpp/*.cpp)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        src/main/cpp/native-lib.cpp

        # Provides a relative path to your source file(s).
        ${source_file})

set(distribution_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI})

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library( avformat
        SHARED
        IMPORTED)
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavformat.a )

add_library( avcodec
        SHARED
        IMPORTED )
set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavcodec.a )

add_library( avfilter
        SHARED
        IMPORTED)
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavfilter.a )

add_library( avutil
        SHARED
        IMPORTED )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libavutil.a )

add_library( swresample
        SHARED
        IMPORTED )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libswresample.a )

add_library( swscale
        SHARED
        IMPORTED)
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/libswscale.a )




set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


target_link_libraries( # Specifies the target library.
        native-lib
        avformat avcodec avfilter    avutil swresample swscale


        #        swscale
#        swresample
#        avutil
#        avformat
#        avfilter
#        avcodec

        # Links the target library to the log library
        # included in the NDK.
        log z android)