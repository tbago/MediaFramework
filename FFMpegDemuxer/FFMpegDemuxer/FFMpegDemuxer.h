//
//  FFMpegDemuxer.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include <MediaBase/MediaBase.h>

namespace media_demuxer {
/**
 *  Demuxer media file by ffmpeg
 *  This is only interface object,all method are implement by subclass
 *  Please call 'createFFMpegDemuxer' function to create instance.
 */
class FFMpegDemuxer
{
public:
    /**
     *  Open file by path
     *
     *  @param filePath input file path
     *
     *  @return success or failed
     */
    virtual bool OpenFileByPath(const std::string &filePath) = 0;

    virtual void CloseInputFile() = 0;

    virtual media_base::MovieInfo * GetMovieInfo() = 0;

    virtual media_base::CompassedFrame * ReadFrame() = 0;

    virtual int64_t GetCurrentTime() = 0;

    /**
     *  Whether read end of the file
     *
     *  @return weather end of file
     */
    virtual bool Eof() = 0;
};

/**
 *  Create Demuxer instance
 *
 *  @return demuxer instance
 */
FFMpegDemuxer *createFFMpegDemuxer();

}   //namespace media_demuxer

