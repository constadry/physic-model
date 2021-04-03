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
        sprite_.rotate(Const::help_degree);
    }

    void move(Event &event, Ball &ball) {
        double ball_degree;
        if (ball.get_degree() < 90) {
            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
                sprite_.rotate(-0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - Const::help_degree)), 360);
                ball.set_degree(ball_degree);
            }
        }
        if (ball.get_degree() > 0) {
            if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
                sprite_.rotate(0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - Const::help_degree)), 360);
                ball.set_degree(ball_degree);
            }
        }
    }

    static void shoot(Event &event, Clock &clock, bool &pr, Ball &ball, double &ball_degree, const int ball_speed) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                pr = true;
                ball.set_status_rebound();
                ball.setX(Const::cannon_position_x - 20 + Const::cannon_len * cos(ball_degree * M_PI / 180));
                ball.setY(Const::cannon_position_y - 22 - Const::cannon_len * sin(ball_degree * M_PI / 180));
                ball.set_x_start(Const::cannon_position_x - 20 + Const::cannon_len * cos(ball_degree * M_PI / 180));
                ball.set_y_start(Const::cannon_position_y - 22 - Const::cannon_len * sin(ball_degree * M_PI / 180));
                ball.set_degree(ball_degree);
                ball.set_speed(ball_speed);
                ball.set_speed_start(ball_speed);
                clock.restart();
            }
        }
    }
};

#endif //PHYSIC_CANNON_HPP
