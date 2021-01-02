//
//  FFMpegDemuxerImp.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "FFMpegDemuxer.h"
#include "FFMpegCommon.h"

namespace media_demuxer {

class FFMpegDemuxerImp : public FFMpegDemuxer
{
public: // FFMpegDemuxer interface
    virtual bool OpenFileByPath(const std::string &filePath);
    virtual void CloseInputFile();
    virtual media_base::MovieInfo * GetMovieInfo();
    virtual media_base::CompassedFrame * ReadFrame();
    virtual int64_t GetCurrentTime();
    virtual bool Eof();
public:
    FFMpegDemuxerImp();
private:
    void InnerInitFFmpeg();
    void BuildMovieInfo(const std::string &filePath);
    bool IsValidFramerate(int32_t numerator, int32_t denominator);
private:
    AVFormatContext*        _formatContext;
    media_base::MovieInfo   _movieInfo;
    bool                  _eof;
};

}   // namespace media_demuxer
