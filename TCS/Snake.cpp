#include "pch.h"
#include "Snake.h"

Snake::Snake()
{
	//初始长度为3，放在正中间
	m_body.AddTail(CPoint(15, 14));
	m_body.AddTail(CPoint(15, 15));
	m_body.AddTail(CPoint(15, 16));
	//初始化方向
	m_direction.SetPoint(0, -1);

}

CList<CPoint>* Snake::GetBody()
{
	return &m_body;
}

bool Snake::IsInBody(CPoint point)
{
	POSITION p = m_body.GetHeadPosition();
	while (p)
	{
		if (point == m_body.GetNext(p))
			return true;
	}
	return false;
}

bool Snake::Move(CPoint food)
{
	CPoint newHead = m_body.GetHead() + m_direction;
	if (IsInBody(newHead))
		return false;
	if (newHead.x < 0 || newHead.x >= 30 || newHead.y < 0 || newHead.y >= 30)
		return false;
	if (newHead != food)
	{
		m_body.RemoveTail();
	}
	m_body.AddHead(newHead);
	return true;
}

void Snake::DirectionChange(CPoint direction)
{
	if (m_direction.x + direction.x == 0 && m_direction.y + direction.y == 0)
		return;
	else
		m_direction = direction;
}