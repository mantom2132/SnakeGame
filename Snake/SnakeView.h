
// SnakeView.h : interface of the CSnakeView class
//
#include <stdbool.h>
#pragma once


class CSnakeView : public CView
{
protected:
	void OnTimer(UINT_PTR nIDEvent);
	// create from serialization only
	CSnakeView();
	DECLARE_DYNCREATE(CSnakeView)

	// Attributes
public:
	CSnakeDoc * GetDocument() const;



	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:


	// Implementation
public:
	virtual ~CSnakeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:


public:
	//starts the game
	afx_msg void OnStartStart();
	//pauses the game
	afx_msg void OnPause();
	//restarts
	afx_msg void OnRestartRestart();
	//sets the gridsize to small
	afx_msg void OnGridsizeSmall();
	//sets the colour to red
	afx_msg void OnColourRed();
	//sets the colour to black
	afx_msg void OnColourBlack();
	//sets the colour to green
	afx_msg void OnColourGreen();
	//sets the colour to blue
	afx_msg void OnColourBlue();
	//sets the colour to gridSizeMedium
	afx_msg void OnGridsizeMedium();
	//sets the colour to large
	afx_msg void OnGridsizeLarge();



#ifndef _DEBUG  // debug version in SnakeView.cpp
	inline CSnakeDoc* CSnakeView::GetDocument() const
	{
		return reinterpret_cast<CSnakeDoc*>(m_pDocument);
	}
#endif
	
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//when pressing the arrows
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//saves the game
	afx_msg void OnAppSave();
	//loads 
	afx_msg void OnAppLoad();
	//sets the speed to slow
	afx_msg void OnSpeedSlow();
	//sets the speed to medium
	afx_msg void OnSpeedMedium();
	//sets the speed to fast
	afx_msg void OnMediumFast();
	//when up arrow is pressed
	afx_msg void OnUp();
	//wehn down arrow is pressed
	afx_msg void OnDown();
	//when the right arrow is pressed
	afx_msg void OnRight();
	//when the left arrow is pressed
	afx_msg void OnLeft();
	//when the space arrow is pressed
	afx_msg void OnSpace();

};