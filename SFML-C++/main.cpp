#include <SFML/Graphics.hpp>

#include "header/GameManager.h"
#include "header/GameObject.h"

int main(int argc, char** argv)
{
    //Cr�ation d'une fen�tre
    GameManager game(640, 480);
    game.GameLoop();

    return 0;
}

