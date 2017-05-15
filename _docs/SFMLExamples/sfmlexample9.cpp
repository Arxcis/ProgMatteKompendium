/*

Example 9:

Simple textures

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const int num = 512;

int main()
{
    srand(1);
    sf::RenderWindow window(sf::VideoMode(512, 512), "Textures");

    sf::Clock clock;
    clock.restart();

    //
    // Example 1: A texture we can draw to
    //
    sf::RenderTexture texture1;
    texture1.create(512,512);
    texture1.clear();

    sf::CircleShape shape;
    shape.setPosition(256,256);
    shape.setOrigin(128,128);
    shape.setRadius(128);
    shape.setFillColor(sf::Color::Yellow);

    texture1.draw(shape);

    //
    // Example 2: A texture as an array of RGBA
    //
    sf::Texture texture2;
    texture2.create(512,512);
    sf::Uint8* pixels = new sf::Uint8[512*512*4];
    for(int i = 0; i < 512; i ++) {
        for(int j = 0; j < 512; j++) {
            if((i-256)*(i-256)+(j-256)*(j-256) < 128*128) {
                pixels[(i+j*512)*4] = 255;
                pixels[(i+j*512)*4+1] = 255;
                pixels[(i+j*512)*4+2] = 0;
                pixels[(i+j*512)*4+3] = 255;
            } else {
                pixels[(i+j*512)*4] = 0;
                pixels[(i+j*512)*4+1] = 0;
                pixels[(i+j*512)*4+2] = 0;
                pixels[(i+j*512)*4+3] = 255;
            }
        }
    }
    texture2.update(pixels);

    // Textures have to be assigned to a sprite
    sf::Sprite sprite;
    // sprite.setTexture(texture1.getTexture());
    sprite.setTexture(texture2);
    sprite.setPosition(0,0);


    //
    // Other ways to get textures
    //
    // Load from image on file
    // Copy off screen
    // ....
    //


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

        window.clear(sf::Color::Black);

        window.draw(sprite);
        window.display();
    }

    delete [] pixels;

    return 0;
}



