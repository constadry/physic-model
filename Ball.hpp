//
// Created by behap on 21.03.2021.
//

#ifndef PHYSIC_BALL_HPP
#define PHYSIC_BALL_HPP

#include "Object.hpp"

class Ball : public Object {

private:
    double x_start;
    double y_start;
    double degree_;
    double speed_;

    void change_fly_x(const double &time) {
        double new_x;
        new_x = x_start + speed_ * time * cos(degree_ * M_PI / 180);
        setX(new_x);
    }

    void change_fly_y(const double &time) {
        double new_y;
        new_y = y_start - speed_ * time * sin(degree_ * M_PI / 180) + g * time * time / 2;
        setY(new_y);
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
        hide_start_position();

    }

    void fly(const double &time, Event &event, bool &pr, Clock &clock) {
        change_fly_x(time);
        change_fly_y(time);
        sprite_.setPosition((float) x_, (float) y_);

        if (y_ >= display_height-height_+5) { // земля..
            rebound(speed_); // уменшение скорости по некоторому закону
            set_x_start(x_); // новые стартовые координаты
            set_y_start(y_);
            clock.restart(); // функция координат зависит от времени
        }

        if (speed_ < 2 || x_ > display_width) { // примерная скорость, когда нужно остановиться шарику
            pr = false;
        }
    }

    static void change_speed(Event &event){
        if(event.mouseWheelScroll.delta > 0 && ball_speed < 99) // При кручении колесика вверх delta > 0 -> увеличиваем скорость
            ball_speed++;                                       // Так же макс скорость шарика сейчас 100
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

    void set_degree(const double degree) {
        degree_ = degree;
    }

    double get_degree() const {
        return degree_;
    }

    void set_speed(const double speed) {
        speed_ = speed;
    }

    double get_speed() const {
        return speed_;
    }

};

#endif //PHYSIC_BALL_HPP
