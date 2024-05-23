#include "CColor.hpp"
#include <sstream>
#include <iomanip>

using namespace CColor;

iRGBA::iRGBA(int r, int g, int b, int a)
{
    R = r;
    G = g;
    B = b;
    A = a;
}

iRGBA iRGBA::FromHex(std::string HexCode)
{
    // Accept with or without #
    if (HexCode[0] == '#') HexCode.erase(0, 1);

    // Expand shorthand hex codes
    if (HexCode.size() == 3)
        HexCode = HexCode.substr(0, 1) + HexCode.substr(0, 1) +
        HexCode.substr(1, 1) + HexCode.substr(1, 1) +
        HexCode.substr(2, 1) + HexCode.substr(2, 1);

    // Subsitute Alpha
    if (HexCode.size() == 6)
        HexCode += "FF";

    // Conversion
    unsigned int HVal;
    std::stringstream Stream;
    Stream << std::hex << HexCode;
    Stream >> HVal;
    return iRGBA((HVal >> 24) & 0xFF, (HVal >> 16) & 0xFF, (HVal >> 8) & 0xFF, HVal & 0xFF);
}

std::string iRGBA::ToHex()
{
    std::stringstream Stream;
    Stream << std::setfill('0') << std::setw(2) << std::hex << A;
    Stream << std::setfill('0') << std::setw(2) << std::hex << R;
    Stream << std::setfill('0') << std::setw(2) << std::hex << G;
    Stream << std::setfill('0') << std::setw(2) << std::hex << B;
    return "#" + Stream.str();
}

int iRGBA::ToI32()
{
    return (A << 24) | (R << 16) | (G << 8) | B;
}

std::string iRGBA::ToString(bool Brackets, bool IncludeConstructor)
{
    // Whether to include Alpha or not
    bool IncludeAlpha = A == 255;
    std::string Constructor = IncludeAlpha?"RGB":"RGBA";
    std::string Result = (IncludeConstructor?Constructor:"");

    // Open brackets if necessary
    if (Brackets) Result += "(";
    Result = Result
    + std::to_string(R) + ", "
    + std::to_string(G) + ", "
    + std::to_string(B);

    if (IncludeAlpha)
    Result += ", " + std::to_string(A);

    // Close brackets if necessary
    if (Brackets) Result += ")";
    return Result;
}

// Thank you chatgpt
iHSVA iRGBA::ToHSV()
{
    float r = R / 255.0f;
    float g = G / 255.0f;
    float b = B / 255.0f;
    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float delta = max - min;

    int h = 0;
    if (delta > 0.00001f)
    {
        if (max == r)
            h = 60 * (int)((g - b) / delta) % 360;
        else if (max == g)
            h = 60 * (int)((b - r) / delta + 2);
        else
            h = 60 * (int)((r - g) / delta + 4);
        
        if (h < 0)
            h += 360;
    }

    int s = max == 0 ? 0 : (delta / max) * 100;
    int v = max * 100;

    return iHSVA(h, s, v, A);
}

iRGBA iHSVA::ToRGB()
{
    float h = H;
    float s = S / 100.0f;
    float v = V / 100.0f;
    int hi = static_cast<int>(h / 60.0f) % 6;
    float f = (h / 60.0f) - hi;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    float r = 0, g = 0, b = 0;
    switch (hi)
    {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }

    return iRGBA(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255), A);
}

iHSVA::iHSVA(int h, int s, int v, int a)
{
    H = h;
    S = s;
    V = v;
    A = a;
}

std::string iHSVA::ToString(bool Brackets, bool IncludeConstructor)
{
    // Whether to include Alpha or not
    bool IncludeAlpha = A == 255;
    std::string Constructor = IncludeAlpha?"HSV":"HSVA";
    std::string Result = (IncludeConstructor?Constructor:"");

    // Open brackets if necessary
    if (Brackets) Result += "(";
    Result = Result
    + std::to_string(H) + ", "
    + std::to_string(S) + ", "
    + std::to_string(V);

    if (IncludeAlpha)
    Result += ", " + std::to_string(A);

    // Close brackets if necessary
    if (Brackets) Result += ")";
    return Result;
}