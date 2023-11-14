#include "header/GameManager.h"

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
    GameObject rect(screenW/2.f, screenH, sf::Color::Green, 30.f, 70.f);

    GameObject movingRect(screenW/2.f, screenH/2.f, sf::Color::Red);
    movingRect.SetDirection(1, 0);

    /*--------------GAMELOOP--------------*/
    while (oWindow->isOpen())
    {
        /*--------------EVENT--------------*/
        detectEvent();
        
        /*--------------UPDATE--------------*/
        if (event)
        {
            rect.SetRotation(mPos, 0.5f, 1.f);
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
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicPos = mPos;
            //cout << "Clic en : " << clicPos.x << "," << clicPos.y << endl;
        }
    }
}