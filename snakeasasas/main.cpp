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
        cout << "========== ������ �����մϴ� =====================" << endl;
        cout << "1. ���� / 2. ����(�̱���) / 3. �����(�̱���)" << endl;
        cout << "���̵��� �����ϼ���: ";
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
        cout << "���� ����" << endl;
        cout << "����: " << game.GetScore() << endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "1. ����� / 2. ����" << endl;
        cout << "����: ";
        cin >> input;

        game.Reset();

        restart = (input == 1);

        system("cls");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "������ �����մϴ�." << endl;

    return 0;
}
