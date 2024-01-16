//
// Created by Sulsenti, Tyler on 1/15/24.
//

#include "Media.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
/*
 * Definitions for the Media object
 */

//an object mapping string attribute values to our custom enumeration will help with static construction.
const std::map<MediaAttribute::ATTR_TYP, std::string> Media::ATTRIBUTES = {
        {MediaAttribute::ATTR_TYP::TYPE, "TYPE"},
        {MediaAttribute::ATTR_TYP::GROUP_ID, "GROUP-ID"},
        {MediaAttribute::ATTR_TYP::NAME, "NAME"},
        {MediaAttribute::ATTR_TYP::LANGUAGE, "LANGUAGE"},
        {MediaAttribute::ATTR_TYP::DEFAULT, "DEFAULT"},
        {MediaAttribute::ATTR_TYP::AUTOSELECT, "AUTOSELECT"},
        {MediaAttribute::ATTR_TYP::CHANNELS, "CHANNELS"},
        {MediaAttribute::ATTR_TYP::URI, "URI"}
};


/**
 * Factory static function to create an instance of the Media object given a list of attribute value pairs.
 *
 * @param attrValuePairs a list of attribute value pairs
 * @return an Media object with the data from the input list.
 */
Media Media::fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs){
    Media media = {};
    for(const std::pair<std::string, std::string>& attrValuePair : attrValuePairs){
        if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::TYPE)){
            media.setType(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::GROUP_ID)){
            media.setGroupId(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::NAME)){
            media.setName(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::LANGUAGE)){
            media.setLanguage(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::DEFAULT)){
            media.setDefaultValue(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::AUTOSELECT)){
            media.setAutoselect(attrValuePair.second);
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::CHANNELS)){
            std::stringstream ss(attrValuePair.second);
            std::string listValue;

            while(getline(ss, listValue, ',')){
                media.getChannels().push_back(listValue);
            }
        }
        else if(attrValuePair.first == Media::ATTRIBUTES.at(MediaAttribute::ATTR_TYP::URI)){
            media.setUri(attrValuePair.second);
        }
    }

    return media;
}

/*
 * Getters and setters
 */
const std::string &Media::getType() const {
    return type;
}

void Media::setType(const std::string &type) {
    Media::type = type;
}

const std::string &Media::getGroupId() const {
    return groupId;
}

void Media::setGroupId(const std::string &groupId) {
    Media::groupId = groupId;
}

const std::string &Media::getName() const {
    return name;
}

void Media::setName(const std::string &name) {
    Media::name = name;
}

const std::string &Media::getLanguage() const {
    return language;
}

void Media::setLanguage(const std::string &language) {
    Media::language = language;
}

const std::string &Media::getDefaultValue() const {
    return defaultValue;
}

void Media::setDefaultValue(const std::string &defaultValue) {
    Media::defaultValue = defaultValue;
}

const std::string &Media::getAutoselect() const {
    return autoselect;
}

void Media::setAutoselect(const std::string &autoselect) {
    Media::autoselect = autoselect;
}

PrintableVector<std::string> &Media::getChannels() {
    return channels;
}

void Media::setChannels(const PrintableVector<std::string> &channels) {
    Media::channels = channels;
}

const std::string &Media::getUri() const {
    return uri;
}

void Media::setUri(const std::string &uri) {
    Media::uri = uri;
}

// cout override to print this class as a string.
std::ostream &operator<<(std::ostream &os, const Media &media) {
    os << "#EXT-X-MEDIA:TYPE=" << media.type << ",GROUP-ID=\"" << media.groupId << "\",NAME=\""
    << media.name << "\",LANGUAGE=\"" << media.language << "\",DEFAULT=" << media.defaultValue
    <<",AUTOSELECT=" << media.autoselect << ",CHANNELS=\"" << media.channels << "\",URI=\""
    << media.uri << "\"" << std::endl;

    return os;
}
