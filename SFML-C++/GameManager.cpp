#include "header/GameManager.h"
#include "header/GameObject.h"

#include <iostream>

using namespace sf;
using namespace std;

GameManager::GameManager(int width, int height)
{
    oWindow = new RenderWindow(VideoMode(width, height), "SFML");
}

GameManager::~GameManager()
{

}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    //GameObject circle(0.f, 0.f, Color::Green, 50.f);
    GameObject rect(100.f, 100.f, Color::Green, 50.f, 100.f);
    
    //GameLoop
    while (oWindow->isOpen())
    {
        //EVENT
        detectEvent();
        //UPDATE

        //DRAW
        oWindow->clear();

        //circle.Draw(*oWindow);
        rect.Draw(*oWindow);
        rect.Rotate(deltaTime);
        //rect.Move(deltaTime);

        oWindow->display();
        deltaTime = deltaClock.restart().asSeconds();
    }
}

void GameManager::detectEvent()
{
    //EVENT
    Event oEvent;
    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == Event::Closed)
            oWindow->close();
        if (oEvent.type == Event::MouseMoved)
        {
            Vector2i mPos = Mouse::getPosition();
            //cout << mPos.x << "," << mPos.y << endl;
        }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i clicPos = Mouse::getPosition();
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }
    }


}