#include <iostream>
#include "Header.hpp"

int main() {
    RenderWindow window(VideoMode(display_width, display_height), "My_gun");
    Cannon cannon("gun.png", cannon_height, 0, -cannon_width, cannon_height, den_iron);
    Object stand("stand.png", 0, 0, stand_width, stand_height, den_iron);
    Ball ball("Ball.png", 0, 0, ball_width, ball_height, den_iron);
    Object background("[OC] Storm (pixel dailies).png", 0, position_back_y, display_width, display_height, 0);
    Block block("block.png", 0, 0, block_width, block_height, den_wood);

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

        double time = clock.getElapsedTime().asMilliseconds(); //дать прошедшее время в микросекундах
        time = time/100; //скорость игры

        if (!pr) {
            cannon.move(event, ball);
            ball_degree = ball.get_degree();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                pr = true;
                ball.setX(cannon_position_x - 20 + cannon_len*cos(ball_degree * M_PI / 180));
                ball.setY(cannon_position_y - 22 - cannon_len*sin(ball_degree * M_PI / 180));
                ball.set_x_start(cannon_position_x - 20 + cannon_len*cos(ball_degree * M_PI / 180));
                ball.set_y_start(cannon_position_y - 22 - cannon_len*sin(ball_degree * M_PI / 180));
                ball.set_degree(ball_degree);
                ball.set_speed(ball_speed);
                clock.restart();
            }
        }

        if (pr) {
            ball.fly(time, event, pr, clock); // передаю время, чтобы перезапускать его внутри функции
        }

        window.clear();
        window.draw(background.sprite_);
        window.draw(cannon.sprite_);
        window.draw(stand.sprite_);
        window.draw(ball.sprite_);
        window.draw(block.sprite_);
        window.display();
    }

    return 0;
}