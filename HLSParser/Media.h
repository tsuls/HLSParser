//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_MEDIA_H
#define HLSPARSER_MEDIA_H

#include "MediaAttribute.h"
#include <map>
#include <string>
#include <vector>
#include <ostream>
#include "PrintableVector.h"

/*
 * Media class to store parsed data from the #EXT-X-MEDIA tag.
 */
class Media {
private:
    std::string type;
    std::string groupId;
    std::string name;
    std::string language;
    std::string defaultValue;
    std::string autoselect;
    PrintableVector<std::string> channels;
    std::string uri;

public:

    static const std::map<MediaAttribute::ATTR_TYP, std::string> ATTRIBUTES;
    static Media fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs);

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getGroupId() const;

    void setGroupId(const std::string &groupId);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getLanguage() const;

    void setLanguage(const std::string &language);

    const std::string &getDefaultValue() const;

    void setDefaultValue(const std::string &defaultValue);

    const std::string &getAutoselect() const;

    void setAutoselect(const std::string &autoselect);

    PrintableVector<std::string> &getChannels();

    void setChannels(const PrintableVector<std::string> &channels);

    const std::string &getUri() const;

    void setUri(const std::string &uri);

    friend std::ostream &operator<<(std::ostream &os, const Media &media);

};


#endif //HLSPARSER_MEDIA_H
