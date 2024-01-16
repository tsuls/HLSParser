//
// Created by Sulsenti, Tyler on 1/15/24.
//

#include "HLSPlaylist.h"

/*
 * Definitions for HLSPlaylist object.
 */

bool HLSPlaylist::isIndependentSegments() const {
    return independentSegments;
}

void HLSPlaylist::setIndependentSegments(bool independentSegments) {
    HLSPlaylist::independentSegments = independentSegments;
}

PrintableVector<Media> &HLSPlaylist::getMediaList() {
    return mediaList;
}

void HLSPlaylist::setMediaList(const PrintableVector<Media> &mediaList) {
    HLSPlaylist::mediaList = mediaList;
}

PrintableVector<StreamINF> &HLSPlaylist::getStreamInfList() {
    return streamInfList;
}

void HLSPlaylist::setStreamInfList(const PrintableVector<StreamINF> &streamInfList) {
    HLSPlaylist::streamInfList = streamInfList;
}

PrintableVector<IFrame> &HLSPlaylist::getIFrameList() {
    return iFrameList;
}

void HLSPlaylist::setIFrameList(const PrintableVector<IFrame> &iFrameList) {
    HLSPlaylist::iFrameList = iFrameList;
}

std::ostream &operator<<(std::ostream &os, const HLSPlaylist &playlist) {
    os << "#EXTM3U\n";
    if(playlist.isIndependentSegments()){
        os << "#EXT-X-INDEPENDENT-SEGMENTS\n";
    }
    os << playlist.mediaList
    << playlist.iFrameList
    << playlist.streamInfList;

    return os;
}
