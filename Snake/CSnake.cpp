//CSnake.cpp file
#include"stdafx.h"
#include"CSnake.h"
extern int HEIGHT;
extern int WIDTH;
extern int snakeSpeed;
CSnake::CSnake() {
	CPoint snake;
	// set the initial points for the snake
	//head
	snake = CPoint(WIDTH / 2, HEIGHT / 2);
	SnakeBody.push_back(snake);
	//body
	snake = CPoint((WIDTH / 2) - 10, HEIGHT / 2);
	SnakeBody.push_back(snake);
	//tail
	snake = CPoint((WIDTH / 2) - 20, HEIGHT / 2);
	SnakeBody.push_back(snake);
	//set the above snake as a default snake
	defaultState = SnakeBody;
	//default direction is right
	direction = RIGHT;
	//object that isn't food
	is_food = FALSE;
}
//method to generate food
void CSnake::generateFood() {
	CPoint point(100, 100);
	do {
		//generate food at random points
		UINT x = rand() % (WIDTH - 200);
		UINT y = rand() % (HEIGHT - 200);
		UINT X = snakeSpeed * (x / snakeSpeed) + snakeSpeed;
		UINT Y = snakeSpeed* (y / snakeSpeed) + snakeSpeed;
		point = CPoint(X, Y);
	} while (point == food);
	food = CPoint(point);
}
BOOL CSnake::move()
{
	CPoint point;
	point = SnakeBody[0];
	if (getDirection() == UP)
	//if it moves up decrease the y value by 10
		point.y -= snakeSpeed;
	else if (getDirection() == DOWN)
	//if it moves down increase the y value by 10
		point.y += snakeSpeed;
	else if (getDirection() == LEFT)
	//if it moves left decrease the x value by 10
		point.x -= snakeSpeed;
	else if (getDirection() == RIGHT)
		//if it moves right increase the x value by 10
		point.x += snakeSpeed;
	else
		return TRUE;
		
	if (point.x < 0|| point.x> WIDTH - 100|| point.y < 5|| point.y > HEIGHT -
		5) {

		return FALSE;
		SnakeBody.begin()->x = WIDTH - point.x;
		SnakeBody.begin()->y = HEIGHT - point.y;
		return TRUE;
	}
	/*if the point at which the snake is has food then
	we increase its size*/
	
	if (point == food)
	{
		SnakeBody.push_back(*(SnakeBody.end() - 1));
		for (vector<CPoint>::iterator iter = SnakeBody.end() - 2; iter !=
			SnakeBody.begin(); iter--)
			{
				iter->x = (iter - 1)->x;
				iter->y = (iter - 1)->y;
			}
			SnakeBody.begin()->x = point.x;
			SnakeBody.begin()->y = point.y;
			generateFood();
		}
		else
		{
			for (vector<CPoint>::iterator iter = SnakeBody.end() - 1;
				iter != SnakeBody.begin(); iter--)
			{
				iter->x = (iter - 1)->x;
				iter->y = (iter - 1)->y;
			}
			SnakeBody.begin()->x = point.x;
			SnakeBody.begin()->y = point.y;
		}
	for (vector<CPoint>::iterator iter = SnakeBody.begin() + 1; iter !=
		SnakeBody.end(); ++iter) {

		if (SnakeBody.front().x == iter->x && SnakeBody.front().y == iter->y) {
			return FALSE;
		}
	}
	return TRUE;
}
//method to change direction
void CSnake::changeDirection(UINT ndir)
{
	direction = ndir;
}
//method to get direction
UINT CSnake::getDirection()
{
	return direction;

}




