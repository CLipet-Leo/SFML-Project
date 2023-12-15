#include "header/GameManager.h"

#include "header/GameObject.h"
#include "header/Canon.h"
#include "header/CanonBall.h"
#include "header/Brick.h"

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

//bool GameManager::RectOverlap(GameObject& object1, GameObject& object2)
//{
//    sf::Vector2f object1Position = object1.GetPosition();
//    sf::Vector2f object2Position = object2.GetPosition();
//    bool IsCollidingX = object1Position.x < object2Position.x + object2.width && object1Position.x + object1.width > object2Position.x;
//    bool IsCollidingY = object1Position.y < object2Position.y + object2.height && object1Position.y + object1.height > object2Position.y;
//
//    return  IsCollidingX && IsCollidingY;
//}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    //----------------------------------------OBJECT CREATION-----------------------------------------//
    Canon canon(screenW / 2.f, screenH * 1.f, sf::Color::Green, 30.f, 70.f);
    
    //----------------------------------------GAME LOOP-----------------------------------------//
    sf::String windowSide;
    while (oWindow->isOpen())
    {

        //----------------------------------------EVENT-----------------------------------------//
        detectEvent();
        if (moveEvent)
        {
            canon.SetRotation(mPos, 0.5f, 1.f);
        }
        if (clicEvent && oBullet.size() < 1)
        {
            canon.Shoot(oBullet);
        }
        for (size_t i = 0; i < oBullet.size(); ++i) {
            for (size_t j = i + 1; j < oBricks.size(); ++j) {
                GameObject* obj1 = oBullet.at(i);
                GameObject* obj2 = oBricks.at(j);

                // Vérifie la collision entre obj1 et obj2
                obj1->CheckWindowCollision(*oWindow);
                obj1->CheckCollisions(*obj2);
            }
        }

        //----------------------------------------UPDATE----------------------------------------//
        if (oBullet.size() != 0)
        {
            for (size_t i = 0; i < oBullet.size(); i++) {
                oBullet.at(i)->Move(deltaTime);
            }
        }
        
        //----------------------------------------DRAW------------------------------------------//
        oWindow->clear();
      
        canon.Draw(*oWindow);
        if (oBullet.size() != 0)
        {
            for (size_t i = 0; i < oBullet.size(); i++) {
                sf::Vector2f position = oBullet.at(i)->GetPosition();
                oBullet.at(i)->Draw(*oWindow);
                //cout << position.x << ", " << position.y << endl;
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
    //----------------------------------------EVENT-----------------------------------------//
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
            //cout << mPos.x << "," << mPos.y << endl;
        }
    }
}