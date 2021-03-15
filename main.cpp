#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

const double g = 9.80665;
const short int help_degree = 18;

class Object {
protected:

    double x_in_sprite, y_in_sprite,
            width_, height_,
            x_, y_;

public:

    String file_;
    Image image_;
    Texture texture_;
    Sprite sprite_;

    Object(const string &File, const double x, const double y, const double width, const double height) {
        file_ = File;
        width_ = width;
        height_ = height;

        image_.loadFromFile("images/" + file_);
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);

        x_in_sprite = x;
        y_in_sprite = y;

        sprite_.setTextureRect(IntRect(x_in_sprite, y_in_sprite, width_, height_));
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
};

class Cannon : public Object {
private:
    const float center_x = 20, center_y = 48;
public:

    Cannon(const string &File,
           const double x,
           const double y,
           const double width,
           const double height) :
            Object(File, x, y, width, height) {
        sprite_.setOrigin(center_x, center_y);
        sprite_.rotate(help_degree);
    }

    void move(Event &event, double &ball_degree) {

        static bool move_pr = false;

        if (!move_pr) //переменная, определяющая "нажатость" клавиши
        {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                sprite_.rotate(-0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - help_degree)), 360);
                move_pr = true; //Изменяется когда нажали
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                sprite_.rotate(0.1);
                ball_degree = fmod((360 - (sprite_.getRotation() - help_degree)), 360);
                move_pr = true; //Изменяется когда нажали
            }
        } else if (event.type == Event::KeyPressed) move_pr = false; //Изменяется, когда отпустили
    }
};

class Ball : public Object {

private:
    double x_start;
    double y_start;
    double degree_;

    void change_fly_x(const double &time, double degree, double speed) {
        double new_x;
        new_x = x_start + speed * time * cos(degree * M_PI / 180);
        setX(new_x);
    }

    void change_fly_y(const double &time, double degree, double speed) {
        double new_y;
        new_y = y_start - speed * time * sin(degree * M_PI / 180) + g * time * time / 2;
        setY(new_y);
    }

public:

    Ball(const string &File,
         const double x,
         const double y,
         const double width,
         const double height) :
            Object(File, x, y, width, height) {}

    void fly(const double &time, double degree, double speed, const double display_height, const double ball_height, Event &event, bool &pr) {
        if (y_ < display_height-ball_height+5) {
            change_fly_x(time, degree, speed);
            change_fly_y(time, degree, speed);
            sprite_.setPosition((float) x_, (float) y_);
        } else {
            pr = false;
        }
    }

    void set_x_start(const double x) {
        x_start = x;
    }

    void set_y_start(const double y) {
        y_start = y;
    }

};

int main() {

    int display_width = 640, display_height = 480;
    int cannon_width = 60, cannon_height = 60;
    int stand_width = 27, stand_height = 22;
    int ball_width = 31, ball_height = 31;
    int back_height = 750;
    int position_back_y = back_height - display_height;

    RenderWindow window(VideoMode(display_width, display_height), "My_gun");
    Cannon cannon("gun.png", 60, 0, -cannon_width, cannon_height);
    Object stand("stand.png", 0, 0, stand_width, stand_height);
    Ball ball("Ball.png", 0, 0, ball_width, ball_height);
    Object background("[OC] Storm (pixel dailies).png", 0, position_back_y, display_width, display_height);

    stand.sprite_.setPosition(0, (float) display_height-20);

    float cannon_position_x = 20, cannon_position_y = 467;

    cannon.sprite_.setPosition(cannon_position_x, cannon_position_y);
    cannon.setX(cannon_position_x);
    cannon.setY(cannon_position_y);

    ball.sprite_.setPosition(-25, -25);
    ball.set_x_start(cannon_position_x); ball.set_y_start(cannon_position_y);

    bool pr = false;

    Event event{};
    Clock clock;
    const double cannon_len = 30;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        double time = clock.getElapsedTime().asMilliseconds(); //дать прошедшее время в микросекундах
        time = time/100; //скорость игры

        double ball_degree;
        if (!pr) {
            cannon.move(event, ball_degree);
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
                clock.restart();
            }
        }

        if (pr) {
            ball.fly(time, ball_degree, 50, display_height, ball_height, event, pr);
        }

        window.clear();
        window.draw(background.sprite_);
        window.draw(cannon.sprite_);
        window.draw(stand.sprite_);
        window.draw(ball.sprite_);
        window.display();
    }

    return 0;
}