#include "header/GameManager.h"

#include "header/GameObject.h"
#include "header/Canon.h"
#include "header/CanonBall.h"

using namespace std;

GameManager::GameManager(int width, int height)
    :screenW(width), screenH(height)
{
    oWindow = new sf::RenderWindow(sf::VideoMode(screenW, screenH), "Casse brique !");
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

    /*--------------OBJECT CREATE--------------*/
    Canon canon(screenW / 2.f, screenH * 1.f, sf::Color::Green, 30.f, 70.f);

    /*--------------GAMELOOP--------------*/
    while (oWindow->isOpen())
    {
        /*--------------EVENT--------------*/
        detectEvent();
        
        /*--------------UPDATE--------------*/
        if (moveEvent)
        {
            canon.SetRotation(mPos, 0.5f, 1.f);
        }
        if (clicEvent && oBullet.size() < 1)
        {
            canon.Shoot(oBullet);
        }
        if (oBullet.size() != 0)
        {
            for (int i = 0; i < oBullet.size(); i++) {
                oBullet.at(i)->Move(deltaTime);
            }
        }

        /*--------------DRAW--------------*/
        oWindow->clear();

        canon.Draw(*oWindow);
        if (oBullet.size() != 0)
        {
            for (int i = 0; i < oBullet.size(); i++) {
                oBullet.at(i)->Draw(*oWindow);
                /*sf::Vector2f position = oBullet.at(i)->GetPosition();
                cout << position.x << ", " << position.y << endl;*/
            }
        }

        oWindow->display();
        
        deltaTime = deltaClock.restart().asSeconds();
    }
}

void GameManager::detectEvent()
{
    moveEvent = false;
    clicEvent = false;

    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == sf::Event::Closed)
            oWindow->close();
        if (oEvent.type == sf::Event::MouseMoved)
        {
            mPos = sf::Mouse::getPosition(*oWindow);
            moveEvent = true;
            //cout << "La position de la souris : " << mPos.x << "," << mPos.y << endl;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicPos = mPos;
            clicEvent = true;
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }
    }
}