//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_HLSPLAYLISTSORTER_H
#define HLSPARSER_HLSPLAYLISTSORTER_H

#include "HLSPlaylist.h"

//Functional class to store HLSPlaylist sorting operations and data.
//in the future, can be improved to sort on more than just resolution.
class HLSPlaylistSorter {
private:
public:
    static void sort(HLSPlaylist &playlist);
    static int calculateResolution(const std::string& resolution);
    static void quickSort(std::vector<StreamINF> &vector, int left, int right);
    static int quicksortPartition(std::vector<StreamINF> &vector, int left, int right);

};


#endif //HLSPARSER_HLSPLAYLISTSORTER_H
