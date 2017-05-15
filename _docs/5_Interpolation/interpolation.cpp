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
    float t;
    bool state;

    Ball();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};



Ball::Ball()
{
    pos = sf::Vector2f(0,0);
    vel = sf::Vector2f(0,0);
    radius = 30;
    t = 0;
    state = true;
}

void Ball::update(float dt)
{
    if(state) {
       t += dt;
       if(t > 1) {
            t = 1;
            state = false;
       }
    }
    else {
        t-= dt;
        if(t < 0) {
            t = 0;
            state = true;
        }
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



class LerpBall : public Ball
{
public:
    sf::Vector2f P0,P1;
    LerpBall();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

LerpBall::LerpBall()
{
    P0 = sf::Vector2f(100,100);
    P1 = sf::Vector2f(300,400);
}

void LerpBall::draw(sf::RenderWindow& w)
{
    Ball::draw(w);
    sf::CircleShape s;
    s.setRadius(radius/2);
    s.setOrigin(radius/2,radius/2);
    s.setPosition(P0);
    s.setFillColor(sf::Color::Yellow);
    w.draw(s);
    s.setPosition(P1);
    w.draw(s);
}

void LerpBall::update(float dt)
{
    Ball::update(dt);

    pos = (1-t)*P0 + t*P1;

    //float PI = 3.1415;
    //pos = cos(PI*t/2)*cos(PI*t/2)*P0 + sin(PI*t/2)*sin(PI*t/2)*P1;

    //pos = (1-t*t)*P0 + t*t*P1;

    // Slerp
    //sf::Vector2f middle = sf::Vector2f(256,256);
    //sf::Vector2f v1 = P0 - middle;
    //float lv1 = sqrt(v1.x*v1.x+v1.y*v1.y);
    //sf::Vector2f v2 = P1 - middle;
    //float lv2 = sqrt(v2.x*v2.x+v2.y*v2.y);
    //float dot = v1.x*v2.x + v1.y*v2.y;
    //float angle = acos(dot/(lv1*lv2));
    //pos = (sin((1-t)*angle)/sin(angle))*v1 + (sin(t*angle)/sin(angle))*v2+middle;

}


class QuadraticBezierBall : public Ball
{
public:
    sf::Vector2f P0,P1,P2;
    QuadraticBezierBall();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

QuadraticBezierBall::QuadraticBezierBall()
{
    P0 = sf::Vector2f(100,100);
    P1 = sf::Vector2f(400,100);
    P2 = sf::Vector2f(300,400);
}

void QuadraticBezierBall::update(float dt)
{
    Ball::update(dt);

    pos = (1-t)*(1-t)*P0 + 2*(1-t)*t*P1+t*t*P2;

    //float PI = 3.1415;
    //pos = pow(cos(PI*t/2),4)*P0 +
    //     2*cos(PI*t/2)*cos(PI*t/2)*sin(PI*t/2)*sin(PI*t/2)*P1+
    //     pow(sin(PI*t/2),4)*P2;

    // pos = (1-t*t)*(1-t*t)*P0 + 2*(1-t*t)*t*t*P1+t*t*t*t*P2;
}


void QuadraticBezierBall::draw(sf::RenderWindow& w)
{
    Ball::draw(w);
    sf::CircleShape s;
    s.setRadius(radius/2);
    s.setOrigin(radius/2,radius/2);
    s.setPosition(P0);
    s.setFillColor(sf::Color::Yellow);
    w.draw(s);
    s.setPosition(P1);
    w.draw(s);
    s.setPosition(P2);
    w.draw(s);
}



class CubicBezierBall : public Ball
{
public:
    sf::Vector2f P0,P1,P2,P3;
    CubicBezierBall();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

CubicBezierBall::CubicBezierBall()
{
    P0 = sf::Vector2f(100,100);
    P1 = sf::Vector2f(400,100);
    P2 = sf::Vector2f(100,400);
    P3 = sf::Vector2f(300,400);
}

void CubicBezierBall::update(float dt)
{
    Ball::update(dt);
    pos = (1-t)*(1-t)*(1-t)*P0 + 3*(1-t)*(1-t)*t*P1+3*(1-t)*t*t*P2+t*t*t*P3;

    //float PI = 3.1415;
    //pos = pow(cos(PI*t/2),6)*P0 +
    //      3*pow(cos(PI*t/2),4)*sin(PI*t/2)*sin(PI*t/2)*P1+
    //      3*pow(sin(PI*t/2),4)*cos(PI*t/2)*cos(PI*t/2)*P2+
    //      pow(sin(PI*t/2),6)*P3;

    // pos = (1-t*t)*(1-t*t)*(1-t*t)*P0 + 3*(1-t*t)*(1-t*t)*t*t*P1+(1-t*t)*t*t*t*t*P2+pow(t,6)*P3;
}

void CubicBezierBall::draw(sf::RenderWindow& w)
{
    Ball::draw(w);
    sf::CircleShape s;
    s.setRadius(radius/2);
    s.setOrigin(radius/2,radius/2);
    s.setPosition(P0);
    s.setFillColor(sf::Color::Yellow);
    w.draw(s);
    s.setPosition(P1);
    w.draw(s);
    s.setPosition(P2);
    w.draw(s);
    s.setPosition(P3);
    w.draw(s);
}






int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Window");

    // window.setVerticalSyncEnabled(true);  // Prevent tearing at high framerates

    // We need to tell the time
    sf::Clock clock;
    clock.restart();

    // We need to draw something
    LerpBall ball;



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
        ball.update(0.5*dt);


        //
        // GAME LOOP STEP 3: RENDER
        //
        window.clear(sf::Color::Black);
        ball.draw(window);
        window.display();
    }

    return 0;
}


