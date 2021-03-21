//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_CANNON_HPP
#define PHYSIC_CANNON_HPP

#include "Ball.hpp"

class Cannon : public Object {
private:
    const float center_x = 20, center_y = 48;
public:

    Cannon(const string &File,
           const double x,
           const double y,
           const double width,
           const double height,
           const double density) :
            Object(File, x, y, width, height, density) {
        sprite_.setOrigin(center_x, center_y);
        sprite_.rotate(help_degree);
    }

    void move(Event &event, Ball &ball) {

        static bool move_pr = false;

        double ball_degree;

        if (!move_pr) //переменная, определяющая "нажатость" клавиши
        {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                sprite_.rotate(-0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - help_degree)), 360);
                ball.set_degree(ball_degree);
                move_pr = true; //Изменяется когда нажали
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                sprite_.rotate(0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - help_degree)), 360);
                ball.set_degree(ball_degree);
                move_pr = true; //Изменяется когда нажали
            }
        } else if (event.type == Event::KeyPressed) move_pr = false; //Изменяется, когда отпустили
    }
};

#endif //PHYSIC_CANNON_HPP
