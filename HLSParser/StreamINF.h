//
// Created by Sulsenti, Tyler on 1/14/24.
//

#ifndef HLSPARSER_STREAMINF_H
#define HLSPARSER_STREAMINF_H

#include "StreamINFAttribute.h"
#include <map>
#include <utility>
#include <vector>
#include <ostream>
#include "PrintableVector.h"

/*
 * IFrame class to store parsed data from the #EXT-X-I-FRAME-STREAM-INF tag.
 */
class StreamINF {
private:
    long bandwidth;
    long averageBandwidth;
    PrintableVector<std::string> codecs;
    std::string resolution;
    double frameRate;
    std::string videoRange;
    std::string audio;
    std::string closedCaptions;
    std::string uri;


public:
    static const std::map<StreamINFAttribute::ATTR_TYP, std::string> ATTRIBUTES;
    static StreamINF fromAttrValuePairList(const std::vector<std::pair<std::string, std::string>>& attrValuePairs);

    long getBandwidth() const;

    void setBandwidth(long bandwidth);

    long getAverageBandwidth() const;

    void setAverageBandwidth(long averageBandwidth);

    PrintableVector<std::string> &getCodecs() ;

    void setCodecs(const PrintableVector<std::string> &codecs);

    const std::string &getResolution() const;

    void setResolution(const std::string &resolution);

    double getFrameRate() const;

    void setFrameRate(double frameRate);

    const std::string &getVideoRange() const;

    void setVideoRange(const std::string &videoRange);

    const std::string &getAudio() const;

    void setAudio(const std::string &audio);

    const std::string &getClosedCaptions() const;

    void setClosedCaptions(const std::string &closedCaptions);

    const std::string &getUri() const;

    void setUri(const std::string &uri);

    friend std::ostream &operator<<(std::ostream &os, const StreamINF &inf);
};


#endif //HLSPARSER_STREAMINF_H
