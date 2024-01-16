cmake_minimum_required(VERSION 3.27)
project(HLSParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(HLSParser main.cpp
        StreamINF.cpp
        StreamINF.h
        HLSParser.cpp
        HLSParser.h
        StreamINFAttribute.h
        HLSPlaylist.cpp
        HLSPlaylist.h
        Media.cpp
        Media.h
        MediaAttribute.h
        IFrame.cpp
        IFrame.h
        IFrameAttribute.h
        PrintableVector.h
        HLSPlaylistSorter.cpp
        HLSPlaylistSorter.h
        HLSPlaylistFetcher.cpp
        HLSPlaylistFetcher.h
)

find_package(unofficial-curlpp CONFIG REQUIRED)
target_link_libraries(HLSParser PRIVATE unofficial::curlpp::curlpp)