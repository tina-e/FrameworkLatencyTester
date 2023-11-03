#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>
#include <vector>

using namespace std;
using namespace chrono;


BITMAPINFO createBitmapInfo()
{
    BITMAPINFO bitmap;
    bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth = 1;
    bitmap.bmiHeader.biHeight = -1;
    bitmap.bmiHeader.biPlanes = 1;
    bitmap.bmiHeader.biBitCount = 32;
    bitmap.bmiHeader.biCompression = BI_RGB;
    bitmap.bmiHeader.biSizeImage = 0;
    bitmap.bmiHeader.biClrUsed = 0;
    bitmap.bmiHeader.biClrImportant = 0;
    return bitmap;
}

int getPixelData(HDC hdcCompatible, HDC hdcScreen, BYTE *bitPointer)
{
    BitBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 0, 0, SRCCOPY);
    return (int)bitPointer[2];
}

void waitForWhite(HDC hdcScreen, HDC hdcCompatible, BYTE *bitPointer)
{
    while (getPixelData(hdcCompatible, hdcScreen, bitPointer) != 255)
    {
        usleep(1);
    }
}

int main(int argc, char **argv)
{
    int iteration = 0;

    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];

    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);

    HBITMAP hBitmap = CreateDIBSection(hdcCompatible, &bitmapinfo, DIB_RGB_COLORS, (void **)(&bitPointer), NULL, NULL);
    SelectObject(hdcCompatible, hBitmap);

    while (true)
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 != 0)
        {
            uint64_t start_time = duration_cast<microseconds>(
                                      system_clock::now().time_since_epoch())
                                      .count();
            waitForWhite(hdcScreen, hdcCompatible, bitPointer);
            uint64_t end_time = duration_cast<microseconds>(
                                    system_clock::now().time_since_epoch())
                                    .count();

            cout << end_time - start_time << endl;
            iteration++;
        }
    }
    return 0;
}

