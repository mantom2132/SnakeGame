#pragma once
#include "CElement.h"
extern int WIDTH;
extern int HEIGHT;
class CFood : public CElement
{
public:
	virtual ~CFood();
	virtual void Draw(CDC* pDC) override; // Function to display a circle
										  // Constructor for a circle object
	CFood(const CPoint& start, const CPoint& end, COLORREF color);
protected:
	CPoint m_BottomRight; // Bottom-right point for defining circle
	CFood(); // Default constructor - should not be used
};