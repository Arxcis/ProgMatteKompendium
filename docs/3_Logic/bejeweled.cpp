#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

const int windowX = 512;
const int windowY = 512;
const float dotRad = 16.0;
const int numDots = 512/32;  // 16

const sf::Color dotColour[8] = {sf::Color::Red, sf::Color::White, sf::Color::Blue,
                                sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta,
                                sf::Color::Yellow, sf::Color::Black};


class Dot
{
public:
    virtual void draw(sf::RenderWindow& w);

    sf::Vector2f pos;
    int type;

};


void Dot::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(dotRad);
    s.setOrigin(dotRad,dotRad);
    s.setFillColor(dotColour[type]);
    s.setPosition(pos);
    w.draw(s);
}



class Board
{
public:
    Dot dots[numDots+4][numDots+4];

    Board();
    virtual void update();
    virtual void draw(sf::RenderWindow& w);
};



void Board::update()
{

}



Board::Board()
{
    // Initialize interior
    for(int i = 0; i < numDots; i++) {
        for(int j = 0; j < numDots; j++) {
            dots[i+2][j+2].type = rand() % 7;  // Black is never used in interior, hence % 7 not % 8
            dots[i+2][j+2].pos = sf::Vector2f(j * 2*dotRad+dotRad,i * 2 * dotRad+dotRad);
        }
    }

    // Inititialize boundary
    for(int i = 0; i < numDots; i++) {
        dots[i][0].type = 7;
        dots[i][1].type = 7;
        dots[0][i].type = 7;
        dots[1][i].type = 7;
        dots[18][i].type = 7;
        dots[19][i].type = 7;
        dots[i][18].type = 7;
        dots[i][19].type = 7;
    }

}


void Board::draw(sf::RenderWindow& w)
{
    for(int i = 0; i < numDots; i++) {
        for(int j = 0; j < numDots; j++) {
            dots[i+2][j+2].draw(w);
        }
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(512,512), "My window");

    int x;
    int y;
    bool pressed = false;

    Board board;

    while (window.isOpen())
    {

        sf::Event event;


        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
                }


            if(!pressed) {
                if (event.type == sf::Event::MouseButtonPressed ) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        x = event.mouseButton.x / (2*dotRad);
                        y = event.mouseButton.y / (2*dotRad);
                        pressed = true;
                        }
                    }
                }
            else {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                    int ax = event.mouseButton.x / (2*dotRad);
                    int ay = event.mouseButton.y / (2*dotRad);
                    int type = board.dots[y+2][x+2].type;
                    board.dots[y+2][x+2].type = board.dots[ay+2][ax+2].type;
                    board.dots[ay+2][ax+2].type = type;
                    pressed = false;
                    }
                }

            }
        }


        board.update();

        window.clear(sf::Color::Black);

        board.draw(window);

        window.display();
        }

    return 0;
}


