#pragma once
#include"stdafx.h"
#include<vector>
#include<iterator>
using namespace std;
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
class CSnake :public CObject {
public:
	//constructor
	CSnake();
	//method to move
	BOOL move();
	//method to generate food
	void generateFood();
	//method to change direction
	void changeDirection(UINT);
	//method to get direction
	UINT getDirection();
	//the actual snake, a vector of points
	vector<CPoint> SnakeBody;
	//the snake we saved
	vector<CPoint> savedSnake;
	//the default snake
	vector<CPoint> defaultState;
	//a point to indicate where the food is
	CPoint food;
private:
	//direction UINT
	UINT direction;
	//a boolean to check what's food.
	BOOL is_food;
};


