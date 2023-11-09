#include "header/GameManager.h"
#include "header/GameObject.h"

#include <iostream>

using namespace sf;
using namespace std;

GameManager::GameManager(int width, int height)
    :screenW(width), screenH(height)
{
    oWindow = new RenderWindow(VideoMode(screenW, screenH), "SFML");
}

GameManager::~GameManager()
{

}

bool GameManager::Bloup(GameObject& object1, GameObject& object2) {
    
    return object1.x < object2.x + object2.width && object1.x + object1.width > object2.x && object1.y < object2.y + object2.height && object1.y + object1.height > object2.y;
}

void GameManager::GameLoop()
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    GameObject circleGreen(100.f, 100.f, Color::Green, 100.f);

    GameObject rectangleRed(50.f, 50.f, Color::Red, 50.f, 50.f);

    GameObject rectangleBlue(300.f, 30.f, Color::Blue, 50.f, 50.f);
    //GameObject circle(0.f, 0.f, Color::Green, 50.f);
    //GameObject rect(100.f, 100.f, Color::Green, 50.f, 100.f);
    
    //GameLoop
    String side;
    while (oWindow->isOpen())
    {
        //----------------------------------------EVENT-----------------------------------------
        detectEvent();
        //----------------------------------------UPDATE----------------------------------------

        if (rectangleBlue.pos.y < 0) {
            side = "up";
            rectangleBlue.DVDMove(side);
        }
        else if (rectangleBlue.pos.y + rectangleBlue.height > screenH) {
            side = "down";
            rectangleBlue.DVDMove(side);
        }
        if (rectangleBlue.pos.x < 0) {
            side = "left";
            rectangleBlue.DVDMove(side);
        }
        else if (rectangleBlue.pos.x + rectangleBlue.width > screenW) {
            side = "right";
            rectangleBlue.DVDMove(side);
        }


        //----------------------------------------DRAW------------------------------------------
        oWindow->clear();

        //circle.Draw(*oWindow);
        //rect.Draw(*oWindow);
        //rect.Rotate(deltaTime);
        //rect.Move(deltaTime);
        rectangleBlue.Draw(*oWindow);
        rectangleRed.Draw(*oWindow);
        rectangleBlue.Move(deltaTime);

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