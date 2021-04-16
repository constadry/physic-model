//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_BALL_HPP
#define PHYSIC_BALL_HPP

#include "Object.hpp"
#include "Land.hpp"
#include "Block.hpp"

class Ball : public Object {

private:
    double x_start;
    double y_start;
    double degree_;
    double speed_;
    double speed_start_;
    double speed_in_time_of_rebound;
    bool reb_was = false;

    void change_fly_x(const double &time) {
        double new_x;
        new_x = x_start + speed_start_ * time * cos(degree_ * M_PI / 180);
        setX(new_x);
    }

    void change_fly_y(const double &time) {
        double new_y;
        new_y = y_start
                - speed_start_ * time * sin(degree_ * M_PI / 180)
                + Const::g * time * time / 2;
        setY(new_y);
    }

    void change_speed(const double &time) {
        speed_ = sqrt(pow(speed_start_ * cos(degree_ * M_PI / 180), 2)
                + pow((speed_start_ * sin(degree_ * M_PI / 180)
                - Const::g * time), 2));
    }

    double dot_prod_with(const Object &object) {
        double ball_vx = x_ - object.getX() + 22;
        double ball_vy = y_ - object.getY() + 22;
        double block_vx = 0; // перпендикулярен земле
        double block_vy = -object.getY();

        return ball_vx*block_vx + ball_vy*block_vy;
    }

    double triangular_height(const Object &object) {
        double height, ox, oy;

        ox = object.getX() - 22; // поправка на размер шара
        oy = object.getY() - 23;

        double ball_vx_1 = ox - x_;
        double ball_vy_1 = oy - y_;

        double ball_vx_2 = ox - x_;
        double ball_vy_2 = Const::display_height - y_;

        double a = sqrt(pow(ball_vx_1, 2) + pow(ball_vy_1, 2));
        double b = sqrt(pow(ball_vx_2, 2) + pow(ball_vy_2, 2));

        double cos_a_b = (ball_vx_1 * ball_vx_2 + ball_vy_1 * ball_vy_2) / (a * b);

        double sin_a_b = sqrt(1 - pow(cos_a_b, 2));

        height = sin_a_b * a * b / object.get_height();

        return height;
    }

public:

    Ball(const string &File,
         const double x,
         const double y,
         const double width,
         const double height,
         const double density) :
            Object(File, x, y, width, height, density) {

        x_start = 0;
        y_start = 0;
        degree_ = 0;
        speed_ = 0;
        speed_start_ = 0;
        hide_start_position();

    }

    void fly(const double &time,
             Event &event,
             bool &pr,
             Clock &clock,
             const Land &land,
             const Block &block,
             bool &falling_ball) {

        change_fly_x(time);
        change_fly_y(time);
        change_speed(time);
        sprite_.setPosition((float) x_, (float) y_);

        if (y_ >= Const::display_height - height_ + 5) { // земля..
            rebound(clock, land);
        }

        if (!reb_was) {
            if (dot_prod_with(block) < 0.0) {
                if (triangular_height(block) <= 1.5) {
                    speed_in_time_of_rebound = speed_;
                    rebound(clock, block);
                    degree_ = 180 - degree_;
                    reb_was = true;
                    falling_ball = true;
                }
            } else {
                if (block.getY() - y_ - 22 <= 1.5 && x_ + 12 < block.getX() + 32 && x_ + 19 > block.getX()) {
                    rebound(clock, block);
                    speed_ += 5;
                    speed_start_ += 5;
                }
            }
        }

        if (speed_start_ < 0.05 || x_ > Const::display_width || x_ < 0) { // примерная скорость, когда нужно остановиться шарику
            pr = false;
        }

    }

    static void change_speed(Event &event, int& ball_speed) {
        if(event.mouseWheelScroll.delta > 0 && ball_speed < 99) // При кручении колесика вверх delta > 0 -> увеличиваем скорость
            ball_speed++;                                      // Так же макс скорость шарика сейчас 100
        else if(event.mouseWheelScroll.delta < 0 && ball_speed > 20) // Аналогично уменьшаем скорость до 20(минимум)
            ball_speed--;
        event.mouseWheelScroll.delta = 0;
    }

    void hide_start_position() {
        sprite_.setPosition(-25, -25);
    }

    void set_x_start(const double x) {
        x_start = x;
    }

    void set_y_start(const double y) {
        y_start = y;
    }

    void set_speed_start(const double speed) {
        speed_start_ = speed;
    }

    void set_degree(const double degree) {
        degree_ = degree;
    }

    double get_degree() const {
        return degree_;
    }

    void set_speed(const double speed) {
        speed_ = speed;
    }

    void set_status_rebound() {
        if (reb_was) {
            reb_was = false;
        }
    }

    double get_speed() const {
        return speed_;
    }

    double get_speed_reb() const {
        return speed_in_time_of_rebound;
    }

    void less_speed(const Object &object) {
        speed_ = speed_ - (1 + object.get_coef_rec())
                * object.get_weight() * speed_
                / (object.get_weight() + weight_);
    }

    void rebound(Clock &clock, const Object &object) {
        less_speed(object); // уменшение скорости по некоторому закону
        set_x_start(x_); // новые стартовые координаты
        set_y_start(y_);
        set_speed_start(speed_);
        clock.restart(); // функция координат зависит от времени
    }

};

#endif //PHYSIC_BALL_HPP
