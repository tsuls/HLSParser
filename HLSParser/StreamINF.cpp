//
// Created by Sulsenti, Tyler on 1/14/24.
//

#include "StreamINF.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
/*
 * Definitions for the StreamINF object
 */

//an object mapping string attribute values to our custom enumeration will help with static construction.
const std::map<StreamINFAttribute::ATTR_TYP, std::string> StreamINF::ATTRIBUTES = {
        {StreamINFAttribute::ATTR_TYP::BANDWIDTH, "BANDWIDTH"},
        {StreamINFAttribute::ATTR_TYP::AVERAGE_BANDWIDTH, "AVERAGE-BANDWIDTH"},
        {StreamINFAttribute::ATTR_TYP::CODECS, "CODECS"},
        {StreamINFAttribute::ATTR_TYP::RESOLUTION, "RESOLUTION"},
        {StreamINFAttribute::ATTR_TYP::FRAME_RATE, "FRAME-RATE"},
        {StreamINFAttribute::ATTR_TYP::VIDEO_RANGE, "VIDEO-RANGE"},
        {StreamINFAttribute::ATTR_TYP::AUDIO, "AUDIO"},
        {StreamINFAttribute::ATTR_TYP::CLOSED_CAPTIONS, "CLOSED-CAPTIONS"}
};

/**
 * Factory static function to create an instance of the StreamINF object given a list of attribute value pairs.
 *
 * @param attrValuePairs a list of attribute value pairs
 * @return an StreamINF object with the data from the input list.
 */
StreamINF StreamINF::fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs){
    StreamINF streamINF = {};
    for(const std::pair<std::string, std::string>& attrValuePair : attrValuePairs){
        if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::BANDWIDTH)){
           streamINF.setBandwidth(stol(attrValuePair.second));
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::AVERAGE_BANDWIDTH)){
            streamINF.setAverageBandwidth(stol(attrValuePair.second));
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::CODECS)){
            std::stringstream ss(attrValuePair.second);
            std::string listValue;

            while(getline(ss, listValue, ',')){
                streamINF.getCodecs().push_back(listValue);
            }
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::RESOLUTION)){
            streamINF.setResolution(attrValuePair.second);
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::FRAME_RATE)){
           streamINF.setFrameRate(stod(attrValuePair.second));
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::VIDEO_RANGE)){
           streamINF.setVideoRange(attrValuePair.second);
        }
        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::AUDIO)){
          streamINF.setAudio(attrValuePair.second);
        }

        else if(attrValuePair.first == StreamINF::ATTRIBUTES.at(StreamINFAttribute::ATTR_TYP::CLOSED_CAPTIONS)){
          streamINF.setClosedCaptions(attrValuePair.second);
        }
    }

    return streamINF;
}

/*
 * Getters and setters
 */
long StreamINF::getBandwidth() const {
    return bandwidth;
}

void StreamINF::setBandwidth(long bandwidth) {
    StreamINF::bandwidth = bandwidth;
}

long StreamINF::getAverageBandwidth() const {
    return averageBandwidth;
}

void StreamINF::setAverageBandwidth(long averageBandwidth) {
    StreamINF::averageBandwidth = averageBandwidth;
}

PrintableVector<std::string> &StreamINF::getCodecs() {
    return codecs;
}

void StreamINF::setCodecs(const PrintableVector<std::string> &codecs) {
    StreamINF::codecs = codecs;
}

const std::string &StreamINF::getResolution() const {
    return resolution;
}

void StreamINF::setResolution(const std::string &resolution) {
    StreamINF::resolution = resolution;
}

double StreamINF::getFrameRate() const {
    return frameRate;
}

void StreamINF::setFrameRate(double frameRate) {
    StreamINF::frameRate = frameRate;
}

const std::string &StreamINF::getVideoRange() const {
    return videoRange;
}

void StreamINF::setVideoRange(const std::string &videoRange) {
    StreamINF::videoRange = videoRange;
}

const std::string &StreamINF::getClosedCaptions() const {
    return closedCaptions;
}

void StreamINF::setClosedCaptions(const std::string &closedCaptions) {
    StreamINF::closedCaptions = closedCaptions;
}

const std::string &StreamINF::getUri() const {
    return uri;
}

void StreamINF::setUri(const std::string &uri) {
    StreamINF::uri = uri;
}

const std::string &StreamINF::getAudio() const {
    return audio;
}

void StreamINF::setAudio(const std::string &audio) {
    StreamINF::audio = audio;

}

std::ostream &operator<<(std::ostream &os, const StreamINF &inf){
    os << "#EXT-X-STREAM-INF:BANDWIDTH=" << inf.bandwidth << ",AVERAGE-BANDWIDTH="
    << inf.averageBandwidth << ",CODECS=\"" << inf.codecs << "\",RESOLUTION=" << inf.resolution
    << ",FRAME-RATE=" << inf.frameRate << ",VIDEO-RANGE=" << inf.videoRange << ",AUDIO=\""
    << inf.audio << "\",CLOSED-CAPTIONS=" << inf.closedCaptions << std::endl << inf.uri
    << std::endl;

    return os;
}


