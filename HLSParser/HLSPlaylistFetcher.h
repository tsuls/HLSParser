//
// Created by Sulsenti, Tyler on 1/16/24.
//

#ifndef HLSPARSER_HLSPLAYLISTFETCHER_H
#define HLSPARSER_HLSPLAYLISTFETCHER_H

/*
 * Utility class to fetch from am static url.
 * in the future with more time, we could fetch from dynamic, command line or file fed urls.
 */
class HLSPlaylistFetcher {
private:
    static const std::string FETCH_URL;
public:
    static void fetchFromUri(std::stringstream &ss);

};


#endif //HLSPARSER_HLSPLAYLISTFETCHER_H
