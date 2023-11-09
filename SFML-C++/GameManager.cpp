#include "header/GameManager.h"
#include "header/GameObject.h"

#include <iostream>

using namespace sf;
using namespace std;

GameManager::GameManager(int width, int height)
    :screenW(width), screenH(height)
{
    oWindow = new RenderWindow(VideoMode(screenW, screenH), "SFML");

    mPos = new Vector2i;
}

GameManager::~GameManager()
{
    delete mPos;

    delete oWindow;
}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    //GameObject circle(0.f, 0.f, Color::Green, 50.f);
    GameObject rect(screenW/2.f, screenH - 10.f, Color::Green, 30.f, 70.f);
    
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
            if (mPos)
            {
                *mPos = Mouse::getPosition();
                cout << mPos->x << "," << mPos->y << endl;
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (mPos)
            {
                clicPos = *mPos;
                //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
            }
        }


    }
}