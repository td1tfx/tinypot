#include "PotSubtitle.h"
#include "PotSubtitleAss.h"
#include "PotSubtitleSrt.h"
#include "Config.h"
#include "File.h"

PotSubtitle::PotSubtitle()
{
    fontname_ = Config::getInstance()->getString("sub_font");
    if (!File::fileExist(fontname_))
    {
#ifdef _WIN32
        fontname_ = "c:/windows/fonts/msyh.ttc";
#endif
#ifdef __APPLE__
        fontname_ = "/System/Library/Fonts/STHeiti Medium.ttc";
#endif
    }
}


PotSubtitle::~PotSubtitle()
{
    if (Config::getInstance()->getString("sub_font") == "")
    {
        Config::getInstance()->setString(fontname_, "sub_font");
    }
}
