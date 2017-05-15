#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class Ball
{
public:
    sf::Vector2f pos;
    sf::Vector2f vel; // per second
    float radius;

    Ball();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};



Ball::Ball()
{
    pos = sf::Vector2f(256,256);
    vel = sf::Vector2f(45,-50);
    radius = 30;
}



void Ball::update(float dt)
{
    // Physics
    pos += vel * dt;

    // Collision test and resolution
    if(pos.x > 512 - radius) {
        pos.x = 512 - radius;
        vel.x = -vel.x;
    } else if(pos.x < radius) {
        pos.x = radius;
        vel.x = -vel.x;
    }


    if(pos.y > 512 - radius) {
        pos.y = 512 - radius;
        vel.y = -vel.y;
    } else if(pos.y < radius) {
        pos.y = radius;
        vel.y = -vel.y;
    }
}

void Ball::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(radius);
    s.setOrigin(radius,radius);
    s.setPosition(pos);
    s.setFillColor(sf::Color::Red);
    w.draw(s);
}


class KeyboardBall : public Ball
{
public:
    void update(float dt);
};


void KeyboardBall::update(float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        pos.y -= dt * 100;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        pos.x -= dt * 100;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pos.y += dt * 100;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        pos.x += dt * 100;
    }

     // Collision test and resolution
    if(pos.x > 512 - radius) {
        pos.x = 512 - radius;
    } else if(pos.x < radius) {
        pos.x = radius;
    }


    if(pos.y > 512 - radius) {
        pos.y = 512 - radius;
    } else if(pos.y < radius) {
        pos.y = radius;
    }

}


class MouseBall : public Ball
{
public:
    void update(float dt, sf::RenderWindow& w);
};



void MouseBall::update(float dt, sf::RenderWindow& w)
{
    Ball::update(dt);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
       sf::Vector2i mousePos = sf::Mouse::getPosition(w);
       pos = w.mapPixelToCoords(mousePos);
    }

}


//
// Basic SFML + game loop
//

using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Window");

    // window.setVerticalSyncEnabled(true);  // Prevent tearing at high framerates

    // We need to tell the time
    sf::Clock clock;
    clock.restart();

    // We need to draw something
    Ball ball;
    KeyboardBall ball2;
    MouseBall ball3;


    //
    // SIMPLE GAME LOOP
    //


    // run the program as long as the window is open
    while (window.isOpen())
    {
        //
        // GAME LOOP STEP 1:  PROCESS INPUT
        //

        sf::Event event;

        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))  {

        // check the type of the event...
        switch (event.type)  {

            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // we don't process other types of events
            default:
                break;

            }
        }

        //
        // GAME LOOP STEP 2: UPDATE STATE
        //

        // find elapsed time
        float dt = clock.restart().asSeconds();
        // do some AI

        // do some physics
        ball.update(dt);
        ball2.update(dt);
        ball3.update(dt,window);


        //
        // GAME LOOP STEP 3: RENDER
        //
        window.clear(sf::Color::Black);
        ball.draw(window);
        ball2.draw(window);
        ball3.draw(window);
        window.display();
    }

    return 0;
}



/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Window");

    window.setVerticalSyncEnabled(true);  // Prevent tearing at high framerates

    // We need to tell the time
    sf::Clock clock;
    clock.restart();
    float dt = 0;

    // We need to draw something
    Ball ball;


    //
    // GAME LOOP: FIXED STEP 1/60 ON PHYSICS BUT RENDERS AT MAX
    //


    // run the program as long as the window is open
    while (window.isOpen())
    {
        //
        // GAME LOOP STEP 1:  PROCESS INPUT
        //

        sf::Event event;

        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))  {

        // check the type of the event...
        switch (event.type)  {

            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // we don't process other types of events
            default:
                break;

            }
        }

        //
        // GAME LOOP STEP 2: UPDATE STATE
        //

        // find elapsed time
        dt += clock.restart().asSeconds();

        while(dt > 1/60.0) {
            // do some physics
            ball.update(1/60.0);
            dt -= 1/60.0;
        }

        //
        // GAME LOOP STEP 3: RENDER
        //
        window.clear(sf::Color::Black);
        ball.draw(window);
        window.display();
    }

    return 0;
}

*/
