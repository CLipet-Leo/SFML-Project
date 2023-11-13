#include "header/GameManager.h"

int main(int argc, char** argv)
{
    //Création d'une fenêtre
    GameManager game(640, 480);
    game.GameLoop();

    return 0;
}

