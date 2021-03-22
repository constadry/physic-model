//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_LAND_HPP
#define PHYSIC_LAND_HPP

#include "Object.hpp"

class Land : public Object {
public:
    Land(const string &File,
         const double x,
         const double y,
         const double width,
         const double height,
         const double density) :
            Object(File, x, y, width, height, density) {}
};

#endif //PHYSIC_LAND_HPP
