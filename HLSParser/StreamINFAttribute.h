//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_STREAMINFATTRIBUTE_H
#define HLSPARSER_STREAMINFATTRIBUTE_H
#include <string>

/*
 * Class to keep track of the possible attributes within the #EXT-X-I-FRAME-STREAM-INF tag
 */
class StreamINFAttribute {
private:
public:
    enum ATTR_TYP {
        BANDWIDTH = 0,
        AVERAGE_BANDWIDTH = 1,
        CODECS = 2,
        RESOLUTION = 3,
        FRAME_RATE = 4,
        VIDEO_RANGE = 5,
        AUDIO = 6,
        CLOSED_CAPTIONS = 7
    };

};


#endif //HLSPARSER_STREAMINFATTRIBUTE_H
