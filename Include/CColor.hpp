#pragma once
#include <string>

namespace CColor
{
    struct iRGBA;
    struct iHSVA;
    
    struct iRGBA
    {
        int R;
        int G;
        int B;
        int A;

        iRGBA(int R = 0, int G = 0, int B = 0, int A = 255);
        static iRGBA FromHex(std::string HexCode);

        int ToI32();
        iHSVA ToHSV();
        std::string ToHex();
        std::string ToString(bool Brackets = true, bool Constructor = false);
    };

    struct iHSVA
    {
        int H;
        int S;
        int V;
        int A;

        iHSVA(int H = 0, int S = 0, int V = 0, int A = 255);
        
        iRGBA ToRGB();
        std::string ToString(bool Brackets = true, bool Constructor = false);
    };
}