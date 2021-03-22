//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_OBJECT_HPP
#define PHYSIC_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

const double g = 9.80665;

const short int help_degree = 18;
int display_width = 640, display_height = 480;

int cannon_width = 60, cannon_height = 60;
int stand_width = 27, stand_height = 22;
int ball_width = 31, ball_height = 31;
int back_height = 750;
int block_width = 34, block_height = 123;
int position_back_y = back_height - display_height;

float cannon_position_x = 20, cannon_position_y = 467;
const double den_iron = 7870, den_wood = 530, den_land = 1000;

int ball_speed = 75; // позже необходимо реализовать изменение скорости прямо внутри приложения

const double cannon_len = 30;

using namespace sf;
using namespace std;

class Object {
protected:

    double x_in_sprite, y_in_sprite,
            width_, height_,
            x_, y_,
            weight_, density_;

public:

    String file_;
    Image image_;
    Texture texture_;
    Sprite sprite_;

    Object(const string &File,
           const double x,
           const double y,
           const double width,
           const double height,
           const double density) {

        file_ = File;
        width_ = width;
        height_ = height;

        image_.loadFromFile("images/" + file_);
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);

        x_in_sprite = x;
        y_in_sprite = y;

        sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));

        x_ = y_ = 0;

        density_ = density;

        weight_ = density_*width_*height_/1000000;
    }

    void setX(const double x) {
        x_ = x;
    }

//    double getX() const {
//        return x_;
//    }

    void setY(const double y) {
        y_ = y;
    }

//    double getY() const {
//        return y_;
//    }

    static void rebound(double &speed) {
        speed = speed*sqrt(0.7);
    }

    double get_weight() const {
        return weight_;
    }

};


#endif //PHYSIC_OBJECT_HPP
