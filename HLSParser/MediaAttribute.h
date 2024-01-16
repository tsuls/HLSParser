//
// Created by Sulsenti, Tyler on 1/15/24.
//

#ifndef HLSPARSER_MEDIAATTRIBUTE_H
#define HLSPARSER_MEDIAATTRIBUTE_H

/*
 * Class to keep track of the possible attributes within the #EXT-X-MEDIA tag.
 */
class MediaAttribute {
private:
public:
    enum ATTR_TYP {
        TYPE = 0,
        GROUP_ID = 1,
        NAME = 2,
        LANGUAGE = 3,
        DEFAULT = 4,
        AUTOSELECT = 5,
        CHANNELS = 6,
        URI = 7
    };

};


#endif //HLSPARSER_MEDIAATTRIBUTE_H
