#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const float PI = 3.1415;

string rewriteRules[256];

class Rule
{
public:
    float rotate=0;
    float forward=0;
    Rule() {};
    Rule(float rotate, float forward) {this->rotate = rotate;
                                     this->forward = forward;};
};

class LSystem
{
public:
    string grammar[256];
    string rewrite(string input);
    LSystem();
};

string LSystem::rewrite(string input)
{
    string::iterator it;
    string res;
    for( it = input.begin(); it!=input.end(); ++it)
    {
        res += grammar[*it];
    }
    return res;
}


LSystem::LSystem()
{
    for(int i=0; i <= 255; i++) {
        grammar[i] = (char) i;
    }
}

class State
{
public:
    float angle = 0;
    sf::Vector2f pos = sf::Vector2f(0,0);
    State() {};
    State(float angle, sf::Vector2f pos) {this->angle = angle; this->pos = pos;};
};

class StateStack
{
public:
    State states[1000];
    int current;

    StateStack() {current = 0;};
    bool empty() {return current < 0;};
    State pop();
    void push(State newState);
};

State StateStack::pop()
{
    if(current < 0) cout << "Stack empty" << endl;
    current--;
    return states[current+1];
}


void StateStack::push(State newState)
{
    if(current >= 999) cout << "Stack overflow" << endl;
    current++;
    states[current] = newState;
}

class Turtle
{
public:
    float angle;
    sf::Vector2f pos;
    StateStack turtleStack;
    int thickness = 1;
    Rule Rules[256];

    Turtle() {angle = -90; pos = sf::Vector2f(0,0);}
    void rotate(float rotAngle);  // degrees
    void forward(float distance, sf::RenderWindow& w);
    sf::FloatRect drawString(string st, sf::RenderWindow& w);

};

sf::FloatRect Turtle::drawString(string st, sf::RenderWindow& w)
{
    angle = -90;
    pos = sf::Vector2f(0,0);
    float minx,miny,maxx,maxy;
    minx = 1000;
    miny = 1000;
    maxx = -1000;
    maxy = -1000;
    string::iterator it;
    for( it = st.begin(); it!=st.end(); ++it)
    {
        if(*it == '(') {
            turtleStack.push(State(angle,pos));
           }
        else if(*it == ')') {
            State s;
            s = turtleStack.pop();
            angle = s.angle;
            pos = s.pos;
        }
        else {
            rotate(Rules[*it].rotate);
            forward(Rules[*it].forward,w);
            if(minx > pos.x) minx = pos.x;
            if(maxx < pos.x) maxx = pos.x;
            if(miny > pos.y) miny = pos.y;
            if(maxy < pos.y) maxy = pos.y;
        }
    }

   float size = maxx-minx;
   if(size < maxy-miny) size = maxy-miny;
   return sf::FloatRect(minx,miny,size,size);

}


void Turtle::rotate(float rotAngle)
{
    angle += rotAngle;
}

void Turtle::forward(float distance, sf::RenderWindow& w)
{
    sf::Vector2f newPos;
    newPos.x = pos.x + cos(angle*PI/180) * distance;
    newPos.y = pos.y + sin(angle*PI/180) * distance;

    sf::RectangleShape line(sf::Vector2f(distance, thickness*2));
    line.rotate(angle);
    line.setPosition(pos);
    line.setFillColor(sf::Color::Yellow);
    line.setOrigin(0,thickness);

    w.draw(line);

    pos = newPos;
}

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Turtle");

    LSystem L;
    Turtle turtle;
// Plant
//    string mystring = "x";
//    L.grammar['f'] = "ff";
//    L.grammar['x'] = "f-((x)+x)+f(+fx)-x";
//    for(int i = 0; i < 5; i++) {
//        mystring = L.rewrite(mystring);
//    }
//     turtle.Rules['f'] = Rule(0,50);
//    turtle.Rules['+'] = Rule(25,0);
//    turtle.Rules['-'] = Rule(-25,0);



// Dragon curve
//
//    string mystring = "fx";
//    L.grammar['x'] = "x+yf+";
//    L.grammar['y'] = "-fx-y";
//    turtle.Rules['f'] = Rule(0,50);
//    turtle.Rules['+'] = Rule(90,0);
//    turtle.Rules['-'] = Rule(-90,0);
//    for(int i = 0; i < 11; i++) {
//       mystring = L.rewrite(mystring);
//    }







    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))  {

        // check the type of the event...
        switch (event.type)  {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                turtle.thickness++;


            // we don't process other types of events
            default:
                break;

            }
        }

        window.clear();

        window.setView(sf::View(turtle.drawString(mystring,window)));

        window.display();
    }

    return 0;
}







