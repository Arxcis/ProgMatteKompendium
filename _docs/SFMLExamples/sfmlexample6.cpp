/*

Example 6:

Simple movement using keyboard as input

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

float abs(sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

const float maxSpeed = 1000;

class Player
{
public:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float angle = -3.1415/2;
    float angVel = 0;

    sf::CircleShape shape;

    Player();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

Player::Player()
{
    shape.setRadius(10);
    shape.setPointCount(3);
    shape.setOrigin(10,10);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(sf::Vector2f(0,0));
}

void Player::update(float dt)
{
    // integrate velocity
    vel += dt * acc;

    // interpolate to 0 - damping
    vel *= (1-dt);

    // cap velocity to maxSpeed
    if(abs(vel) > maxSpeed) {
        vel = vel * (maxSpeed / abs(vel));
    }

    // integrate position
    pos += dt * vel;

    // integrate angle
    angle += dt * angVel;

    // reset forces
    acc = sf::Vector2f(0,0);
    angVel = 0;

    // simple collision detecting which could be done elsewhere
    if(pos.x < -256) {
        pos.x = -256;
        vel.x = -vel.x;
    }

    if(pos.x > 256) {
        pos.x = 256;
        vel.x = -vel.x;
    }

    if(pos.y < -256) {
        pos.y = -256;
        vel.y = -vel.y;
    }

    if(pos.y > 256) {
        pos.y = 256;
        vel.y = -vel.y;
    }
}

void Player::draw(sf::RenderWindow& w)
{
    shape.setRotation(90+angle*180/3.1415);
    shape.setPosition(pos);
    w.draw(shape);
}


int main()
{
    // We create a square window
    // Change windowSize if you want a different sized window
    int windowSize = 512;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Example 1");

    // We create a view of the world - think of this as setting up the camera
    sf::Vector2f viewOrigin(0,0);
    sf::Vector2f viewSize(512,512);
    sf::View view(viewOrigin, viewSize);
    window.setView(view);


    // Change currentObject for different behaviour
    //
    // 0: adjust velocity if key is pressed
    // 1: adjust accelleration if key is pressed
    // 2: with gravity
    // 3: Astroid like
    // 4: Using mouse
    int currentObject = 4;
    Player object[10];

    sf::Clock clock;

    // reset timer to 0
    clock.restart();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // get time since last frame
        float dt = clock.restart().asSeconds();

        // apply forces (or change velocities)
        // 0: adjust velocity if key is pressed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            object[0].vel.y = -50;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            object[0].vel.y = 50;
        } else object[0].vel.y = 0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            object[0].vel.x = -50;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            object[0].vel.x = 50;
        } else object[0].vel.x = 0;

        // 1: adjust accelleration if key is pressed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            object[1].acc.y = -300;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            object[1].acc.y = 300;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            object[1].acc.x = -300;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            object[1].acc.x = 300;
        }

        // 2: as 1 but with gravity
        // The first part is as for 1 above
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            object[2].acc.y = -300;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            object[2].acc.y = 300;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            object[2].acc.x = -300;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            object[2].acc.x = 300;
        }

        // gravity
        object[2].acc += sf::Vector2f(0,200);



        // 3: Astroids
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            object[3].acc = 300.0f*sf::Vector2f(cos(object[3].angle),sin(object[3].angle));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            object[3].angVel = -3.1415/4;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            object[3].angVel = 3.1415/4;
        }

        // gravity
        object[3].acc += sf::Vector2f(0,200);


        // 4: To mouse position
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2i mousePosScreen = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosScreen);
            sf::Vector2f diff = sf::Vector2f(mousePos.x,mousePos.y)-object[4].pos;
            float d = abs(diff);
            if(d > 10) {
                object[4].acc = 300.0f*diff / d;
            }
        }



        // integrate
        for(int i = 0; i < 10; i++) {
            object[i].update(dt);
        }

        // render
        window.clear(sf::Color::Black);
        object[currentObject].draw(window);
        window.display();
    }

    return 0;
}



