//
// Created by laccs on 3/31/2022.
//

#ifndef WIDGET_TEXT_HPP
#define WIDGET_TEXT_HPP

#include "Widget.hpp"

class Text : public Widget {
protected:
    std::string _string;
public:
    Text(PrimeWindow* pw,int x, int y, int sx, int sy, const std::string& str);
    void draw() override;
    void handle(const genv::event& ev) override;
    bool isFocusable() override;

    const std::string &getString() const;
};


#endif //WIDGET_TEXT_HPP
