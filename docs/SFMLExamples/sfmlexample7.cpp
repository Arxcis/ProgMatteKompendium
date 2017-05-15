/*

Example 7:

Snake (btw. all snake games should have an ascii feel)

*/

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const int windowSize = 512;
const int tileSize = 8;
const int maxSnake = 100000;
const float pause = 0.02;  // 1/pause is number of pixels per second

float abs(sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

class Snake
{
public:
    sf::Vector2f* pos;
    sf::Vector2f vel;
    int tail;
    float time;
    int grow;
    sf::CircleShape shape;

    Snake();
    ~Snake();
    void update(float dt);
    void draw(sf::RenderWindow& w);

};

Snake::Snake()
{
    pos = new sf::Vector2f[maxSnake + 1];
    tail = 10;
    for (int i = 0; i <= tail; i++) {
        pos[i].y = windowSize / 2;
        pos[i].x = windowSize / 2 + tileSize*i;
    }
    grow = 0;
    vel = sf::Vector2f(0, tileSize);
    shape.setFillColor(sf::Color::Yellow);
    shape.setRadius(tileSize / 2);
    shape.setOrigin(tileSize / 2, tileSize / 2);
}

Snake::~Snake()
{
    delete[] pos;
}

void Snake::draw(sf::RenderWindow& w)
{
    for (int i = 0; i <= tail; i++) {
        shape.setPosition(pos[i]);
        w.draw(shape);
    }
}

void Snake::update(float dt)
{
    time += dt;
    if (time > pause) {
        time = 0;
        if (grow > 0 && tail < maxSnake) {
            tail++;
            grow--;
        }

        for (int i = tail; i > 0; i--) {
            pos[i] = pos[i - 1];
        }

        pos[0] = pos[0] + vel;

        // Game over if out of screen
        if (pos[0].x < 0 || pos[0].y < 0 || pos[0].x > windowSize || pos[0].y > windowSize) {
            exit(0);
        }

        for (int a = 1; a < tail; a++)
            if (pos[0] == pos[a])
                exit(0);
    }
}


const int maxFood = 1000;
const float foodPause = 3;

class Food
{
public:
    float time = 0;
    sf::Vector2f pos[maxFood + 1];
    float foodSize[maxFood + 1];
    int nextFood = 0;

    void removeFood(int i);
    void eat(Snake& snake);
    void update(float dt);
    void draw(sf::RenderWindow& w);
};


void Food::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setFillColor(sf::Color::Green);
    for (int i = 0; i < nextFood; i++) {
        s.setPosition(pos[i]);
        s.setRadius(foodSize[i]);
        s.setOrigin(foodSize[i], foodSize[i]);
        w.draw(s);
    }
}


void Food::removeFood(int i)
{
    if (i < nextFood && nextFood > 0) {
        for (int j = i; j < nextFood; j++) {
            pos[j] = pos[j + 1];
            foodSize[j] = foodSize[j + 1];
        }
        nextFood--;
    }
}


void Food::eat(Snake& snake)
{
    for (int i = 0; i < nextFood; i++) {
        if (abs(snake.pos[0] - pos[i])<foodSize[i]) {
            snake.grow += foodSize[i];
            removeFood(i);
        }
    }
}


void Food::update(float dt)
{
    time -= dt;
    if (time < 0 && nextFood <= maxFood) {
        pos[nextFood] = sf::Vector2f(rand() % windowSize, rand() % windowSize);
        foodSize[nextFood] = rand() % 20 + 5;
        nextFood++;
        time = foodPause;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Example 1");

    sf::Clock clock;
    clock.restart();

    Snake snake;
    Food food;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Up) {
                    snake.vel = sf::Vector2f(0, -tileSize);
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    snake.vel = sf::Vector2f(0, tileSize);
                }

                if (event.key.code == sf::Keyboard::Left) {
                    snake.vel = sf::Vector2f(-tileSize, 0);
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    snake.vel = sf::Vector2f(tileSize, 0);
                }

            }
        }

        float dt = clock.restart().asSeconds();
        snake.update(dt);
        food.update(dt);
        food.eat(snake);

        // render
        window.clear(sf::Color::Black);
        snake.draw(window);
        food.draw(window);
        window.display();
    }

    return 0;

}


