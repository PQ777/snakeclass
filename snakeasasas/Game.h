#pragma once

const int width = 40;
const int height = 20;
const int MaxTail = 100;

enum class Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Position
{
    int x;
    int y;
};

class Snake
{
private:
    Position segments[MaxTail];
    int NumSegment;
    Direction key;

public:
    Snake();
    int GetX(int index) const;
    int GetY(int Index) const;
    Direction GetDirection() const;
    void SetDirection(Direction key);
    int GetNumSegments() const;
    void Move();
    void Grow();
};

class Apple
{
private:
    Position position;

public:
    Apple();
    int GetX() const;
    int GetY() const;
    void Respawn();
};

class Game
{
private:
    bool GameOver;
    Snake snake;
    Apple apple;
    int score;

public:
    Game();
    bool IsGameOver() const;
    int GetScore() const;
    void IsInput();
    void Update();
    void CheckCollision();
    void Draw();
    void Reset();
};
