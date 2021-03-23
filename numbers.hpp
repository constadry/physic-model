//
// Created by behap on 22.03.2021.
//

#ifndef PHYSIC_NUMBERS_HPP
#define PHYSIC_NUMBERS_HPP

#include "Object.hpp"

class Numbers : public Object{
public:
    Numbers(const string &File,
            const double x,
            const double y,
            const double width,
            const double height,
            const double density) :
            Object(File, x, y, width, height, density) {} // Конструктор класса Numbers

    void change_numbers(int number){ // Смена циферок на экране при изменении скорости шарикка
        switch (number) {
            case 0:
            {
                x_in_sprite = 10;
                y_in_sprite = 10;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 1:
            {
                x_in_sprite = 10;
                y_in_sprite = 64;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 2:
            {
                x_in_sprite = 10;
                y_in_sprite = 118;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 3:
            {
                x_in_sprite = 10;
                y_in_sprite = 172;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 4:
            {
                x_in_sprite = 64;
                y_in_sprite = 10;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 5:
            {
                x_in_sprite = 118;
                y_in_sprite = 10;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 6:
            {
                x_in_sprite = 172;
                y_in_sprite = 10;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 7:
            {
                x_in_sprite = 64;
                y_in_sprite = 64;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 8:
            {
                x_in_sprite = 64;
                y_in_sprite = 118;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            case 9:
            {
                x_in_sprite = 64;
                y_in_sprite = 172;
                sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
                break;
            }
            default:  // Если вдруг скорость вышла за пределы
            {
                cout << "Error";
            }
        }
    }
};

#endif //PHYSIC_NUMBERS_HPP
