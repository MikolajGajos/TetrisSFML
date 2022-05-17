#include <SFML/Graphics.hpp>
#include "../menu/MenuClass.h"
#include <regex>
#include <Windows.h>

constexpr auto BACKSPACE = 8;
constexpr auto ENTER = 13;
constexpr auto ESC = 27;

void main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Menu menu;
    menu.update();
}