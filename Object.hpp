//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_OBJECT_HPP
#define PHYSIC_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Const {
    const double g = 9.80665; // Постоянная g, используется для физики

    const short int help_degree = 18; // Постоянная для Костиных трюков

// Постоянные для формы объктов(ширина и длина спрайтов)
    const int display_width = 640, display_height = 480;
    const int cannon_width = 60, cannon_height = 60;
    const int stand_width = 27, stand_height = 22;
    const int ball_width = 31, ball_height = 31;
    const int back_height = 750;
    const int block_width = 34, block_height = 123;
    const int position_back_y = back_height - display_height;

    const float cannon_position_x = 20, cannon_position_y = 467; // Позиция пушки
    const double den_iron = 7870, den_wood = 530, den_land = 1000; // Видимо плотнось(если что-то поправьте)
    const double k_land = 0.95; // коэффициент восстановления для земли
    const double cannon_len = 30;
    //int block_width = 26, block_height = 98;   ////XZ
}

using namespace sf;
using namespace std;

class Object {
protected:

    double x_in_sprite, y_in_sprite,
            width_, height_,
            x_, y_,
            weight_, // масса объекта, необходимо для расчётов скоростей
            density_, // плотность объекта, нужно для расчета массы
            recovery_coefficient_;  // коэффициент восстановления, нужен для отскока

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
           const double density,
           const double recovery_coefficient = -1) {

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

        recovery_coefficient_ = recovery_coefficient;
    }

    void setX(const double x) {
        x_ = x;
    }

    double getX() const {
        return x_;
    }

    void setY(const double y) {
        y_ = y;
    }

    double getY() const {
        return y_;
    }

    double get_weight() const {
        return weight_;
    }

    double get_height() const {
        return height_;
    }

    double get_coef_rec() const {
        return recovery_coefficient_;
    }

};


#endif //PHYSIC_OBJECT_HPP
