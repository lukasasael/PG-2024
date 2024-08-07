#include "Screen.h"
#include <iostream>

Screen::Screen() {
    this->w = 256;
    this->h = 256;
    this->pixels = new colorRGB*[h];
    for (int y = 0; y < h; y++) {
        this->pixels[y] = new colorRGB[w];

        for (int x = 0; x < w; ++x) {
            this->pixels[y][x].red = 0;
            this->pixels[y][x].green = 0;
            this->pixels[y][x].blue = 0;
        }
    }
}

Screen::Screen(int w, int h) {
    this->w = w;
    this->h = h;
    this->pixels = new colorRGB*[h];
    for (int y = 0; y < h; y++) {
        this->pixels[y] = new colorRGB[w];

        for (int x = 0; x < w; ++x) {
            this->pixels[y][x].red = 0;
            this->pixels[y][x].green = 0;
            this->pixels[y][x].blue = 0;
        }
    }
}


colorRGB Screen::get(int x, int y) {
    return this->pixels[y][x];
}

void Screen::set(int x, int y, colorRGB color) {
    this->pixels[y][x] = color;
}

std::string Screen::to_string() {
    std::string retorno = "P3\n" + std::to_string(w) + " " + std::to_string(h) + "\n255\n";
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            colorRGB color = get(x, y);
            retorno += std::to_string(color.red) + " " + std::to_string(color.green) + " " + std::to_string(color.blue) + "\n";
        }
    }
    return retorno;
}

