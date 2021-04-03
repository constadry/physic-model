#include <iostream>
#include "Header.hpp"

int main() {

    RenderWindow window(VideoMode(Const::display_width, Const::display_height),"My_gun"); // Создание окна

    Cannon cannon("gun.png",
                  Const::cannon_height,
                  0,
                  -Const::cannon_width,
                  Const::cannon_height,
                  Const::den_iron); // Инициализация объекта "дуло пушки"

    Object stand("stand.png",
                 0,
                 0,
                 Const::stand_width,
                 Const::stand_height,
                 Const::den_iron); // Инициализация объекта "подставка пушки"

    Ball ball("Ball.png",
              0,
              0, Const::ball_width,
              Const::ball_height,
              Const::den_iron); // Инициализация объекта "ядро"

    Object background("[OC] Storm (pixel dailies).png",
                      0,
                      Const::position_back_y,
                      Const::display_width,
                      Const::display_height,
                      0); // Инициализация объекта "фон"

    Block block("block.png",0,0 ,Const::block_width, Const::block_height, Const::den_wood); // Инициализация объекта "ящик"

    Land land("land.bmp",0,0, Const::display_width,6, Const::den_land, Const::k_land);// Инициализация объекта "поверхность"
    Numbers number_of_speed_1("numbers.png", 64, 64, 51, 51, 0); // изначально цифра 7, т.к. ball_speed = 75
    Numbers number_of_speed_2("numbers.png", 10, 10, 51, 51, 0); // изначально цифра 5, т.к. ball_speed = 75

    number_of_speed_2.sprite_.setPosition(51, 0); // Ставим sprite второй цифры на нужную позицию

    stand.sprite_.setPosition(0, (float) Const::display_height - 20);

    cannon.sprite_.setPosition(Const::cannon_position_x, Const::cannon_position_y);
    cannon.setX(Const::cannon_position_x); cannon.setY(Const::cannon_position_y);

    bool pr = false;

    Event event{};
    Clock clock;

    double ball_degree;

    int ball_speed = 75; // стартовое значение

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        double time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        time = time/100000; //скорость игры

        if (!pr) {
            ball_degree = ball.get_degree();
            if (ball_degree > 90) {
                ball_degree = 180 - ball_degree;
                ball.set_degree(ball_degree);
            }
            cannon.move(event, ball);
            if(event.type == Event::MouseWheelScrolled) { // Изменение скорости полета шарика
                Ball::change_speed(event, ball_speed);
            }
            Cannon::shoot(event, clock, pr, ball, ball_degree, ball_speed);
        }

        if (pr) {
            ball.fly(time, event, pr, clock, land, block); // передаю время, чтобы перезапускать его внутри функции
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