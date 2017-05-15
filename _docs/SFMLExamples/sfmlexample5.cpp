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
    float angVel;
    float angle = 0;
    float radius = 100;
    GameObject* parent;

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
    parent = NULL;
    angVel = 3.1415 / 4;
    shapeSize = 50;
    angle = 0;
    pos = sf::Vector2f(100,0);
    shape.setFillColor(sf::Color::Yellow);
}

void GameObject::update(float dt)
{
    angle += angVel * dt;
    pos = sf::Vector2f(radius*cos(angle), radius*sin(angle));
    if(parent != NULL) pos += parent->pos;
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


    GameObject object1;
    GameObject object2;
    object2.parent = &object1;
    object2.shapeSize = 25;
    object2.angVel = -3.14/2;

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
        object1.update(dt);
        object2.update(dt);

        //
        // Rendering:
        //

        // Clear buffer
        window.clear();

        // Change view - empty here

        // Draw to buffer - nothing is appearing on the screen yet
        object1.draw(window);
        object2.draw(window);

        // Finally move result onto screen
        window.display();
    }

    return 0;
}
