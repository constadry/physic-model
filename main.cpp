#include <SFML/Graphics.hpp>
#include <iostream>
#include <initializer_list>


using namespace sf;
using namespace std;



class Object{
protected:
    float x_, y_, w_, h_;
public:

    String file_;
    Image image_;
    Texture texture_;
    Sprite sprite_;

    Object(const string &File, const float x, const float y, const float width, const float height){
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

    void setX(const float x) {
        x_ = x;
    }

    float getX() const{
        return x_;
    }

    void setY(const float y) {
        y_ = y;
    }

    float getY() const{
        return y_;
    }
};

class Cannon : public Object {
public:
    Cannon(const string &File,
           const float x,
           const float y,
           const float width,
           const float height) :
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
public:
    Ball(const string &File,
           const float x,
           const float y,
           const float width,
           const float height) :
            Object(File, x, y, width, height) {}
//    void fly() {
//
//    }
};

int main() {

    RenderWindow window(VideoMode(640, 480), "My_gun");

    Cannon cannon("guns_4.jpg", 60, 0, -60, 60);
    Ball ball("Ball.png", 0, 0, 31, 31);
//    Object b("lol.jpg", 0, 0, 640, 480);

    cannon.sprite_.setPosition(0, 420);
    ball.image_.createMaskFromColor(Color(0, 0, 0), 100);
    ball.sprite_.setPosition(25, 420);
//    b.sprite_.setPosition(0, 0);

    while (window.isOpen()) {

        Event event{};

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        cannon.move(event);

        window.clear();
        window.draw(cannon.sprite_);
        window.draw(ball.sprite_);
        window.display();
    }

    return 0;
}