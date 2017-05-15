/*
Example 1:

Setting up a game loop and drawing something

*/


#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    // We create a square window
    // Change windowSize if you want a different sized window
    int windowSize = 512;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Example 1");

    // We create a view of the world - think of this as setting up the camera
    sf::Vector2f viewOrigin(0,0);
    sf::Vector2f viewSize(1024,1024);
    sf::View view(viewOrigin, viewSize);
    window.setView(view);


    // We create some shapes
    sf::CircleShape circle;
    circle.setOrigin(100,100);
    circle.setRadius(100);
    // due to setOrigin above, this is the position of the center of the circle
    circle.setPosition(0,0);
    circle.setFillColor(sf::Color::Yellow);


    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setSize(sf::Vector2f(100,200));
    // due to lack of setOrigin, this is the upper left corner
    rectangle.setPosition(-200,-200);
    rectangle.rotate(45);


    sf::CircleShape triangle;
    // a triangle is a circle with three points
    triangle.setPointCount(3);
    triangle.setOrigin(200,200);
    triangle.setRadius(200);
    triangle.setPosition(100,-200);
    // This time in RGBA format
    triangle.setFillColor(sf::Color(255,255,255,255));


    sf::RectangleShape thickline;
    thickline.rotate(-30);
    thickline.setSize(sf::Vector2f(150,10));
    thickline.setFillColor(sf::Color::Green);
    thickline.setPosition(-250,-250);




    // Game loop - runs until you close the window
    while (window.isOpen())
    {

        // Remove events from the event-queue
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Note: We will be drawing once to a closed window - but nothing bad seems to happen.
            if (event.type == sf::Event::Closed)
                window.close();

            // Other events - none here

        }
        //
        // Physics and AI - empty here:
        //

        //
        // Rendering:
        //

        // Clear buffer
        window.clear();

        // Change view - empty here

        // Draw to buffer - nothing is appearing on the screen yet
        window.draw(rectangle);
        window.draw(thickline);
        window.draw(circle);
        window.draw(triangle);


        // Finally move result onto screen
        window.display();
    }

    return 0;
}
