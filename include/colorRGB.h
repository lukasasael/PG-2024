#ifndef COLORRGB_H
#define COLORRGB_H
#include <string>
#include <algorithm>

struct colorRGB {
    int red;
    int green;
    int blue;

    std::string to_string() {
        return (std::to_string(red) + ' ' + std::to_string(green) + ' ' + std::to_string(blue));
    }


    inline colorRGB operator=(colorRGB c) {
        red=c.red;
        green=c.green;
        blue=c.blue;
        return c;
    }

    inline colorRGB operator+(colorRGB c) {
        return {std::clamp(0,red+c.red,255),
                std::clamp(0,green+c.green,255),
                std::clamp(0,blue+c.blue,255)};
    }

    inline bool operator==(colorRGB c) {
        return (c.red==red && c.green==green && c.blue==blue);
    }

    inline colorRGB operator*(double d) {
        return {std::clamp(0,(int)(red*d),255),
                std::clamp(0,(int)(green*d),255),
                std::clamp(0,(int)(blue*d),255)};
    }
    inline colorRGB operator/(double d) {
        return {std::clamp(0,(int)(red/d),255),
                std::clamp(0,(int)(green/d),255),
                std::clamp(0,(int)(blue/d),255)};
    }
};

#endif // COLORRGB_H
