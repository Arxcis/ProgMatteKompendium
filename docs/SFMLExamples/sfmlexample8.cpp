/*

Example 8:

Tetris

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;


class Shape
{
public:
    sf::Color tiles[4][4];
    sf::Vector2i pos;
    float time = 0;

    Shape();
    void init();
    void update(float dt);
    void draw(sf::RenderWindow& w);
    void rotateLeft();
    void rotateRight();
};

void Shape::rotateLeft()
{
    sf::Color tmp[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tmp[i][j]=tiles[j][3-i];
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tiles[i][j]=tmp[i][j];
        }
    }
}

void Shape::rotateRight()
{
    rotateLeft();
    rotateLeft();
    rotateLeft();
}

Shape::Shape()
{
    init();
}

void Shape::init()
{
    pos.y = 0;
    pos.x = 4;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tiles[i][j] = sf::Color::Black;
        }
    }

    switch(rand() % 2) {

    case 0:
        tiles[2][0] = sf::Color::Red;
        tiles[2][1] = sf::Color::Red;
        tiles[2][2] = sf::Color::Red;
        tiles[2][3] = sf::Color::Red;
        break;

    case 1:
        tiles[0][2] = sf::Color::Blue;
        tiles[1][2] = sf::Color::Blue;
        tiles[1][1] = sf::Color::Blue;
        tiles[2][1] = sf::Color::Blue;
        break;

    }

}

void Shape::update(float dt)
{
    time += dt;
    if(time > 1) {
        time = 0;
        pos.y += 1;
    }
}

void Shape::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(8);
    s.setOrigin(8,8);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tiles[i][j] != sf::Color::Black) {
                s.setFillColor(tiles[i][j]);
                s.setPosition(sf::Vector2f(pos.x * 16 + 16 * i + 100, pos.y * 16 + 16 * j + 100));
                w.draw(s);
            }
        }
    }
}

class Board
{
public:
    sf::Color tiles[12][20];

    Board();
    void add(Shape& shape);
    bool intersect(Shape& shape);
    void reduce();
    void draw(sf::RenderWindow& w);
};


void Board::reduce()
{
    for(int i = 0; i < 19; i++) {
        int c = 0;

        for(int j = 0; j < 12; j++) {
            if(tiles[j][i] != sf::Color::Black) {
                c ++;
            }
        }

        if(c == 12) {
            for(int k = i; k > 0; k--) {
                for(int l = 1; l < 11; l++) {
                    tiles[l][k] = tiles[l][k-1];
                }
            }

        }
    }
}

bool Board::intersect(Shape& shape)
{
    bool intersect = false;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tiles[i+shape.pos.x][j+shape.pos.y] != sf::Color::Black &&
               shape.tiles[i][j] != sf::Color::Black)
               intersect = true;
        }
    }
    return intersect;
}

void Board::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(8);
    s.setOrigin(8,8);
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 20; j++) {
            s.setFillColor(tiles[i][j]);
            s.setPosition(sf::Vector2f(16 * i + 100, 16*j + 100));
            w.draw(s);
        }
    }
}

void Board::add(Shape& shape)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            if(shape.tiles[i][j] != sf::Color::Black) {
                tiles[i + shape.pos.x][j + shape.pos.y] = shape.tiles[i][j];

                }

            }

        }


}





Board::Board()
{
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 12; j++) {
            tiles[j][i] = sf::Color::Black;
        }
    }
    for(int i = 0; i < 12; i++) {
        tiles[i][19] = sf::Color::Red;
    }
    for(int i = 0; i < 19; i++) {
        tiles[0][i] = sf::Color::Red;
        tiles[11][i] = sf::Color::Red;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Tetris");

    sf::Clock clock;
    clock.restart();

    Shape shape;

    Board board;


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


            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Left) {
                    shape.pos.x -= 1;
                    if(board.intersect(shape)) shape.pos.x += 1;
                }
                if(event.key.code == sf::Keyboard::Right) {
                    shape.pos.x += 1;
                    if(board.intersect(shape)) shape.pos.x -= 1;
                }
                if(event.key.code == sf::Keyboard::Down) {
                    shape.pos.y += 1;
                    if(board.intersect(shape)) shape.pos.y -= 1;
                }
                if(event.key.code == sf::Keyboard::Up) {
                    shape.rotateLeft();
                    if(board.intersect(shape)) shape.rotateRight();
                }
            }


        }



        float dt = clock.restart().asSeconds();

        shape.update(dt);
        if(board.intersect(shape)) {
            shape.pos.y -= 1;
            board.add(shape);
            board.reduce();
            shape.init();
            if(board.intersect(shape)) {
                cout << "GAME OVER" << endl;
            }
        }


        window.clear(sf::Color::Black);

        board.draw(window);
        shape.draw(window);


        window.display();
    }

    return 0;
}



