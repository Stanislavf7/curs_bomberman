#pragma once
#include "motion.h"

using namespace malysh;

inline bool motion::change_pos(int x, int y)
{
	if (can_move(x, y))
		unit->Location = Point(unit->Location.X + x, unit->Location.Y + y);
	if (x == 0 && y == 0) return false;
	return true;
}
inline bool motion::can_move(int& x, int& y)
{
	/*
	движение на углах
	*Ч-- ---*-Ч- ---*-Ч- ---*
	|       |       |       |
			6       7
	|       |       |       |
	*Ч--5---1-Ч- ---2-Ч-8---*
	|       |       |       |
			   p_p
	|       |       |       |
	*Ч-12---4-Ч- ---3-Ч-9---*
	|       |       |       |
		   11       10
	|       |       |       |
	*Ч-- ---*-Ч- ---*-Ч- ---*
	*/

	Point p_point = get_pl_pos();

	Point corner1 = Point(unit->Location.X, unit->Location.Y);
	Point corner2 = Point(unit->Location.X + unit->Size.Width, unit->Location.Y);
	Point corner3 = Point(unit->Location.X + unit->Size.Width, unit->Location.Y + unit->Size.Height);
	Point corner4 = Point(unit->Location.X, unit->Location.Y + unit->Size.Height);

	Point corner5, corner6, corner7, corner8, corner9, corner10, corner11, corner12;

	corner5 = corner6 = Point(ghost[p_point.Y][p_point.X]->Location.X, ghost[p_point.Y][p_point.X]->Location.Y);
	corner7 = corner8 = Point(ghost[p_point.Y][p_point.X + 1]->Location.X, ghost[p_point.Y][p_point.X + 1]->Location.Y);
	corner9 = corner10 = Point(ghost[p_point.Y + 1][p_point.X + 1]->Location.X, ghost[p_point.Y + 1][p_point.X + 1]->Location.Y);
	corner11 = corner12 = Point(ghost[p_point.Y + 1][p_point.X]->Location.X, ghost[p_point.Y + 1][p_point.X]->Location.Y);

	if (y < 0 && 
		(
			body[p_point.Y - 1][p_point.X] == obj::grass || 
			body[p_point.Y - 1][p_point.X] == obj::exit ||
			body[p_point.Y - 1][p_point.X] == obj::fire ||
			body[p_point.Y - 1][p_point.X] == obj::fireDE ||
			body[p_point.Y - 1][p_point.X] == obj::fireRE ||
			body[p_point.Y - 1][p_point.X] == obj::fireTE ||
			body[p_point.Y - 1][p_point.X] == obj::fireLE ||
			body[p_point.Y - 1][p_point.X] == obj::fireDT ||
			body[p_point.Y - 1][p_point.X] == obj::fireRT ||
			body[p_point.Y - 1][p_point.X] == obj::fireTT ||
			body[p_point.Y - 1][p_point.X] == obj::fireLT ||
			body[p_point.Y - 1][p_point.X] == obj::bns_1 ||
			body[p_point.Y - 1][p_point.X] == obj::bns_2 
		))
	{
		if ((corner5.X - 2 * spd) <= corner1.X || (corner8.X + 2 * spd) >= corner2.X)
		{
			if ((corner8.X + 2 * spd) >= corner2.X && corner1.X >= corner5.X)
			{
				if ((corner2.X - corner8.X) <= spd)
				{
					x = corner8.X - corner2.X; return true;
				}
				if ((corner2.X - corner8.X) <= 2 * spd)
				{
					y = 0;  x = -spd; return true;
				}
			}
			if ((corner5.X - 2 * spd) <= corner1.X && corner2.X <= corner8.X)
			{
				if ((corner5.X - corner1.X) <= spd)
				{
					x = corner5.X - corner1.X; return true;
				}
				if ((corner5.X - corner1.X) <= 2 * spd)
				{
					y = 0;  x = spd; return true;
				}
			}
		}
		x = 0; y = 0;
		return true;
	}

	if (x > 0 && 
		(
			body[p_point.Y][p_point.X + 1] == obj::grass ||
			body[p_point.Y][p_point.X + 1] == obj::exit ||
			body[p_point.Y][p_point.X + 1] == obj::fire ||
			body[p_point.Y][p_point.X + 1] == obj::fireDE ||
			body[p_point.Y][p_point.X + 1] == obj::fireRE ||
			body[p_point.Y][p_point.X + 1] == obj::fireTE ||
			body[p_point.Y][p_point.X + 1] == obj::fireLE ||
			body[p_point.Y][p_point.X + 1] == obj::fireDT ||
			body[p_point.Y][p_point.X + 1] == obj::fireRT ||
			body[p_point.Y][p_point.X + 1] == obj::fireTT ||
			body[p_point.Y][p_point.X + 1] == obj::fireLT ||
			body[p_point.Y][p_point.X + 1] == obj::bns_1 ||
			body[p_point.Y][p_point.X + 1] == obj::bns_2
		))
	{
		if ((corner7.Y - 2 * spd) <= corner2.Y || (corner10.Y + 2 * spd) >= corner3.Y)
		{
			if ((corner10.Y + 2 * spd) >= corner3.Y && corner2.Y >= corner7.Y)
			{
				if ((corner3.Y - corner10.Y) <= spd)
				{
					y = corner10.Y - corner3.Y; return true;
				}
				if ((corner3.Y - corner10.Y) <= 2 * spd)
				{
					x = 0;  y = -spd; return true;
				}
			}
			if ((corner7.Y - 2 * spd) <= corner2.Y && corner10.Y >= corner3.Y)
			{
				if ((corner7.Y - corner2.Y) <= spd)
				{
					y = corner7.Y - corner2.Y; return true;
				}
				if ((corner7.Y - corner2.Y) <= 2 * spd)
				{
					x = 0;  y = spd; return true;
				}
			}
		}
		x = 0; y = 0;
		return true;
	}

	if (y > 0 && 
		(
			body[p_point.Y + 1][p_point.X] == obj::grass ||
			body[p_point.Y + 1][p_point.X] == obj::exit ||
			body[p_point.Y + 1][p_point.X] == obj::fire ||
			body[p_point.Y + 1][p_point.X] == obj::fireDE ||
			body[p_point.Y + 1][p_point.X] == obj::fireRE ||
			body[p_point.Y + 1][p_point.X] == obj::fireTE ||
			body[p_point.Y + 1][p_point.X] == obj::fireLE ||
			body[p_point.Y + 1][p_point.X] == obj::fireDT ||
			body[p_point.Y + 1][p_point.X] == obj::fireRT ||
			body[p_point.Y + 1][p_point.X] == obj::fireTT ||
			body[p_point.Y + 1][p_point.X] == obj::fireLT ||
			body[p_point.Y + 1][p_point.X] == obj::bns_1 ||
			body[p_point.Y + 1][p_point.X] == obj::bns_2
		))
	{
		if ((corner12.X - 2 * spd) <= corner4.X || (corner9.X + 2 * spd) >= corner3.X)
		{
			if ((corner9.X + 2 * spd) >= corner3.X && corner4.X >= corner12.X)
			{
				if ((corner3.X - corner9.X) <= spd)
				{
					x = corner9.X - corner3.X; return true;
				}
				if ((corner3.X - corner9.X) <= 2 * spd)
				{
					y = 0;  x = -spd; return true;
				}
			}
			if ((corner12.X - 2 * spd) <= corner4.X && corner3.X <= corner9.X)
			{
				if ((corner12.X - corner4.X) <= spd)
				{
					x = corner12.X - corner4.X; return true;
				}
				if ((corner12.X - corner4.X) <= 2 * spd)
				{
					y = 0;  x = spd; return true;
				}
			}
		}
		x = 0; y = 0;
		return true;
	}

	if (x < 0 && 
		(
			body[p_point.Y][p_point.X - 1] == obj::grass ||
			body[p_point.Y][p_point.X - 1] == obj::fire ||
			body[p_point.Y][p_point.X - 1] == obj::exit ||
			body[p_point.Y][p_point.X - 1] == obj::fireDE ||
			body[p_point.Y][p_point.X - 1] == obj::fireRE ||
			body[p_point.Y][p_point.X - 1] == obj::fireTE ||
			body[p_point.Y][p_point.X - 1] == obj::fireLE ||
			body[p_point.Y][p_point.X - 1] == obj::fireDT ||
			body[p_point.Y][p_point.X - 1] == obj::fireRT ||
			body[p_point.Y][p_point.X - 1] == obj::fireTT ||
			body[p_point.Y][p_point.X - 1] == obj::fireLT ||
			body[p_point.Y][p_point.X - 1] == obj::bns_1 ||
			body[p_point.Y][p_point.X - 1] == obj::bns_2
		))
	{
		if ((corner6.Y - 2 * spd) <= corner1.Y || (corner11.Y + 2 * spd) >= corner4.Y)
		{
			if ((corner11.Y + 2 * spd) >= corner4.Y && corner1.Y >= corner6.Y)
			{
				if ((corner4.Y - corner11.Y) <= spd)
				{
					y = corner11.Y - corner4.Y; return true;
				}
				if ((corner4.Y - corner11.Y) <= 2 * spd)
				{
					x = 0;  y = -spd; return true;
				}
			}
			if ((corner6.Y - 2 * spd) <= corner1.Y && corner11.Y >= corner4.Y)
			{
				if ((corner6.Y - corner1.Y) <= spd)
				{
					y = corner6.Y - corner1.Y; return true;
				}
				if ((corner6.Y - corner1.Y) <= 2 * spd)
				{
					x = 0;  y = spd; return true;
				}
			}
		}
		x = 0; y = 0;
		return true;
	}


	/*
	движение в соседние €чейки
	*Ч-- ---*-Ч- ---*-Ч- ---*
	|       |       |       |

	|       |       |       |
	*Ч-- ---*-Чd_b--*-Ч- ---*
	|       |       |       |
		   r_b p_p l_b
	|       |       |       |
	*Ч-- ---*-Чu_b--*-Ч- ---*
	|       |       |       |

	|       |       |       |
	*Ч-- ---*-Ч- ---*-Ч- ---*
	*/

	int left_bound = ghost[p_point.Y][p_point.X + 1]->Location.X;
	int right_bound = ghost[p_point.Y][p_point.X]->Location.X;
	int up_bound = ghost[p_point.Y + 1][p_point.X]->Location.Y;
	int down_bound = ghost[p_point.Y][p_point.X]->Location.Y;

	int pl_left_bound = unit->Location.X;
	int pl_right_bound = unit->Location.X + unit->Size.Width;
	int pl_up_bound = unit->Location.Y;
	int pl_down_bound = unit->Location.Y + unit->Size.Height;

	if (x > 0 && (pl_right_bound + x) > left_bound)
		x = left_bound - pl_right_bound - 1;
	if (x < 0 && (pl_left_bound + x) < right_bound)
		x = right_bound - pl_left_bound;
	if (y > 0 && (pl_down_bound + y) > up_bound)
		y = up_bound - pl_down_bound - 1;
	if (y < 0 && (pl_up_bound + y) < down_bound)
		y = down_bound - pl_up_bound;

	return true;
}
inline Point motion::get_pl_pos()
{
	Point^ cur = gcnew Point();
	cur->X = unit->Location.X + unit->Size.Width / 2;
	cur->Y = unit->Location.Y + unit->Size.Height / 2;
	for (int i = 0; i < ghost->GetLength(0); ++i)
		for (int j = 0; j < ghost[i]->GetLength(0); ++j)
			if ((ghost[i][j]->Location.X <= cur->X) &&
				(ghost[i][j]->Location.Y <= cur->Y) &&
				((ghost[i][j]->Location.X + ghost[i][j]->Size.Width) >= cur->X) &&
				((ghost[i][j]->Location.Y + ghost[i][j]->Size.Height) >= cur->Y))
				return Point(j, i);
	return Point();
};
