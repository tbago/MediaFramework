# MediaFramework
Media framework for iOS， Written in C++ for cross platoform usage.

The framework is basic on ffmpeg.

## How to compile
I use the script basic on [FFmpeg-iOS-build-script](https://github.com/kewlbear/FFmpeg-iOS-build-script).

* First you should download the FFMpeg source code from [ffmpeg.org](http://ffmpeg.org/download.html#releases). (I use ffmpeg 4.3.1). Then copy the ffmpeg source folder to the * MediaFramework root path and rename the dictionary name to FFMpegSource;
* Second I have alreay update the FFMpeg Build Scrip in FFMpegScript folder. Then you can run the [build-ffmpeg-decoder.sh](https://github.com/tbago/MediaFramework/blob/master/FFMpegScript/build-ffmpeg-decoder.sh) to build the ffmpeg decoder, And run the [build-ffmpeg-demuxer.sh](https://github.com/tbago/MediaFramework/blob/master/FFMpegScript/build-ffmpeg-demuxer.sh) to build the ffmpeg demuxer;
* The build script is dependeny on the yasm. And if you already install the **homebrew** then the script will download the yasm automatic;

* Then you can open the **MediaFramework.xcworkspace** to build and run the project.

## Todo List

* For now I just impelement the video decoder and display. The audio decoder and player is not complete;
* And the video audio sync is also not implement;
* You can use this Framework to test the video latency(There is no latency except the decoder cost times);
* Or you can just use it as rtsp server for no audio;