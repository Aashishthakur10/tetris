#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;
wstring tetromino[7];
//playing field coords
int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenHeight = 30;
int nScreenWidth = 80;
unsigned char *pField = nullptr;

int Rotate(int px, int py, int angle) {
    switch (angle % 4) {
        case 0:
            return py * 4 + px;
        case 1:
            return 12 + py - (px * 4);
        case 2:
            return 15 - (py * 4) - px;
        case 3:
            return 3 - py + (px * 4);
    }
    return 0;
}


int main() {

    //create assets i.e. different types of blocks
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L".. X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L".X...X...XX.....");
    tetromino[6].append(L"..X...X..XX.....");


    pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer
    for (int x = 0; x < nFieldWidth; x++) // Board Boundary
        for (int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

//    wchar_t *screen = new wchar_t[nScreenHeight*nScreenWidth];
        auto *screen = new char[nScreenWidth * nScreenHeight];
        HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
                                                    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hConsole);
        DWORD dw = 0;

            for (int i = 0; i < nFieldWidth; i++) {
                for (int j = 0; j < nFieldHeight; j++) {
                    screen[(j+2)*nScreenWidth+(i+2)] = L" ABCDEFG=#"[pField[j*nFieldWidth+i]];;
                }}
        //Display
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dw);

    return 0;
}
