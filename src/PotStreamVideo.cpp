#include "PotStreamVideo.h"


PotStreamVideo::PotStreamVideo()
{
    //视频缓冲区, 足够大时会较流畅，但是跳帧会闪烁
    type_ = BPMEDIA_TYPE_VIDEO;
}


PotStreamVideo::~PotStreamVideo()
{
}

//-1无视频
//1有可显示的包，未到时间
//2已经没有可显示的包
int PotStreamVideo::show(int time)
{
    if (stream_index_ < 0)
    {
        return NoVideo;
    }
    if (haveDecoded())
    {
        auto f = getCurrentContent();
        int time_c = f.time;
        if (time >= time_c)
        {
            auto tex = (BP_Texture*)f.data;
            engine_->renderCopy(tex);
            time_shown_ = time_c;
            ticks_shown_ = engine_->getTicks();
            dropDecoded();
            return VideoFrameShowed;
        }
        else
        {
            return VideoFrameBeforeTime;
        }
    }
    return NoVideoFrame;
}

void PotStreamVideo::freeContent(void* p)
{
    engine_->destroyTexture((BP_Texture*)p);
}

FrameContent PotStreamVideo::convertFrameToContent()
{
    auto& f = frame_;
    auto tex = nullptr;
    //auto tex = engine_->createYUVTexture(codec_ctx_->width, codec_ctx_->height);
    engine_->updateYUVTexture(tex, f->data[0], f->linesize[0], f->data[1], f->linesize[1], f->data[2], f->linesize[2]);
    return { time_dts_, f->linesize[0], tex };
}


