#pragma once
class Snake
{
public:
	Snake();
	CList<CPoint>* GetBody();
	bool IsInBody(CPoint point);
	bool Move(CPoint food);
	void DirectionChange(CPoint direction);
	//~Snake();
private:
	CList<CPoint> m_body;
	CPoint m_direction;
};

