//
// Created by Sulsenti, Tyler on 1/14/24.
//

#ifndef HLSPARSER_HLSPARSER_H
#define HLSPARSER_HLSPARSER_H
#include <sstream>
#include "HLSPlaylist.h"

//Functional class to store HLSPlaylist parsing operations and data.
class HLSParser {
private:
    static void processTag(HLSPlaylist &hlsPlaylist, std::stringstream &input,
                                std::string &line, std::string::size_type index);

public:
    static const std::string EXTM3U;
    static const std::string EXT_X_STREAM_INF;
    static const std::string EXT_X_MEDIA;
    static const std::string EXT_X_INDEPENDENT_SEGMENTS;
    static const std::string EXT_X_I_FRAME_STREAM_INF;

    static HLSPlaylist parse(std::stringstream &input);

    static std::vector<std::pair<std::string, std::string>> findAttributes(const std::string &attrLine);

    static bool getAttributes(std::string &line, std::string &attr, bool &notAList, bool &end);
};

#endif //HLSPARSER_HLSPARSER_H