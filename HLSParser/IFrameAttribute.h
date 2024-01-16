//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_IFRAMEATTRIBUTE_H
#define HLSPARSER_IFRAMEATTRIBUTE_H


/*
 * Class to keep track of the possible attributes within the #EXT-X-I-FRAME-STREAM-INF tag
 */
class IFrameAttribute {
private:
public:
    enum ATTR_TYP {
        BANDWIDTH = 0,
        CODECS = 1,
        RESOLUTION = 2,
        VIDEO_RANGE = 3,
        URI = 4
    };
};


#endif //HLSPARSER_IFRAMEATTRIBUTE_H
