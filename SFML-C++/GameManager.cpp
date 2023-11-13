#include "header/GameManager.h"
#include "header/GameObject.h"

#include <iostream>

using namespace sf;
using namespace std;

GameManager::GameManager(int width, int height)
    :screenW(width), screenH(height)
{
    oWindow = new sf::RenderWindow(sf::VideoMode(screenW, screenH), "SFML");
}

GameManager::~GameManager()
{

}

bool GameManager::RectOverlap(GameObject& object1, GameObject& object2)
{

    return object1.pos.x < object2.pos.x + object2.width && object1.pos.x + object1.width > object2.pos.x && object1.pos.y < object2.pos.y + object2.height && object1.pos.y + object1.height > object2.pos.y;
}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    GameObject circleGreen(100.f, 100.f, sf::Color::Green, 100.f);

    GameObject* rectangleRed = new GameObject(150.f, 150.f, sf::Color::Red, 50.f, 50.f);
    GameObject* rectangleBlue = new GameObject(150.f, 300.f, sf::Color::Blue, 50.f, 50.f);
    
    //GameLoop
    sf::String windowSide;
    while (oWindow->isOpen())
    {
        //----------------------------------------EVENT-----------------------------------------
        detectEvent();
        //----------------------------------------UPDATE----------------------------------------

        if (rectangleBlue->pos.y < 0)
        {
            windowSide = "up";
            rectangleBlue->DVDMove(windowSide);
        }
        else if (rectangleBlue->pos.y + rectangleBlue->height > screenH)
        {
            windowSide = "down";
            rectangleBlue->DVDMove(windowSide);
        }
        if (rectangleBlue->pos.x < 0)
        {
            windowSide = "left";
            rectangleBlue->DVDMove(windowSide);
        }
        else if (rectangleBlue->pos.x + rectangleBlue->width > screenW)
        {
            windowSide = "right";
            rectangleBlue->DVDMove(windowSide);
        }

        rectangleBlue->Move(deltaTime);

        if (RectOverlap(*rectangleBlue, *rectangleRed))
        {
            rectangleBlue->collision(*rectangleRed);
            //printf("bloup\n");
        }


        //----------------------------------------DRAW------------------------------------------
        oWindow->clear();

        rectangleBlue->Draw(*oWindow);
        rectangleRed->Draw(*oWindow);

        oWindow->display();
        deltaTime = deltaClock.restart().asSeconds();
    }
}

void GameManager::detectEvent()
{
    //EVENT
    sf::Event oEvent;
    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == sf::Event::Closed)
            oWindow->close();
        if (oEvent.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mPos = sf::Mouse::getPosition();
            //cout << mPos.x << "," << mPos.y << endl;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i clicPos = sf::Mouse::getPosition();
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }
    }


}