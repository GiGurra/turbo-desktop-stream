//============================================================================
// Name        : TurboDesktopRecord.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>

static char s_blob[50 * 1024 * 1024];

int main() {

	HWND desktop = GetDesktopWindow();
	HDC desktopHdc = GetDC(desktop);
	HBITMAP desktopBmp = (HBITMAP) GetCurrentObject(desktopHdc, OBJ_BITMAP);

	BITMAPINFO bmpInfo = { };
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	GetDIBits(desktopHdc, desktopBmp, 0, 1, NULL, &bmpInfo, DIB_RGB_COLORS);

	const int w = bmpInfo.bmiHeader.biWidth;
	const int h = bmpInfo.bmiHeader.biHeight;
	const int bits = bmpInfo.bmiHeader.biBitCount;

	std::cout << "w/h/bits: " << w << "/" << h << "/" << bits << std::endl;
	std::cout << "sz: " << bmpInfo.bmiHeader.biSize << std::endl;
	std::cout << "szImg: " << bmpInfo.bmiHeader.biSizeImage << std::endl;

	while (true) {

		LARGE_INTEGER frequency, start, end;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);

		const int lines = GetDIBits(desktopHdc, desktopBmp, 0, h, s_blob,
				&bmpInfo, DIB_RGB_COLORS);

		QueryPerformanceCounter(&end);

		double interval = (double) ((double) end.QuadPart
				- (double) start.QuadPart) / (double) frequency.QuadPart;

		std::cout << "lines/dt: " << lines << "/" << interval << std::endl;

	}

	return 0;

}

// Also see http://www.codeproject.com/Articles/5051/Various-methods-for-capturing-the-screen
