#include "Game.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

Snake::Snake()
{
    NumSegment = 1;                 // 뱀 길이
    segments[0].x = width / 2;      // 뱀을 중앙에 설정
    segments[0].y = height / 2;

    key = Direction::STOP;
}

int Snake::GetX(int segmentIndex) const
{
    return segments[segmentIndex].x;
}

int Snake::GetY(int segmentIndex) const
{
    return segments[segmentIndex].y;
}

Direction Snake::GetDirection() const
{
    return key;
}

void Snake::SetDirection(Direction direction)
{
    key = direction;
}

int Snake::GetNumSegments() const
{
    return NumSegment;
}

void Snake::Move()
{
    for (int i = NumSegment - 1; i > 0; i--)
    {
        segments[i] = segments[i - 1];          // 뱀을 이전 위치로 이동
    }

    switch (key)
    {
    case Direction::LEFT:
        segments[0].x--;
        break;

    case Direction::RIGHT:
        segments[0].x++;
        break;

    case Direction::UP:
        segments[0].y--;
        break;

    case Direction::DOWN:
        segments[0].y++;
        break;
    }
}

void Snake::Grow()
{
    if (NumSegment < MaxTail)
    {
        // 뱀의 꼬리 부분을 추가하여 길이 증가
        segments[NumSegment] = segments[NumSegment - 1];
        NumSegment++;
    }
}

Apple::Apple()
{
    Respawn();
}

int Apple::GetX() const
{
    return position.x;
}

int Apple::GetY() const
{
    return position.y;
}

void Apple::Respawn()
{
    position.x = rand() % width;
    position.y = rand() % height;
}

Game::Game()
{
    GameOver = false;
    score = 0;
}

bool Game::IsGameOver() const
{
    return GameOver;
}

int Game::GetScore() const
{
    return score;
}

void Game::IsInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            snake.SetDirection(Direction::LEFT);
            break;

        case 'd':
        case 'D':
            snake.SetDirection(Direction::RIGHT);
            break;

        case 'w':
        case 'W':
            snake.SetDirection(Direction::UP);
            break;

        case 's':
        case 'S':
            snake.SetDirection(Direction::DOWN);
            break;

        case 'x':
        case 'X':
            GameOver = true;
            break;
        }
    }
}

void Game::Update()
{
    snake.Move();
    CheckCollision();
}

void Game::CheckCollision()         // 충돌확인
{
    int snakeX = snake.GetX(0);
    int snakeY = snake.GetY(0);

    // 뱀 머리와 몸통 충돌 확인
    for (int i = 1; i < snake.GetNumSegments(); i++)
    {
        if (snakeX == snake.GetX(i) && snakeY == snake.GetY(i))
        {
            GameOver = true;
            
        }
    }

    int appleX = apple.GetX();
    int appleY = apple.GetY();

    // 뱀 머리과 사과 충돌 확인
    if (snakeX == appleX && snakeY == appleY)
    {
        score++;
        snake.Grow();
        apple.Respawn();
    }

    // 뱀이 벽에 충돌 확인
    if (snakeX >= width || snakeX < 0 || snakeY >= height || snakeY < 0)
    {
        GameOver = true;
    }
}

void Game::Draw()
{
    system("cls");

    for (int i = 0; i < width / 2 + 2; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "■";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "■";
            }

            bool isSnakeSegment = false;
            for (int k = 0; k < snake.GetNumSegments(); k++)
            {
                if (i == snake.GetY(k) && j == snake.GetX(k))
                {
                    isSnakeSegment = true;
                    break;
                }
            }

            if (isSnakeSegment)
            {
                cout << "O";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            }
            else if (i == apple.GetY() && j == apple.GetX())
            {
                cout << "@";
            }
            else
            {
                cout << " ";
            }

            if (j == width - 1)
            {
                cout << "■";
            }
        }
        cout << endl;
    }



    for (int i = 0; i < width / 2 + 2; i++)
    {
        cout << "■";
    }
    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Score: " << score << endl;
}

void Game::Reset()
{
    GameOver = false;
    score = 0;
    snake = Snake();
    apple = Apple();
}
