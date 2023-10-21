#include<windows.h>
#include<stdio.h>
#include <ctime>
#include <chrono>

typedef WINAPI COLORREF (*GETPIXEL)(HDC, int, int);
using namespace std::chrono;


// https://stackoverflow.com/questions/4839623/getting-pixel-color-in-c
int main(int argc, char** argv)
{
    bool currentlyWhite = false;
    microseconds timestampLastWhite;
    microseconds msBefore = duration_cast< microseconds >(
            system_clock::now().time_since_epoch()
    );

    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
    if(_hGDI)
    {
        while(true) {
            microseconds ms = duration_cast< microseconds >(
                    system_clock::now().time_since_epoch()
            );
            printf("%d\n", (ms - msBefore));
            msBefore = ms;
            GETPIXEL pGetPixel = (GETPIXEL)GetProcAddress(_hGDI, "GetPixel");
            HDC _hdc = GetDC(NULL);
            if(_hdc)
            {
                COLORREF _color = (*pGetPixel) (_hdc, 0, 0);
                int _red = GetRValue(_color);
                int _green = GetGValue(_color);
                int _blue = GetBValue(_color);

                //printf("Red: %d, ", _red);
                //printf("Green: %d, ", _green);
                //printf("Blue: %d\n", _blue);

                if (_red == 255 && _green == 255 && _blue == 255) {
                    if (!currentlyWhite) {
                        microseconds ms_white = duration_cast< microseconds >(
                                system_clock::now().time_since_epoch()
                        );
                        //std::time_t timestamp = std::time(nullptr);
                        printf("changed to WHITE at %d\n", ms_white);
                        printf("time since last WHITE: %d\n", ms_white - timestampLastWhite);
                        timestampLastWhite = ms_white;
                    }
                    currentlyWhite = true;
                } else {
                    currentlyWhite = false;
                }
                //printf("------------\n");*/
            }
            FreeLibrary(_hGDI);
        }
    }
    return 0;
}
