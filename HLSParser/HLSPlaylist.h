//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_HLSPLAYLIST_H
#define HLSPARSER_HLSPLAYLIST_H

#include "StreamINF.h"
#include "Media.h"
#include "IFrame.h"
#include "PrintableVector.h"
#include <vector>
#include <ostream>

/*
 * HLS Playlist object to store all data
 */
class HLSPlaylist {
private:
    bool independentSegments = false;
    PrintableVector<Media> mediaList;
    PrintableVector<StreamINF> streamInfList;
    PrintableVector<IFrame> iFrameList;

public:
    bool isIndependentSegments() const;

    void setIndependentSegments(bool independentSegments);

    PrintableVector<Media> &getMediaList();

    void setMediaList(const PrintableVector<Media> &mediaList);

    PrintableVector<StreamINF> &getStreamInfList();

    void setStreamInfList(const PrintableVector<StreamINF> &streamInfList);

    PrintableVector<IFrame> &getIFrameList();

    void setIFrameList(const PrintableVector<IFrame> &iFrameList);


    friend std::ostream &operator<<(std::ostream &os, const HLSPlaylist &playlist);
};



#endif //HLSPARSER_HLSPLAYLIST_H
