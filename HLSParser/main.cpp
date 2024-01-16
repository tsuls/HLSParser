#include <iostream>
#include <fstream>
#include <sstream>
#include "HLSPlaylistFetcher.h"

#include "HLSParser.h"
#include "HLSPlaylistSorter.h"

int main() {

    //Start by fetching the document into a string stream
    std::stringstream ss;
    HLSPlaylistFetcher::fetchFromUri(ss);

    if (ss) {
        HLSPlaylist hlsPlaylist = {};
        //send the string stream to our parser
        hlsPlaylist = HLSParser::parse(ss);

        //sort our resulting HLSPlaylist object
        HLSPlaylistSorter::sort(hlsPlaylist);

        //Output to stdout.
       std::cout << "HLSPlaylist Output: " << std::endl << hlsPlaylist << std::endl;
    }

    return 0;
    
}
