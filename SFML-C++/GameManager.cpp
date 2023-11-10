#include "header/GameManager.h"
#include "header/GameObject.h"

#include <iostream>

using namespace sf;
using namespace std;

GameManager::GameManager(int width, int height)
    :screenW(width), screenH(height)
{
    oWindow = new RenderWindow(VideoMode(screenW, screenH), "SFML");
    oWindow->setFramerateLimit(60);
    
}

GameManager::~GameManager()
{
    delete oWindow;
}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    //GameObject circle(0.f, 0.f, Color::Green, 50.f);
    GameObject rect(screenW/2.f, screenH - 10.f, Color::Green, 30.f, 70.f);
    GameObject line(screenW / 2.f, screenH / 2.f, Color::White, 5.f, screenH);
    
    //GameLoop
    while (oWindow->isOpen())
    {
        //EVENT
        detectEvent();
        
        //UPDATE
        if (event)
        {
            rect.Rotate(deltaTime, mPos);
        }

        //rect.Move(deltaTime);


        //DRAW
        oWindow->clear();

        //circle.Draw(*oWindow);
        rect.Draw(*oWindow);
        line.Draw(*oWindow);

        oWindow->display();
        
        deltaTime = deltaClock.restart().asSeconds();
    }
}

void GameManager::detectEvent()
{
    //EVENT
    event = false;
    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == Event::Closed)
            oWindow->close();
        if (oEvent.type == Event::MouseMoved)
        {
            mPos = Mouse::getPosition(*oWindow);
            event = true;
            cout << "La position de la souris : " << mPos.x << "," << mPos.y << endl;
            //cout << "Angle en degres : " << angleDegrees << endl;
        }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            clicPos = mPos;
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }


    }
}