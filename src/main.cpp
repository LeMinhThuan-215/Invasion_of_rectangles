#include "game.h"

int main()
{
    //Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    //Run game
    Game game;
    while (game.running())
    {   
        game.update();
        game.render();
    }

    return 0;
}
