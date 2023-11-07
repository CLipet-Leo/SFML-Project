#include "header/GameManager.h"
#include "header/GameObject.h"

using namespace sf;

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

    GameObject circle(0.f, 0.f, Color::Green, 50.f);
    GameObject rect(100.f, 100.f, Color::Green, 50.f, 100.f);
    
    //GameLoop
    while (oWindow->isOpen())
    {
        //EVENT
        Event oEvent;
        while (oWindow->pollEvent(oEvent))
        {
            if (oEvent.type == Event::Closed)
                oWindow->close();
        }

        //UPDATE

        //DRAW
        oWindow->clear();

        circle.Draw(*oWindow);
        //circle.Move(1, 10);
        rect.Draw(*oWindow);
        //rect.Rotate();
        rect.Update(deltaTime);

        oWindow->display();
        deltaTime = deltaClock.restart().asSeconds();
    }
}