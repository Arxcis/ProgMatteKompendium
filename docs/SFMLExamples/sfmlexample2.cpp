/*
Example 2:

Moving something

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class GameObject
{
public:
    sf::Vector2f pos;

    // measured in pixels per second if viewSize and windowSize are equal
    sf::Vector2f vel;
    sf::CircleShape shape;
    float shapeSize;

    GameObject();
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

GameObject::GameObject()
{
    shapeSize = 100;
    vel = sf::Vector2f(143,56);
    pos = sf::Vector2f(0,0);
    shape.setFillColor(sf::Color::Yellow);
}

void GameObject::update(float dt)
{
    // integrate velocity
    pos += dt * vel;

    // collision detecting
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

void GameObject::draw(sf::RenderWindow& w)
{
    shape.setPosition(pos);
    shape.setOrigin(shapeSize,shapeSize);
    shape.setRadius(shapeSize);
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


    sf::Clock clock;

    // reset timer to 0
    clock.restart();


    GameObject object;

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
        // Physics and AI
        //
        float dt = clock.restart().asSeconds();
        object.update(dt);

        //
        // Rendering:
        //

        // Clear buffer
        window.clear();

        // Change view - empty here

        // Draw to buffer - nothing is appearing on the screen yet
        object.draw(window);

        // Finally move result onto screen
        window.display();
    }

    return 0;
}
