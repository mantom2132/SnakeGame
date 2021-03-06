
// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif
#include "CSnake.h"
#include "SnakeDoc.h"
#include "SnakeView.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//Saves the direction the snake is facing
UINT DirectionSave;
//saves the direction the snake was facing before it was saved
UINT directionBeforePause = 0;
//a bool to check if a snake was saved.
bool saveGameExist = false;
//Csnake object to signify the snake in our game
CSnake snake;
//difficulty game
int speed = -1;
//checks what the state of the saved game was
int StateOfSavedGame= 0; // 0 running, 1 paused, 2 over
//height and width values initiated at 600
int HEIGHT = 600;
int WIDTH = 600;
//state of the game
int StateOfGame = 0;	 //0 when the game is running, 1 when the game is paused, 2 when game is over
//namespace declaration
using namespace std;
//red initiated at 255 so as to draw the initial snake as red
int Red = 255;
//Green color
int Green = 0;
//blue color
int Blue = 0;
//integer to set the speed of the game.
int snakeSpeed = 10;
// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_START_START, &CSnakeView::OnStartStart)
	ON_COMMAND(ID_PAUSE, &CSnakeView::OnPause)
	ON_COMMAND(ID_RESTART_RESTART, &CSnakeView::OnRestartRestart)
	ON_COMMAND(ID_GRIDSIZE_SMALL, &CSnakeView::OnGridsizeSmall)
	ON_COMMAND(ID_COLOUR_RED, &CSnakeView::OnColourRed)
	ON_COMMAND(ID_COLOUR_BLACK, &CSnakeView::OnColourBlack)
	ON_COMMAND(ID_COLOUR_GREEN, &CSnakeView::OnColourGreen)
	ON_COMMAND(ID_COLOUR_BLUE, &CSnakeView::OnColourBlue)
	ON_COMMAND(ID_GRIDSIZE_MEDIUM, &CSnakeView::OnGridsizeMedium)
	ON_COMMAND(ID_GRIDSIZE_LARGE, &CSnakeView::OnGridsizeLarge)
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_APP_SAVE, &CSnakeView::OnAppSave)
	ON_COMMAND(ID_APP_LOAD, &CSnakeView::OnAppLoad)
	ON_COMMAND(ID_SPEED_SLOW, &CSnakeView::OnSpeedSlow)
	ON_COMMAND(ID_SPEED_MEDIUM, &CSnakeView::OnSpeedMedium)
	ON_COMMAND(ID_MEDIUM_FAST, &CSnakeView::OnMediumFast)
END_MESSAGE_MAP()


//method to set the timer
void CSnakeView::OnTimer(UINT_PTR nIDEvent)
{
	if (snake.move() != TRUE)
	{
		KillTimer(nIDEvent);
		StateOfGame = 2;
		CString string;
		string.Format(_T("GAME OVER !!!"));
		MessageBox(string);
		//theApp.OnAppLostGame();
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}
//Constructor
CSnakeView::CSnakeView()
{


}
//Deconstructor
CSnakeView::~CSnakeView()
{
}
//Pre-create window method
BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//construct rect to fill background
	CRect rect;
	GetClientRect(rect);
	//Move window at the standart position
	GetParentFrame()->MoveWindow(0, 0, WIDTH, HEIGHT);
	SetRect(rect, 0, 0, WIDTH-90, HEIGHT);
	//set brush color to yellow
	CBrush yellow(RGB(255, 253, 150));
	//Draw Background
	pDC->FillRect(rect, &yellow);
	CRect rect1;
	//Grey collor to display score on
	CBrush grey(RGB(88, 89, 89));
	{
		SetRect(rect1, 0, WIDTH-200, WIDTH-90, HEIGHT-250);
		pDC->FillRect(rect1, &grey);
	}
	//food brush
	CBrush food(RGB(Red, Green, Blue));
	{
		SetRect(rect, snake.food.x - 5, snake.food.y - 5,
		snake.food.x + 5, snake.food.y + 5);
		pDC->FillRect(rect, &food);
	}
	//snake brush
	CBrush snakeBrush(RGB(Red, Green, Blue));
	//draw the snake's body
	for (vector<CPoint>::iterator iter = snake.SnakeBody.begin(); iter !=
		snake.SnakeBody.end(); ++iter) {
		SetRect(rect, (*iter).x - 5, (*iter).y - 5,
			(*iter).x + 5, (*iter).y + 5);
		pDC->FillRect(rect, &snakeBrush);
	}
	//score string
	CString score;
	//If the game is lost
	if (StateOfGame == 2)
		score.Format(_T("GAME OVER !!!"));
	if (StateOfGame == 1)
		score.Format(_T("GAME PAUSED"));
	else
		score.Format(_T("SCORE: %d"), (-3 + snake.SnakeBody.size()) * 5);
	pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	pDC->DrawText(score, -1, rect1, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX |
		DT_VCENTER | DT_END_ELLIPSIS);


}


// CSnakeView printing




// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeView message handlers




void CSnakeView::OnStartStart()
{
	//sets the game of state to 0, so runnning
	StateOfGame = 0;
	//set's the default direction okf te snake which is right
	snake.changeDirection(RIGHT);
	SetTimer(1, speed, NULL);
	srand((unsigned)time(NULL));
	snake.generateFood();
	snake.SnakeBody = snake.defaultState;
}
//on Pause method
void CSnakeView::OnPause()
{
	if (StateOfGame == 2 || speed <= 0) // game over OR difficulty not yet set
		return;
	else if (StateOfGame == 1) // resume
	{
		snake.changeDirection(directionBeforePause);
		directionBeforePause = 0;
		SetTimer(1, speed, NULL);
		StateOfGame = 0;
	}
	else // pause
	{
		directionBeforePause = snake.getDirection();
		snake.changeDirection(0); // passing 0 will cause the snake to pause
		StateOfGame = 1;
	}
}





void CSnakeView::OnRestartRestart()
{

	OnStartStart();
}


void CSnakeView::OnGridsizeSmall()
{
	HEIGHT = 500;
	WIDTH = 500;
	Invalidate();
	UpdateWindow();
}
//Method to set the color to red
void CSnakeView::OnColourRed()
{
	Red = 255;
	Green = 0;
	Blue = 0;
	Invalidate();
	UpdateWindow();

}

//Method to set the colour to black
void CSnakeView::OnColourBlack()
{

	Red = 0;
	Green = 0;
	Blue = 0;
	Invalidate();
	UpdateWindow();
}

//Method to set the colour to green
void CSnakeView::OnColourGreen()
{
	Red = 0;
	Green = 255;
	Blue = 0;
	Invalidate();
	UpdateWindow();
}


//Method to set the colour to blue
void CSnakeView::OnColourBlue()
{
	Red = 0;
	Green = 0;
	Blue = 255;
	Invalidate();
	UpdateWindow();
}

//sets the size of the window
void CSnakeView::OnGridsizeMedium()
{
	HEIGHT = 600;
	WIDTH = 600;

	Invalidate();
	UpdateWindow();
}

//sets the size of the window
void CSnakeView::OnGridsizeLarge()
{

	HEIGHT = 700;
	WIDTH = 600;
	Invalidate();
	UpdateWindow();
}




void CSnakeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	CView::OnRButtonUp(nFlags, point);
}

//Message handler for when one of the keys is pressed
void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//on key Up
	if (nChar == VK_UP)
		OnUp();
	//on key down
	if (nChar == VK_DOWN)
		OnDown();
	//on key left
	if (nChar == VK_LEFT)
		OnLeft();
	//on key right
	if (nChar == VK_RIGHT)
		OnRight();
	//on space
	if (nChar == VK_SPACE)
		OnSpace();

}

//on save game
void CSnakeView::OnAppSave()
{
	//saves the current saved game
	snake.savedSnake = snake.SnakeBody;
	if (StateOfGame == 1)
	//if the game has been pauses, we save the direction before it was paused
		DirectionSave = directionBeforePause;
	else
	//if the snake wasn't paused then we call the getDirection method
		DirectionSave = snake.getDirection();
	//set the save game exist to true
	saveGameExist = true;
	StateOfSavedGame = StateOfGame;
	CString string;
	string.Format(_T("Game Saved"));
	MessageBox(string);
}


void CSnakeView::OnAppLoad()
{
	if (!saveGameExist) // if no save was clicked
	{

		CString string;
		string.Format(_T("No Saved Game"));
		MessageBox(string);
		return;
	}
	snake.SnakeBody = snake.savedSnake;
	if (StateOfGame == 2) // load after game over
	{
		directionBeforePause = DirectionSave;
		snake.changeDirection(0);
		SetTimer(1,speed, NULL);
		srand((unsigned)time(NULL));
		snake.generateFood();
	}
	else if (StateOfSavedGame == 1) // game was paused when saved
	{
		directionBeforePause = DirectionSave;
		snake.changeDirection(0);
	}
	else
	{
		snake.changeDirection(DirectionSave);
		SetTimer(1, speed, NULL);
		srand((unsigned)time(NULL));
		snake.generateFood();
	}
	StateOfGame = StateOfSavedGame;
}

//When the slowest speed has been picked
void CSnakeView::OnSpeedSlow()
{
	CWnd* pParent = GetParent();
	CMenu* pMenu = pParent->GetMenu();
	pMenu->CheckMenuItem(ID_SPEED_SLOW, MF_CHECKED);
	pMenu->CheckMenuItem(ID_SPEED_MEDIUM, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_SPEED_FAST, MF_UNCHECKED);
	speed = 100;
	snakeSpeed = 5;
	OnStartStart();
}

//When the medium speed has been picked
void CSnakeView::OnSpeedMedium()
{
CWnd* pParent = GetParent();
CMenu* pMenu = pParent->GetMenu();
pMenu->CheckMenuItem(ID_SPEED_SLOW, MF_UNCHECKED);
pMenu->CheckMenuItem(ID_SPEED_MEDIUM, MF_CHECKED);
pMenu->CheckMenuItem(ID_SPEED_FAST, MF_UNCHECKED);
speed = 100;
snakeSpeed = 10;
OnStartStart();
}
//when the fastest speed has been picked
void CSnakeView::OnMediumFast()
{
	CWnd* pParent = GetParent();
	CMenu* pMenu = pParent->GetMenu();
	pMenu->CheckMenuItem(ID_SPEED_SLOW, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_SPEED_MEDIUM, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_SPEED_FAST, MF_CHECKED);
	speed = 100;
	snakeSpeed = 15;
	OnStartStart();
}
//when UP key has beeen pressed
void CSnakeView::OnUp()
{
	if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
		snake.changeDirection(UP);
}
//When the down key has been pressed
void CSnakeView::OnDown()
{
		if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
			snake.changeDirection(DOWN);
}
//When the right key has been pressed

void CSnakeView::OnRight()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(RIGHT);
}
//When the left key has been pressed
void CSnakeView::OnLeft()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(LEFT);
}
//When the OnSpace key has been pressed
void CSnakeView::OnSpace()
{
	if (StateOfGame == 2 || speed <= 0) // game over OR difficulty not yet set
		return;
	else if (StateOfGame == 1) // resume
	{
		snake.changeDirection(directionBeforePause);
		directionBeforePause = 0;
		SetTimer(1, speed, NULL);
		StateOfGame = 0;
	}
else // pause
{
	directionBeforePause = snake.getDirection();
	snake.changeDirection(0); // passing 0 will cause the snake to pause
	StateOfGame = 1;
}
}
