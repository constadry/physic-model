//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_BLOCK_HPP
#define PHYSIC_BLOCK_HPP

#include "Ball.hpp"

class Block : public Object {
public:
    float angel;
    Block(const string &File,
          const double x,
          const double y,
          const double width,
          const double height,
          const double density) :
            Object(File, x, y, width, height, density) {

        x_ = 300;
        angel = 0;

        sprite_.setOrigin((float) width_, (float) height_);
        sprite_.setPosition(float(x_ + width_), Const::display_height);

        y_ = Const::display_height - Const::block_height;
        recovery_coefficient_ = 0.15;
        weight_ *= 4;
    }

    void fall (float speed) {
        angel += speed / 200;
        sprite_.setRotation(angel);
        width_ += speed / 1000;
        sprite_.setPosition(float(x_ + width_), Const::display_height);
    }
};

#endif //PHYSIC_BLOCK_HPP
