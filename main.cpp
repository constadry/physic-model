#include <iostream>
#include "Header.hpp"

int main() {

    RenderWindow window(VideoMode(display_width, display_height), "My_gun");
    Cannon cannon("gun.png", cannon_height, 0, -cannon_width, cannon_height, den_iron);
    Object stand("stand.png", 0, 0, stand_width, stand_height, den_iron);
    Ball ball("Ball.png", 0, 0, ball_width, ball_height, den_iron);
    Object background("[OC] Storm (pixel dailies).png", 0, position_back_y, display_width, display_height, 0);
    Block block("block.png", 0, 0, block_width, block_height, den_wood);
    Land land("land.bmp", 0, 0, display_width, 6, den_land, k_land);

    Numbers number_of_speed_1("numbers.png", 64, 64, 51, 51, 0); // изначально цифра 7, т.к. ball_speed = 75
    Numbers number_of_speed_2("numbers.png", 10, 10, 51, 51, 0); // изначально цифра 5, т.к. ball_speed = 75

    number_of_speed_2.sprite_.setPosition(51, 0); // Ставим sprite второй цифры на нужную позицию

    stand.sprite_.setPosition(0, (float) display_height-20);

    cannon.sprite_.setPosition(cannon_position_x, cannon_position_y);
    cannon.setX(cannon_position_x); cannon.setY(cannon_position_y);

    bool pr = false;

    Event event{};
    Clock clock;

    double ball_degree;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        double time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        time = time/100000; //скорость игры

        if (!pr) {
            cannon.move(event, ball);
            if(event.type == Event::MouseWheelScrolled){ // Изменение скорости полета шарика
                Ball::change_speed(event);
            }
            ball_degree = ball.get_degree();
            Cannon::shoot(event, clock, pr, ball, ball_degree);
        }

        if (pr) {
            ball.fly(time, event, pr, clock, land); // передаю время, чтобы перезапускать его внутри функции
        }

        number_of_speed_1.change_numbers(ball_speed / 10); // Смена первой цифры на экране при изменении скорости шарикка
        number_of_speed_2.change_numbers(ball_speed % 10);// Смена второй цифры на экране при изменении скорости шарикка

        if (Keyboard::isKeyPressed(Keyboard::Escape)) // Окно закрывается при нажатии клавиши esc
            break;

        window.clear();
        window.draw(background.sprite_);
        window.draw(cannon.sprite_);
        window.draw(stand.sprite_);
        window.draw(ball.sprite_);
        window.draw(block.sprite_);
        window.draw(number_of_speed_1.sprite_);
        window.draw(number_of_speed_2.sprite_);
        window.display();
    }

    return 0;
}