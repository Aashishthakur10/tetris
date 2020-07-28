#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <thread>

using namespace std;
wstring tetromino[7];
//playing field coords
int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenHeight = 30;
int nScreenWidth = 80;
unsigned char *pField = nullptr;

bool doesPieceFit(int i, int i1, int i2, int i3);

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
    bool done = false;

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
        //Game logic
        int nCurrPiece = 1;
        int nCurrRotation = 0;
        int nCurrX = nFieldWidth/2;
        int nCurrY = 0;
        bool arrows[4];
        while(!done) {

            // Game etime
            this_thread::sleep_for(50ms);
            // Input
            for (int k = 0; k < 4; k++){
                arrows[k] =  (0x8000 & GetAsyncKeyState((unsigned char )("\x27\x25\x28Z"[k]))) != 0;
            }
            // Game logic
            if(arrows[1] && doesPieceFit(nCurrPiece, nCurrRotation, nCurrX - 1, nCurrY))
            {
                    nCurrX -= 1;

            }
            else if(arrows[0] && doesPieceFit(nCurrPiece, nCurrRotation, nCurrX + 1, nCurrY) ){
                    nCurrX += 1;
            }
            else if(arrows[2] && doesPieceFit(nCurrPiece, nCurrRotation, nCurrX, nCurrY+1))
            {
                nCurrY += 1;

            }
            if(arrows[0] && doesPieceFit(nCurrPiece, nCurrRotation, nCurrX + 1, nCurrY) ){
                nCurrX += 1;
            }
            // Render Output

            //Draw on screen
            for (int i = 0; i < nFieldWidth; i++) {
                for (int j = 0; j < nFieldHeight; j++) {
                    screen[(j + 2) * nScreenWidth + (i + 2)] = L" ABCDEFG=*"[pField[j * nFieldWidth + i]];;
                }
            }

            // Draw current piece
            for(int px = 0; px < 4; px++){
                for(int py =0; py<4; py++){
                    if (tetromino[nCurrPiece][Rotate(px,py,nCurrRotation)] == L'X'){
                        screen[(nCurrY + py + 2)*nScreenWidth+ (nCurrX+px+2)] = nCurrPiece+65;
                    }
                }
            }

            //Display
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dw);
        }
    return 0;
}




bool doesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY){
    for(int px = 0; px < 4; px++){
        for(int py =0; py<4; py++){
            int ind = Rotate(px,py,nRotation);
            int fi = (nPosY+py) * nFieldWidth + (nPosX+px);
            if(nPosX+px>=0 && nPosX +px < nFieldWidth){
                if(nPosY+py>=0 && nPosY + py < nFieldHeight){
                    if(tetromino[nTetromino][ind]==L'X' && pField[fi]!= 0){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}