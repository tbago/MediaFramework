//
//  MovieInfo.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_BASE_MOVIE_INFO_H_
#define MEDIA_BASE_MOVIE_INFO_H_

#include "StreamInfo.h"
#include <vector>

namespace media_base {

/**
 * Movie Info
 */
struct MovieInfo {
    int32_t                     id;         // movie id -1 for unknown
    std::string                 name;      // movie name
    std::string                 format;    // movie format e.g. mov mp4 mxf mts
    std::vector<StreamInfo *>    streams;
    std::map<std::string, std::string> metaData;
public:
    MovieInfo();
    MovieInfo(const MovieInfo &movieInfo);
    MovieInfo & operator=(const MovieInfo &moveInfo);
    ~MovieInfo();
private:
    void CopyInfo(const MovieInfo &movieInfo);
};

}   // namespace media_base
#endif  // MEDIA_BASE_MOVIE_INFO_H_

