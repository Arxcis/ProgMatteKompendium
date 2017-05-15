#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>


using namespace std;


//
// Drawing the super formula
//

// a,b are both positive numbers
//
float a = 2;
float b = 2;


float n = 3;  // n = m is the number of sectors we divide the plane into
float m = n;  // we assume m = n for simplicity

// cycles = 1,2 gives basic pattern, the rest are symmetric copies
// cycles = n is once around the circle
// cycles 2*n should be once around the pattern
float cycles = 6;


//
//
//
//
//
// No effect of terms
// float n1 = -1
// float n2 = 1
// float n3 = 1

// larger n1 tend to make rounder shapes
float n1 = 2;
float n2 = 3;
float n3 = 3;

float f(float theta)
{
    return pow(pow(abs(cos(n*theta/4)/a),n2) + pow(abs(sin(m*theta/4)/b),n3), -1/n1);
}

float rad = 5;

void superformula(float x, float y, sf::RenderWindow& window)
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sf::Vector2i mpos = sf::Mouse::getPosition(window);
        n2 = mpos.x / 20.0;
        n3 = mpos.y / 20.0;
        cout << "n2=" << " " << n2 << " " << "n3= " << n3 << endl;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        sf::Vector2i mpos = sf::Mouse::getPosition(window);
        a = mpos.x / 20.0;
        b = mpos.y / 20.0;
        cout << "a=" << " " << a << " " << "b= " << b << endl;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        sf::Vector2i mpos = sf::Mouse::getPosition(window);
        n1 = mpos.x / 30.0;
        cout << "n1=" << " " << n1 <<  endl;
    }

    sf::CircleShape c;
    c.setOrigin(rad,rad);
    c.setFillColor(sf::Color::Yellow);
    c.setRadius(rad);

    float maxv = -100000;

    for(float theta = 0; theta < cycles*2*3.1415/n; theta += 0.001) {
        float v = f(theta);

        if(maxv < v) maxv = v;
    }

    for(float theta = 0; theta < cycles*2*3.1415/n; theta += 0.001) {
        float v = f(theta)/maxv;
        c.setPosition(sf::Vector2f(cos(theta)*v*200 + x, sin(theta)*v*200 + y));
        window.draw(c);
    }


}



int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "My window");
   /* sf::View view(sf::FloatRect(-10,-10,10,10));
    window.setView(view);*/

    sf::Clock clock;
    clock.restart();
    float t = 0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        t += clock.restart().asSeconds();

        window.clear(sf::Color::Black);


        superformula(256,256,window);

        window.display();
    }

    return 0;
}

