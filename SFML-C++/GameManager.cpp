#include "header/GameManager.h"

using namespace std;

GameManager::GameManager(int width, int height, string windowName)
    :screenW(width), screenH(height)
{
    oWindow = new sf::RenderWindow(sf::VideoMode(screenW, screenH), windowName);
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
    GameObject rect(screenW/2.f, screenH, sf::Color::Green, 30.f, 70.f);
    rect.SetPosition(0, 0, 0.5f, 0);

    GameObject movingRect(screenW/2.f, screenH/2.f, sf::Color::Red);
    movingRect.SetPosition();
    movingRect.SetDirection(1, 0);

    /*--------------GAMELOOP--------------*/
    while (oWindow->isOpen())
    {
        /*--------------EVENT--------------*/
        detectEvent();
        
        /*--------------UPDATE--------------*/
        if (event)
        {
            rect.Rotate(mPos);
        }
        
        movingRect.Move(deltaTime);

        /*--------------DRAW--------------*/
        oWindow->clear();

        rect.Draw(*oWindow);
        movingRect.Draw(*oWindow);

        oWindow->display();
        
        deltaTime = deltaClock.restart().asSeconds();
    }
}

void GameManager::detectEvent()
{
    event = false;
    while (oWindow->pollEvent(oEvent))
    {
        if (oEvent.type == sf::Event::Closed)
            oWindow->close();
        if (oEvent.type == sf::Event::MouseMoved)
        {
            mPos = sf::Mouse::getPosition(*oWindow);
            event = true;
            //cout << "La position de la souris : " << mPos.x << "," << mPos.y << endl;
            //cout << "Angle en degres : " << angleDegrees << endl;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicPos = mPos;
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }
    }
}