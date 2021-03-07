#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Object{
protected:
    double x_, y_, w_, h_;
public:

    String file_;
    Image image_;
    Texture texture_;
    Sprite sprite_;

    Object(const string &File, const double x, const double y, const double width, const double height){
        file_ = File;
        w_ = width;
        h_ = height;

        image_.loadFromFile("images/" + file_);
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);

        x_ = x;
        y_ = y;

        sprite_.setTextureRect(IntRect(x_, y_, w_, h_));
    }

    void setX(const double x) {
        x_ = x;
    }

    double getX() const{
        return x_;
    }

    void setY(const double y) {
        y_ = y;
    }

    double getY() const{
        return y_;
    }
};

class Cannon : public Object {
public:
    Cannon(const string &File,
           const double x,
           const double y,
           const double width,
           const double height) :
           Object(File, x, y, width, height) {}
    void move(Event &event) {

        static bool pr = false;

        if (!pr) //переменная, определяющая "нажатость" клавиши
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if(y_ == 120){
                    y_ = 0;
                } else{
                    y_ += 60;
                }
                sprite_.setTextureRect(IntRect(60, y_, -60, 60));
                pr = true; //Изменяется когда нажали
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if(y_ == 0){
                    y_ = 120;
                } else{
                    y_ -= 60;
                }
                sprite_.setTextureRect(IntRect(60, y_, -60, 60));
                pr = true; //Изменяется когда нажали
            }
        }
        else if (event.type == Event::KeyReleased) pr = false; //Изменяется, когда отпустили
    }
};

class Ball : public Object {
private:
    const double g = 9.80665;
    double x_start;
    double y_start;
    void change_fly_x(const double &time, double degree, double speed) {
        double new_x;
        new_x = x_start + speed*time*cos(degree*M_PI/180);
        setX(new_x);
    }
    void change_fly_y(const double &time, double degree, double speed) {
        double new_y;
        new_y = y_start - speed*time*sin(degree*M_PI/180) + g*time*time/2;
        setY(new_y);
    }
public:
    Ball(const string &File,
         const double x,
         const double y,
         const double width,
         const double height) :
            Object(File, x, y, width, height) {
        x_start = 41;
        y_start = 435;
    }
    void fly(const double &time, double degree, double speed) {
        change_fly_x(time, degree, speed);
        change_fly_y(time, degree, speed);
        sprite_.setPosition((float) x_, (float) y_);
    }
};

int main() {

    RenderWindow window(VideoMode(640, 480), "My_gun");

    Cannon cannon("guns_3.png", 60, 0, -60, 60);
    Ball ball("Ball.png", 0, 0, 31, 31);
    Object background("[OC] Storm (pixel dailies).png", 0, 270, 640, 480);

    cannon.sprite_.setPosition(0, 420);
    ball.sprite_.setPosition(41, 435);
    ball.setX(41); ball.setY(435);
    background.sprite_.setPosition(0, 0);

    Event event{};
    Clock clock;
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        double time = clock.getElapsedTime().asMilliseconds(); //дать прошедшее время в микросекундах
//        clock.restart(); //перезагружает время
        time = time/400; //скорость игры
        cout << time << endl;

        cannon.move(event);
        if (ball.getY() < 454) {
            ball.fly(time, 70, 80);
        }
        window.clear();
        window.draw(background.sprite_);
        window.draw(cannon.sprite_);
        window.draw(ball.sprite_);
        window.display();
    }

    return 0;
}