//
// Created by Sulsenti, Tyler on 1/16/24.
//

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <sstream>
#include "HLSPlaylistFetcher.h"
const std::string HLSPlaylistFetcher::FETCH_URL =
        "https://lw.bamgrid.com/2.0/hls/vod/bam/ms02/hls/dplus/bao/master_unenc_hdr10_all.m3u8";

/**
 * Utility function to fetch the HLSPlaylist from a static URL.
 * Uses the 3rd party library cURLpp (a libcurl c++ wrapper) to perform HTTP get requests & response collection.
 * https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
 * https://github.com/jpbarrette/curlpp/tree/master
 *
 * @param ss the reference to the string stream to store the GET response.
 */
void HLSPlaylistFetcher::fetchFromUri(std::stringstream &ss){
    //init
    cURLpp::initialize(CURL_GLOBAL_ALL);

    cURLpp::Cleanup cleaner;
    cURLpp::Easy request;

    //Set up the URL & output to stream reference
    request.setOpt( cURLpp::options::Url(FETCH_URL));
    request.setOpt( cURLpp::options::WriteStream(&ss));
    request.perform();

    cURLpp::terminate();
}