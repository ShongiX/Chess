//
// Created by laccs on 3/6/2022.
//

#ifndef SAKK_SPRITE_H
#define SAKK_SPRITE_H

#include "Widget.hpp"

struct Pixel;

class Sprite : public Widget {
    std::vector<Pixel> _pixels;

public:
    Sprite(const std::string& fileName,int xx,int yy);

    void loadFromFile(const std::string& fileName);
    void draw() override;
};

struct Pixel {
private:
    int x,y;
    Color c = Color(0,0,0);

    friend class Sprite;

public:
    Pixel(int xx,int yy,char rr,char gg,char bb);
};




#endif //SAKK_SPRITE_H
