#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include "colorRGB.h"


class Screen {
    public:
        Screen();
        Screen(int w, int h);
        int width();
        int height();
        colorRGB get(int x, int y);
        void set(int x, int y, colorRGB color);
        std::string to_string();
        //~Screen();

    protected:
        int w;
        int h;
        colorRGB** pixels;
    private:
};

#endif // SCREEN_H
