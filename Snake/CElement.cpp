// CElement.cpp : implementation file
//

#include "stdafx.h"
#include "Snake.h"
#include "CElement.h"


// CElement

void CElement::createAPen(CPen & aPen)
{
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
	{
		// Pen creation failed
		AfxMessageBox(_T("Pen creation failed."), MB_OK);
		AfxAbort();
	}
}

CElement::CElement()
{
}

CElement::~CElement()
{
}
CElement::CElement(const CPoint& start, COLORREF color, int penWidth) :
	m_StartPoint{ start }, m_PenWidth{ penWidth }, m_Color{ color } {}

// CElement member functions
