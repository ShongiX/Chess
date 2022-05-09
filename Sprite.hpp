//
// Created by laccs on 3/6/2022.
//

#ifndef SAKK_SPRITE_H
#define SAKK_SPRITE_H

#include "Widget.hpp"

struct Pixel;

class Sprite : public Widget {
protected:
    std::vector<Pixel> _pixels;

public:
    Sprite() = default;
    Sprite(Menu* m,int x,int y,const std::string& fileName);

    void loadFromFile(const std::string& fileName);
    void draw() override;
    bool isFocusable() override;
};

struct Pixel {
public:
    int x,y;
    Color c = Color(0,0,0);

    friend class Sprite;

public:
    Pixel(int xx,int yy,int rr,int gg,int bb);
};




#endif //SAKK_SPRITE_H
