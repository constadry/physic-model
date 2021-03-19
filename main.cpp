#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

const double g = 9.80665;
const short int help_degree = 18;

int display_width = 640, display_height = 480;
int cannon_width = 60, cannon_height = 60;
int stand_width = 27, stand_height = 22;
int ball_width = 31, ball_height = 31;
int back_height = 750;
int block_width = 34, block_height = 123;

int position_back_y = back_height - display_height;
float cannon_position_x = 20, cannon_position_y = 467;

const double den_iron = 7870, den_wood = 530, den_land = 1000;

int ball_speed = 75; // позже необходимо реализовать изменение скорости прямо внутри приложения

const double cannon_len = 30;

class Object {
protected:

    double x_in_sprite, y_in_sprite,
            width_, height_,
            x_, y_,
            weight_, density_;

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
           const double density) {

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
    }

    void setX(const double x) {
        x_ = x;
    }

//    double getX() const {
//        return x_;
//    }

    void setY(const double y) {
        y_ = y;
    }

//    double getY() const {
//        return y_;
//    }

    static void rebound(double &speed) {
        speed = speed*sqrt(0.7);
    }

    double get_weight() const {
        return weight_;
    }

};

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

        if (y_ >= display_height-height_+5) {
            rebound(speed_);
            set_x_start(x_);
            set_y_start(y_);
            clock.restart();
        }

        if (speed_ < 2 || x_ > display_width) {
            pr = false;
        }
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

    void set_speed(const double speed) {
        speed_ = speed;
    }

    double get_degree() const {
        return degree_;
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

class Block : public Object {
public:
    Block(const string &File,
           const double x,
           const double y,
           const double width,
           const double height,
           const double density) :
            Object(File, x, y, width, height, density) {
        sprite_.setPosition((float) 200, (float) (display_height - block_height));
    }
};

class Land : public Object {
public:
    Land(const string &File,
          const double x,
          const double y,
          const double width,
          const double height,
          const double density) :
            Object(File, x, y, width, height, density) {}
};

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

    cout << ball.get_weight();

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
            ball.fly(time, event, pr, clock);
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