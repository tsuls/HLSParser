//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_IFRAME_H
#define HLSPARSER_IFRAME_H
#include "IFrameAttribute.h"
#include "PrintableVector.h"
#include <map>
#include <vector>
#include <string>
#include <ostream>

/*
 * IFrame class to store parsed data from the #EXT-X-I-FRAME-STREAM-INF tag.
 */
class IFrame {
private:
    long bandwidth;
    PrintableVector<std::string> codecs;
    std::string resolution;
    std::string videoRange;
    std::string uri;
public:
    static const std::map<IFrameAttribute::ATTR_TYP, std::string> ATTRIBUTES;
    static IFrame fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs);

    long getBandwidth() const;

    void setBandwidth(long bandwidth);

    PrintableVector<std::string> &getCodecs();

    void setCodecs(const PrintableVector<std::string> &codecs);

    const std::string &getResolution() const;

    void setResolution(const std::string &resolution);

    const std::string &getVideoRange() const;

    void setVideoRange(const std::string &videoRange);

    const std::string &getUri() const;

    void setUri(const std::string &uri);

    friend std::ostream &operator<<(std::ostream &os, const IFrame &frame);

};


#endif //HLSPARSER_IFRAME_H
