//
// Created by Sulsenti, Tyler on 1/14/24.
//

#include <iostream>
#include <utility>
#include <vector>
#include "HLSParser.h"

//Tags included in the HLS playlist - Note: may not include all possible HLS tags.
// The scope of this project will be within the assignment HLS document.
//It is possible that this can be expanded as future steps to accomade more tags.
const std::string HLSParser::EXTM3U = "#EXTM3U";
const std::string HLSParser::EXT_X_INDEPENDENT_SEGMENTS = "#EXT-X-INDEPENDENT-SEGMENTS";
const std::string HLSParser::EXT_X_MEDIA = "#EXT-X-MEDIA";
const std::string HLSParser::EXT_X_STREAM_INF = "#EXT-X-STREAM-INF";
const std::string HLSParser::EXT_X_I_FRAME_STREAM_INF = "#EXT-X-I-FRAME-STREAM-INF";

/**
 * Master parser function. From the input stream of a HLS Playlist, it will parse the document and create the
 * necessary objects in memory.
 *
 * @param input the reference to the input stream containing the HLS Playlist document.
 * @return A HLSPlaylist object constructed from the values in the stream
 */
HLSPlaylist HLSParser::parse(std::stringstream &input) {
    HLSPlaylist hlsPlaylist  = {};
    //https://developer.apple.com/documentation/http-live-streaming/event-playlist-construction#
    //All HLS playlists must start with #EXTM3U
    //Lets check the first line.
    bool validPlaylist = false;
    std::string curLine{};
    //Loop through the document, through blank space lines to find the #EXTM3U tag
    while(input.peek() != EOF){
        getline(input, curLine);
        //when found, mark it and exit this loop
        if (curLine == EXTM3U) {
            validPlaylist = true;
            break;
        }
    }

    //If it isn't there, then exit.
    if (!validPlaylist) {
        std::cout << "ERROR" << std::endl;
        throw std::invalid_argument("HLS Playlists must start with " + EXTM3U + ". Invalid Playlist was received. ");
    }

    //if it is, then continue parsing the rest of the document.

    //If we are here, then our playlist has a valid first tag. Begin parsing the rest\
    //Loop until end of file is reached.
    while (input.peek() != EOF) {
        getline(input, curLine);

        //Look for a tag
        if(curLine.find("#EXT-", 0) == 0){
            //We need to split the string on the colon that separates the tag from its attributes
            std::string delimiter = ":";
            std::string::size_type delIndex = curLine.find(delimiter);

            if(delIndex == std::variant_npos){
                //check for #EXT-X-INDEPENDENT-SEGMENTS
                if(curLine == EXT_X_INDEPENDENT_SEGMENTS){
                    hlsPlaylist.setIndependentSegments(true);
                }
            }
            //other than independent segments, we haveb found a tag and need to process it.
            else {
                processTag(hlsPlaylist, input, curLine, delIndex);
            }
        }

    }

    //End of parser.
    return hlsPlaylist;
}

/**
 * Helper/Utility/Service to process HLS tags when they are seen. It will add them to the referenced HLS Playlist Object
 * based upon what tag is sent to it.
 *
 * @param hlsPlaylist - the reference to the HLS playlist object being constructed in this parser
 * @param input - the reference to the input stream, used to find the next line, if necessary
 * @param line - the reference to the current line, used to dissect the tag and attribute string
 * @param index - the string position of the colon separating the tag and the attribute list. It will never equal npos.
 */
void HLSParser::processTag(HLSPlaylist &hlsPlaylist, std::stringstream  &input,
                                  std::string &line, std::string::size_type index) {
    //index is the location of the :
    //tag is everything in front
    //attr is everything after (excluding :)
    std::string tag = line.substr(0, index);
    std::string attr = line.substr(index + 1);

    if(tag == EXT_X_STREAM_INF){

        //process the attributes
        std::vector<std::pair<std::string, std::string>> attrValuePairs =
                findAttributes(attr);

        //Build the StreamINF Object from the key value pairs.
        StreamINF streamINF = StreamINF::fromAttrValuePairList(attrValuePairs);

        //the next line should be the uri
        getline(input, line);
        //Error checking on the uri.
        if(line.empty() || line.find('#') != std::variant_npos){
            //error
            throw std::invalid_argument("Expected a URL. Got a tag " + line);
        }
        streamINF.setUri(line);

        //add to the Playlist Object
        hlsPlaylist.getStreamInfList().push_back(streamINF);

    }
    else if(tag == EXT_X_MEDIA){
        //process the attributes
        std::vector<std::pair<std::string, std::string>> attrValuePairs =
                findAttributes(attr);

        //Build the Media Object from the key value pairs.
        Media media = Media::fromAttrValuePairList(attrValuePairs);

        //add to the Playlist Object
        hlsPlaylist.getMediaList().push_back(media);

    }
    else if(tag == EXT_X_I_FRAME_STREAM_INF){
        //process the attributes
        std::vector<std::pair<std::string, std::string>> attrValuePairs =
                findAttributes(attr);

        //Build the IFrame Object from the key value pairs.v
        IFrame iFrame = IFrame::fromAttrValuePairList(attrValuePairs);

        //add to the Playlist Object
        hlsPlaylist.getIFrameList().push_back(iFrame);
    }

    //end of processor/service. - in the future we can account for more HLS tags and expand our parser.
}

/**
 * Helper/Utility to find the attributes given in a line. They are comma separated.
 *
 * @param attrLine the line of comma separated attributes.
 * @return a vector of attribute,value pairs.
 */
std::vector<std::pair<std::string, std::string>> HLSParser::findAttributes(const std::string& attrLine){
    std::vector<std::pair<std::string, std::string>> attrValuePairs;
    //split the comma delimited attr string
    //There are several commas & attrs to split on, as well as nested ones that represent lists
    //We will define a custom mini parser to handle this.

    //create a place to store our attribute
    std::string attr;
    std::string lineCopy = attrLine; //copying to preserve original text
    bool notAList = true; //memory allocation for listFlag in iterative function
    bool end = false;
    while(getAttributes(lineCopy, attr, notAList, end)){
        //Now that we have an attribute, we know that it is attrName=attrValue.

        //Split one last time on '=';
        std::string attributeKey = attr.substr(0, attr.find('='));
        std::string attributeValue = attr.substr(attr.find('=') + 1);

        //one check to remove escaped quotes
        while(attributeValue.find('\"') != std::variant_npos){
            attributeValue.erase(attributeValue.find('\"'), 1);
        }

        //create a key value pair and add it to the vector of pairs.
        std::pair<std::string, std::string> attrValuePair(attributeKey, attributeValue);
        attrValuePairs.push_back(attrValuePair);
    }

    return attrValuePairs;
}

/**
 * Helper function to iterate through a line of comma separated attributes and extract the attribute=value portion from
 * the comma separated list. It takes embedded lists (between quotes) into consideration.
 *
 * @param line a reference to the line of comma separated attributes.
 * @param attr the reference to the location where the attribute=value string will be stored once it is parsed here.
 * @param notAList the reference to the boolean flag that determines if we have found a nested list as a value or not.
 * @param end the reference to the boolean flag that determines if the program has finished parsing the attributes or not.
 * @return true if there is more to parse in the comma separated attribute list string, false if not.
 */
bool HLSParser::getAttributes(std::string &line, std::string &attr, bool &notAList, bool &end){
    if(end){
        return false;
    }

    std::string::size_type commaIndex;

    //if we meet the conditions for a list last iteration
    if(!notAList){
        //we will be interested in the second occurrence of the comma
        commaIndex = line.find(',', line.find(',') + 1);

        //reset the list flag.
        notAList = true;
    }
    else{
        //Otherwise, only the first occurrence is required
        commaIndex = line.find(',');
    }

    //Get the string before the comma, this will be out attribute=value
    std::string sub1 = line.substr(0, commaIndex);
    //Get the string after the comma, this will be the remainder
    std::string sub2 = line.substr(commaIndex + 1, line.size());

    //Commas either mean we have a new attribute=value pair, or we stumbled into a nested list.
    //Check for a list in the next attribute to collect. Does the next attribute's value start with a quotation mark.
    if(sub2.find("=\"") != std::variant_npos) {
        //If so, a list exists if a comma exists between this quotation mark and its closing one.

        //Find the first quote
        std::string ::size_type firstQuote = sub2.find("=\"");
        //Find the next comma
        std::string::size_type nextComma = sub2.find(',');
        //Find the second occurrence of the quote
        std::string::size_type nextQuote = sub2.find('\"', sub2.find('\"') + 1);

        //We found a list when the next comma in our string is between the values' quotes, and these quotes exist.
        if(nextQuote != std::variant_npos &&  firstQuote < nextComma && nextComma < nextQuote){
            //mark the list flag for next iteration.
            notAList = false;
        }
    }

    // if another comma exists, move through the line.
    if(commaIndex != std::variant_npos) {
        line = sub2;
    }
    //end the loop if not.
    else{
        attr = sub1;
        end = true;
    }

    //split this on the = and have fun.
    attr = sub1;
    return true;
}
