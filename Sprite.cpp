//
// Created by laccs on 3/6/2022.
//

#include "Sprite.hpp"
#include <fstream>

Pixel::Pixel(int xx, int yy, int rr, int gg, int bb) : x(xx), y(yy)  {
    c = Color(rr,gg,bb);
}

Sprite::Sprite(Menu* m,int x,int y,const std::string &fileName) : Widget(m,x,y,0,0) {
    loadFromFile(fileName);
}

void Sprite::loadFromFile(const std::string& fileName) {
    int r,g,b;
    std::ifstream f(fileName);
    if (f.good()) {
        f >> _sx >> _sy;

        for (int i=0; i<_sx; i++) {
            for (int j=0; j<_sy; j++) {
                f >> r >> g >> b;
                _pixels.emplace_back(j, i, r, g, b);
            }
        }
    }
}

void Sprite::draw() {
    for (Pixel &pixel : _pixels) {
        if (!(pixel.c.r == 255 && pixel.c.g == 0 && pixel.c.b == 255)) {
            genv::gout << genv::move_to(pixel.x + _x, pixel.y + _y) << genv::color(pixel.c.r, pixel.c.g, pixel.c.b) << genv::dot;
        }
    }
}

bool Sprite::isFocusable() {
    return false;
}
