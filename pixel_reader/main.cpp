#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>
#include <vector>

using namespace std::chrono;

/*LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam){
    if(wParam == WM_LBUTTONDOWN)
    {
        clickedAt = duration_cast<microseconds>(
                system_clock::now().time_since_epoch()
        );
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}*/

struct Event {
    uint64_t start;  // event timestamp in microseconds
    uint64_t end;  // event timestamp in microseconds
    uint64_t delta;  // event timestamp in microseconds
    int iteration;  // iteration number to identify events belonging together
};

std::vector<Event> events;
std::string testProgramName;
std::string frameworkName;

// appends event to the events list
void logEvent(uint64_t start, uint64_t end, int iteration)
{
    Event tempEvent = Event();
    tempEvent.start = start;
    tempEvent.end = end;
    tempEvent.delta = end - start;
    tempEvent.iteration = iteration;
    events.push_back(tempEvent);
}

// called when program is finished
// iterates the events list and prints it to stdout in CSV format
void printLog()
{
    std::cout << "start,end,delta,iteration,program,framework" << std::endl;
    for(auto const& ev : events)
    {
        std::cout << std::dec <<
             ev.start << "," <<
             ev.end << "," <<
             ev.delta << "," <<
             ev.iteration << "," <<
             testProgramName << "," <<
             frameworkName << std::endl;
    }
}


BITMAPINFO createBitmapInfo() {
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

int getPixelData_getpixel(HDC hdc) {
    COLORREF _color = GetPixel(hdc, 0, 0);
    return int(GetRValue(_color));
}

int getPixelData_bitblt(HDC hdcCompatible, HDC hdcScreen, BYTE* bitPointer) {
    BitBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 0, 0, SRCCOPY);
    /* *b = (int)bitPointer[0];
    *g = (int)bitPointer[1];
    *r = (int)bitPointer[2];*/
    return (int)bitPointer[2];
}

int getPixelData_getdbit(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE* bitPointer, BITMAPINFO bitmapinfo) {
    //HBITMAP hbwindow = CreateCompatibleBitmap(hdcScreen, 1, 1);
    //SelectObject(hdcCompatible, hbwindow);

    StretchBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 0, 0, 1, 1, SRCCOPY);   //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hdcCompatible, hBitmap, 0, 1, bitPointer, (BITMAPINFO*)&bitmapinfo, DIB_RGB_COLORS);

    /* *b = (int)bitPointer[0];
    *g = (int)bitPointer[1];
    *r = (int)bitPointer[2];*/
    return (int)bitPointer[2];
}

// currently only working for getpixel
void waitForWhiteGetPixel(HDC hdcScreen)
{
    while(getPixelData_getpixel(hdcScreen) != 255)
    {
        usleep(1);
    }
    return;
}

void waitForWhiteBitBlt(HDC hdcScreen, HDC hdcCompatible, BYTE* bitPointer)
{
    while(getPixelData_bitblt(hdcCompatible, hdcScreen, bitPointer) != 255)
    {
        usleep(1);
    }
    return;
}

void waitForWhiteGetDBits(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE* bitPointer, BITMAPINFO bitmapinfo)
{
    while(getPixelData_getdbit(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo) != 255)
    {
        usleep(1);
    }
    return;
}

int main() {
    int iteration = 0;
    testProgramName = "bitblt";
    frameworkName = "pygame";
    //HHOOK mouse = SetWindowsHookEx(WH_MOUSE_LL, &MouseHookProc, 0, 0);

    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE* bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];

    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);

    HBITMAP hBitmap = CreateDIBSection(hdcCompatible, &bitmapinfo, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, NULL);
    // HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, 1, 1);  //bitmap for getdbits
    SelectObject(hdcCompatible, hBitmap);

    while(iteration < 20) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 != 0) {
            uint64_t start_time = duration_cast<microseconds>(
                    system_clock::now().time_since_epoch()
            ).count();
            //logEvent(start_time, EVENT_TYPE_CLICK, iteration);

            // waitForWhiteGetPixel(hdcScreen);
            waitForWhiteBitBlt(hdcScreen, hdcCompatible, bitPointer);
            // waitForWhiteGetDBits(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo);

            uint64_t end_time = duration_cast<microseconds>(
                    system_clock::now().time_since_epoch()
            ).count();
            logEvent(start_time, end_time, iteration);

            //std::cout << end_time - start_time << std::endl;
            iteration++;
        }
    }

    printLog();
    //UnhookWindowsHookEx(mouse);
    return 0;
}
