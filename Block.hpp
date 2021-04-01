//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_BLOCK_HPP
#define PHYSIC_BLOCK_HPP

#include "Object.hpp"

class Block : public Object {
public:
    Block(const string &File,
          const double x,
          const double y,
          const double width,
          const double height,
          const double density) :
            Object(File, x, y, width, height, density) {
        sprite_.setPosition((float) 300, (float) (display_height - block_height));
        x_ = 300;
        y_ = display_height - block_height;
        recovery_coefficient_ = 0.9;
    }
};

#endif //PHYSIC_BLOCK_HPP
