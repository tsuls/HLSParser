//
// Created by Sulsenti, Tyler on 1/15/24.
//

#include "IFrame.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

/*
 * Definitions for the IFrame object
 */

//an object mapping string attribute values to our custom enumeration will help with static construction.
const std::map<IFrameAttribute::ATTR_TYP, std::string> IFrame::ATTRIBUTES = {
        {IFrameAttribute::ATTR_TYP::BANDWIDTH, "BANDWIDTH"},
        {IFrameAttribute::ATTR_TYP::CODECS, "CODECS"},
        {IFrameAttribute::ATTR_TYP::RESOLUTION, "RESOLUTION"},
        {IFrameAttribute::ATTR_TYP::VIDEO_RANGE, "VIDEO-RANGE"},
        {IFrameAttribute::ATTR_TYP::URI, "URI"}
};

/**
 * Factory static function to create an instance of the IFrame object given a list of attribute value pairs.
 *
 * @param attrValuePairs a list of attribute value pairs
 * @return an IFrame object with the data from the input list.
 */
IFrame IFrame::fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs){
    IFrame iFrame = {};
    for(const std::pair<std::string, std::string>& attrValuePair : attrValuePairs){
        if(attrValuePair.first == IFrame::ATTRIBUTES.at(IFrameAttribute::ATTR_TYP::BANDWIDTH)){
            iFrame.setBandwidth(stol(attrValuePair.second));
        }
        else if(attrValuePair.first == IFrame::ATTRIBUTES.at(IFrameAttribute::ATTR_TYP::CODECS)){
            std::stringstream ss(attrValuePair.second);
            std::string listValue;

            while(getline(ss, listValue, ',')){
                iFrame.getCodecs().push_back(listValue);
            }
        }
        else if(attrValuePair.first == IFrame::ATTRIBUTES.at(IFrameAttribute::ATTR_TYP::RESOLUTION)){
            iFrame.setResolution(attrValuePair.second);
        }
        else if(attrValuePair.first == IFrame::ATTRIBUTES.at(IFrameAttribute::ATTR_TYP::VIDEO_RANGE)){
            iFrame.setVideoRange(attrValuePair.second);
        }
        else if(attrValuePair.first == IFrame::ATTRIBUTES.at(IFrameAttribute::ATTR_TYP::URI)){
            iFrame.setUri(attrValuePair.second);
        }
    }

    return iFrame;
}

/*
 * Getters and setters
 */
long IFrame::getBandwidth() const {
    return bandwidth;
}

void IFrame::setBandwidth(long bandwidth) {
    IFrame::bandwidth = bandwidth;
}

PrintableVector<std::string> &IFrame::getCodecs() {
    return codecs;
}

void IFrame::setCodecs(const PrintableVector<std::string> &codecs) {
    IFrame::codecs = codecs;
}

const std::string &IFrame::getResolution() const {
    return resolution;
}

void IFrame::setResolution(const std::string &resolution) {
    IFrame::resolution = resolution;
}

const std::string &IFrame::getVideoRange() const {
    return videoRange;
}

void IFrame::setVideoRange(const std::string &videoRange) {
    IFrame::videoRange = videoRange;
}

const std::string &IFrame::getUri() const {
    return uri;
}

void IFrame::setUri(const std::string &uri) {
    IFrame::uri = uri;
}

// cout override to print this class as a string.
std::ostream &operator<<(std::ostream &os, const IFrame &frame) {
    os << "#EXT-X-I-FRAME-STREAM-INF:BANDWIDTH=" << frame.bandwidth
    << ",CODECS=\"" << frame.codecs << "\",RESOLUTION=" << frame.resolution
    << ",VIDEO-RANGE=" << frame.videoRange << ",URI=\"" << frame.uri << "\""
            << std::endl;

    return os;
}
