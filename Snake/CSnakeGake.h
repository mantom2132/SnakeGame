#pragma once

// CSnakeGake command target

class CSnakeGake : public CObject
{
private:
	CPoint m_StartPoint;
	CPoint m_EndingPoint;
	int m_penWidth;
public:
	CSnakeGake();
	virtual ~CSnakeGake();
};


