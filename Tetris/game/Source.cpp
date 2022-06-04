#include "../menu/MenuClass.h"
#include <Windows.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Menu menu;
    menu.update();
}