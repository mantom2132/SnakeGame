#include "stdafx.h"
#include "CFood.h"


CFood::CFood()
{
}


CFood::~CFood()
{
}
void CFood::Draw(CDC * pDC)
{

		// Create a pen for this object and initialize it
		CPen aPen;
		createAPen(aPen);

		// Select the pen and the null brush
		CPen* pOldPen{ pDC->SelectObject(&aPen) };
		CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };
		int pos = rand() % 1000;
		// Now draw the rectangle
		pDC->Rectangle(m_StartPoint.x + pos, m_StartPoint.y + pos,
			m_BottomRight.x+5 + pos, m_BottomRight.y+5+ pos);

		pDC->SelectObject(pOldBrush); // Restore the old brush
		pDC->SelectObject(pOldPen); // Restore the old pen
	}

// Constructor for a Food object
// CRectangle constructor
CFood::CFood(
	const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color }
{
	// Normalize the rectangle defining points
	m_StartPoint = CPoint{ (start.x, end.x),(start.y, end.y) };
	m_BottomRight = CPoint{ (start.x, end.x), (start.y, end.y) };
	// Ensure width and height between the points is at least 2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
		m_BottomRight.x = m_StartPoint.x + 2;
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
		m_BottomRight.y = m_StartPoint.y + 2;
	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}