#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Game.h"

using namespace std;

int main()
{
    system("mode con:cols=60 lines=40");
    Game game;
    bool restart = true;

    while (restart)
    {
        cout << "========== 게임을 시작합니다 =====================" << endl;
        cout << "1. 쉬움 / 2. 보통(미구현) / 3. 어려움(미구현)" << endl;
        cout << "난이도를 선택하세요: ";
        int input;
        cin >> input;

        while (!game.IsGameOver())
        {
            game.Draw();
            game.IsInput();
            game.Update();
            //Sleep(100);  
        }

        cout << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "게임 오버" << endl;
        cout << "점수: " << game.GetScore() << endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "1. 재시작 / 2. 종료" << endl;
        cout << "선택: ";
        cin >> input;

        game.Reset();

        restart = (input == 1);

        system("cls");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "게임을 종료합니다." << endl;

    return 0;
}
