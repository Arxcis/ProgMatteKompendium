/*

Example 10:

Think like a fragment shader

*/

using namespace std;

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

//
// x,y: -1..1
// r,g,b: 0..1
//
void computePixel(sf::Vector2f p, float t, float& r, float& g, float& b, float& a)
{
    // 0..1
    float v;

    //
    // computations of v (insert your stuff here)
    //
    v = abs(p.x)+0.2*t;

    r = v;
    g = v;
    b = v;
    a = v;
}


using namespace std;

const int num = 512;

sf::Uint8 scale(float v)
{
    v = floor(v*256);
    if(v > 255) return 255;
    if(v < 0) return 0;
    return v;
}


int main()
{
    srand(1);
    sf::RenderWindow window(sf::VideoMode(512, 512), "Textures");

    sf::Clock clock;
    clock.restart();
    float t = 0;

    sf::Texture texture;
    texture.create(512,512);
    sf::Uint8* pixels = new sf::Uint8[512*512*4];

    // Textures have to be assigned to a sprite
    sf::Sprite sprite;
    sprite.setPosition(0,0);
    sprite.setTexture(texture);

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

        float dt = clock.restart().asSeconds();
        t += dt;

        for(int i = 0; i < 512; i ++) {
            for(int j = 0; j < 512; j++) {
                float r,g,b,a;
                computePixel(sf::Vector2f(i/256.0f-1.0f,j/256.0f-1.0f),t,r,g,b,a);
                pixels[(i*512+j)*4] = scale(r);
                pixels[(i*512+j)*4+1] = scale(g);
                pixels[(i*512+j)*4+2] = scale(b);
                pixels[(i*512+j)*4+3] = scale(a);
            }
        }

        texture.update(pixels);
        sprite.setTexture(texture);

        window.clear(sf::Color::Black);

        window.draw(sprite);
        window.display();
    }

    delete [] pixels;

    return 0;
}



