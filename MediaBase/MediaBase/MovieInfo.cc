//
//  MovieInfo.cc
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "MovieInfo.h"

namespace media_base {

MovieInfo::MovieInfo()
{
    id = -1;
}

MovieInfo::MovieInfo(const MovieInfo &movieInfo)
{
    CopyInfo(movieInfo);
}

MovieInfo & MovieInfo::operator=(const MovieInfo &movieInfo)
{
    if (this == &movieInfo) {
        return *this;
    }
    CopyInfo(movieInfo);
    return *this;
}

MovieInfo::~MovieInfo()
{
    for (uint32_t i = 0; i < streams.size(); i++) {
        StreamInfo *streamInfo = streams[i];
        delete streamInfo;
        streams[i] = NULL;
    }
    streams.clear();
}

void MovieInfo::CopyInfo(const MovieInfo &movieInfo)
{
    id = movieInfo.id;
    name = movieInfo.name;
    format = movieInfo.format;

    for (uint32_t i = 0; i < movieInfo.streams.size(); i++) {
        StreamInfo *streamInfo = new StreamInfo(*movieInfo.streams[i]);
        streams.push_back(streamInfo);
    }
}

}   // namespoace media_base

