#include "VideoMode.h"
#include <Windows.h>

////////////////////////////////////////////////////
VideoMode::VideoMode() :
m_width			(0),
m_height		(0),
m_bitsPerPixel	(0)
{

}

////////////////////////////////////////////////////
VideoMode::VideoMode(unsigned short _modeWidth, unsigned short _modeHeight, unsigned short _modeBitsPerPixel) :
m_width			(_modeWidth),
m_height		(_modeHeight),
m_bitsPerPixel	(_modeBitsPerPixel)
{
}

////////////////////////////////////////////////////
VideoMode VideoMode::GetDesktopMode() const
{
	DEVMODE winmode;
	winmode.dmSize = sizeof(winmode);
	winmode.dmDriverExtra = 0;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &winmode);

	return VideoMode(winmode.dmPelsWidth,winmode.dmPelsHeight,winmode.dmBitsPerPel);
}

////////////////////////////////////////////////////
unsigned short VideoMode::GetWidth() const
{
	return m_width;
}

////////////////////////////////////////////////////
unsigned short VideoMode::GetHeight() const
{
	return m_height;
}

////////////////////////////////////////////////////
unsigned short VideoMode::GetBitsPerPixel() const
{
	return m_bitsPerPixel;
}


