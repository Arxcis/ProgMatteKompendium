/*
Example 4:

Visualisation of Markov simulation for area of circle

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;

class GameObject
{
public:
    sf::Vector2f pos;
    sf::Color color;
    GameObject();
    void draw(sf::RenderWindow& w);
};

// I don't think this is needed, but just in case...
GameObject::GameObject()
{
    pos = sf::Vector2f(0,0);
}

void GameObject::draw(sf::RenderWindow& w)
{
    sf::CircleShape shape;

    shape.setPosition(pos);
    shape.setOrigin(0.01,0.01);
    shape.setRadius(0.01);
    shape.setFillColor(color);

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
    sf::Vector2f viewSize(2.0,2.0);
    sf::View view(viewOrigin, viewSize);
    window.setView(view);


    // Create datapoints to be put on screen
    const int numPoints = 10000;
    GameObject* data = new GameObject[numPoints];
    int current = 0;
    float hits = 0;

    // We need to generate random numbers, so lets create a generator
    mt19937 generator;
    uniform_real_distribution<float> distribution(-1.0,1.0);


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


        if(current < numPoints) {
            sf::Vector2f np = sf::Vector2f(distribution(generator), distribution(generator));
            data[current].pos = np;
            if(np.x * np.x + np.y * np.y <= 1) {
                hits += 1.0f;
                data[current].color = sf::Color::Red;
            } else data[current].color = sf::Color::Yellow;
            current ++;
        }

        //
        // Rendering:
        //

        // Clear buffer
        window.clear();

        // Change view - empty here

        // Draw to buffer - nothing is appearing on the screen yet
        for(int i = 0; i < current; i++) {
            data[i].draw(window);
        }

        // Finally move result onto screen
        window.display();

        cout << hits / current << " " << 4*(hits / current) << endl;
    }


    delete [] data;




    return 0;
}
