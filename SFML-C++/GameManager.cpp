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

    GameObject* rectangleRed = new GameObject(150.f, 150.f, sf::Color::Red, 50.f, 50.f);
    GameObject* rectangleBlue = new GameObject(300.f, 150.f, sf::Color::Blue, 50.f, 50.f);
    rectangleBlue->SetDirection(1, 1);
    
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
        if (oBullet.size() != 0)
        {
            for (int i = 0; i < oBullet.size(); i++) {
                oBullet.at(i)->Move(deltaTime);
            }
        }

        //----------------------------------------UPDATE----------------------------------------//
        rectangleBlue->GetPosition();
        rectangleRed->GetPosition();


        sf::Vector2f oPositionMin = rectangleBlue->GetPosition(0, 0);
        sf::Vector2f oPositionMax = rectangleBlue->GetPosition(1, 1);

        //up screen collision
        if (oPositionMin.y < 0)
        {
            //go down
            rectangleBlue->SetDirection(rectangleBlue->oDirection.x, rectangleBlue->oDirection.y * (-1));
        }
        //down screen collision
        else if (oPositionMax.y > screenH)
        {
            //go up
            rectangleBlue->SetDirection(rectangleBlue->oDirection.x, rectangleBlue->oDirection.y * (-1));
        }
        //left screen collision
        if (oPositionMin.x < 0)
        {
            //go right
            rectangleBlue->SetDirection(rectangleBlue->oDirection.x * (-1), rectangleBlue->oDirection.y);
        }
        //right screen collision
        else if (oPositionMax.x > screenW)
        {
            //go left
            rectangleBlue->SetDirection(rectangleBlue->oDirection.x * (-1), rectangleBlue->oDirection.y);
        }

        rectangleBlue->Move(deltaTime);
        rectangleBlue->CheckCollision(rectangleRed);
        


        //----------------------------------------DRAW------------------------------------------//
        oWindow->clear();
      
        canon.Draw(*oWindow);
        if (oBullet.size() != 0)
        {
            for (int i = 0; i < oBullet.size(); i++) {
                oBullet.at(i)->GetPosition();
                oBullet.at(i)->Draw(*oWindow);
                //cout << position.x << ", " << position.y << endl;
            }
        }
        rectangleBlue->Draw(*oWindow);
        rectangleRed->Draw(*oWindow);

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