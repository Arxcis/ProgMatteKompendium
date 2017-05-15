#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline float abs(sf::Vector2f v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}

inline float abssq(sf::Vector2f v)
{
    return v.x*v.x+v.y*v.y;
}

float sign(float x)
{
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}

const int noTiny = 160;  //divisble by 4

class Blob
{
public:
    sf::Vector2f pos;
    sf::Vector2f p[noTiny];
    sf::Vector2f q[noTiny];
    float l[noTiny];
    sf::Color color;
    bool active;
    float t;
    float s;

    Blob();
    void activate();
    void secondPhase();
    void deActivate();
    void draw(sf::RenderWindow& w);
    void update(float dt);
};

Blob::Blob()
{
    color = sf::Color::Yellow;
    for(int i = 0; i < noTiny/4; i++ ) {
        p[i].x = 20*(0 + ((float) i) / (noTiny/4.0));
        p[i].y = 20*(-1 + ((float) i) / (noTiny/4.0));

    }

    for(int i = 0; i < noTiny/4; i++ ) {
        p[i + noTiny/4].x = 20*(1 - ((float) i) / (noTiny/4.0));
        p[i + noTiny/4].y = 20*(0 + ((float) i) / (noTiny/4.0));


    }

    for(int i = 0; i < noTiny/4; i++ ) {
        p[i+ 2*noTiny/4].x = 20*(0 - (float) i / (noTiny/4.0));
        p[i+ 2*noTiny/4].y = 20*(1 - (float) i / (noTiny/4.0));

    }

    for(int i = 0; i < noTiny/4; i++ ) {
        p[i+ 3*noTiny/4].x = 20*(-1 + (float) i / (noTiny/4.0));
        p[i+ 3*noTiny/4].y = 20*(0 - (float) i / (noTiny/4.0));

    }

    active = false;

    for(int i = 0; i < noTiny; i++) {
        q[i] = p[i];
        l[i] = 40;
    }
}

void Blob::draw(sf::RenderWindow& w)
{
    if(!active) {
        sf::CircleShape s;
        s.setOrigin(5,5);
        s.setRadius(5);
        s.setFillColor(color);
        for(int i = 0; i < noTiny; i++ ) {
            s.setPosition(sf::Vector2f(pos.x + p[i].x, pos.y + p[i].y));
            w.draw(s);
        }

    } else {
        sf::CircleShape c;
        c.setOrigin(5,5);
        c.setRadius(5);
        c.setFillColor(color);
        for(int i = 0; i < noTiny; i++ ) {
            c.setPosition(sf::Vector2f(pos.x + q[i].x, pos.y + q[i].y));
            w.draw(c);
        }


    }

}


void Blob::activate()
{
    if(! active) {

        color = sf::Color::Red;
        active = true;
        t = 3.1415 ;
    }

}


void Blob::deActivate()
{
    color = sf::Color::Yellow;
    active = false;
    for(int i = 0; i < noTiny; i++) {
        q[i] = p[i];
    }
}


void Blob::update(float dt)
{
    if(active) {
        if(t > 3.1415 / 2) t -= 2*dt;
        else t -= 0.6*dt;
        if(t < 0) {
            deActivate();
        } else {
            s = sin(t)*sin(t);
            float c = cos(t)*cos(t);
            for(int i = 0; i < noTiny; i++) {
                q[i] =  s*sf::Vector2f(l[i]*cos(2*3.1415*i/noTiny- 3.1415/2) ,l[i]*sin(2*3.1415*i/noTiny- 3.1415/2))+c*p[i];
                color=sf::Color(255, 255 - s*255, 0, 255);
            }
        }

    }
}


class BlobScreen
{
public:
    Blob blobs[8][8];

    BlobScreen();

    void activate(sf::Vector2f pos);
    void draw(sf::RenderWindow& w);
    void update(float dt);
};


void BlobScreen::activate(sf::Vector2f pos)
{
    int i = (int) pos.x / 64;
    int j = (int) pos.y / 64;
    if(i < 8 && i >= 0 && j < 8 && j >= 0) {
        blobs[i][j].activate();
    }
}

BlobScreen::BlobScreen()
{
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            blobs[i][j].pos = sf::Vector2f(i * 512 / 8 + 32, j * 512 / 8 + 32);
            blobs[i][j].color = sf::Color::Yellow;
        }
    }
}

void BlobScreen::draw(sf::RenderWindow& w)
{
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(!blobs[i][j].active) blobs[i][j].draw(w);
        }
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
           if(blobs[i][j].active) blobs[i][j].draw(w);
        }
    }
}


void BlobScreen::update(float dt)
{
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            blobs[i][j].update(dt);
        }
    }
}


const float dtfactor = 2;

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "My window");

    BlobScreen myBlobs;

    Blob b;
    b.pos = sf::Vector2f(256,256);

    sf::Clock clock;
    clock.restart();

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

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = sf::Vector2f(mousePos.x,mousePos.y);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) myBlobs.activate(worldPos);

        myBlobs.update(dt*dtfactor);


        window.clear(sf::Color::Black);

        //b.draw(window);
        myBlobs.draw(window);



        window.display();
    }

    return 0;
}



