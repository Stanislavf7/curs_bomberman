#include "enemy.h"
#include "motion.cpp"
#include "cmath"

using namespace malysh;

inline Void enemy::init_timer()
{
	timer = gcnew Timer();
	timer->Interval = 100;
	timer->Tick += gcnew EventHandler(this, &malysh::enemy::OnTick);
	timer->Enabled = true;
}
inline Void enemy::init_timer2()
{
	timer = gcnew Timer();
	timer->Interval = 50;
	timer->Tick += gcnew EventHandler(this, &malysh::enemy::OnTick);
	timer->Enabled = true;
	timer_to_targ = gcnew Timer();
	timer_to_targ->Interval = 7000;
	timer_to_targ->Enabled = true;
	timer_to_targ->Tick += gcnew EventHandler(this, &malysh::enemy::OnTick2);

}
inline Void enemy::init_timer3()
{
	timer = gcnew Timer();
	timer->Interval = 50;
	timer->Tick += gcnew EventHandler(this, &malysh::enemy::OnTick);
	timer->Enabled = true;
	timer_to_targ = gcnew Timer();
	timer_to_targ->Interval = 4000;
	timer_to_targ->Enabled = true;
	timer_to_targ->Tick += gcnew EventHandler(this, &malysh::enemy::OnTick2);
}
inline Void enemy::OnTick(Object^ sender, EventArgs^ e)
{
	if ((pathstep > curstep) && (ob_e[path[curstep].Y][path[curstep].X] == obj::grass || ob_e[path[curstep].Y][path[curstep].X] == obj::fire))
	{
		if (movefoe(path[curstep])) movefoe(cur_e);
	}
	else getnewtarg();
}
inline Void enemy::OnTick2(Object^ sender, EventArgs^ e)
{
	try_go_to_targ();
	if ((pathstep > curstep) && (ob_e[path[curstep].Y][path[curstep].X] == obj::grass || ob_e[path[curstep].Y][path[curstep].X] == obj::fire))
	{
		if (movefoe(path[curstep])) movefoe(cur_e);
	}
	else getnewtarg();
}
inline bool enemy::movefoe(Point^ targ)
{
	int x = foe->Location.X;
	int y = foe->Location.Y;

	int t_x = (targ->X) * foe->Size.Width;
	int t_y = (targ->Y) * foe->Size.Height;

	int f_lb = x;
	int f_rb = x + foe->Size.Width;
	int f_ub = y;
	int f_db = y + foe->Size.Height;

	int t_lb = t_x;
	int t_rb = t_x + foe->Size.Width;
	int t_ub = t_y;
	int t_db = t_y + foe->Size.Height;

	bool fl = true;
	
	if ((f_ub > t_ub) && fl) //иду вверх
	{
		if(action_e->change_pos(0, -step_e))
		fl = false;
		f_ub -= step_e;
		if (f_ub == t_ub) ++curstep;
	}

	if ((f_lb > t_lb) && fl) //иду влево
	{
		if(action_e->change_pos(-step_e, 0))
		fl = false;
		f_lb -= step_e;
		if (f_lb == t_lb) ++curstep;
	}

	if ((f_db < t_db) && fl)//иду вниз
	{
		if(action_e->change_pos(0, step_e))
		fl = false;
		f_db += step_e;
		if (f_db == t_db) ++curstep;
	}

	if ((f_rb < t_rb) && fl)//иду вправо
	{
		if(action_e->change_pos(step_e, 0))
		fl = false;
		f_rb += step_e;
		if (f_rb == t_rb) ++curstep;
	}
	prev_pos->X = x; prev_pos->Y = y;
	cur_e = action_e->get_pl_pos();
	return fl;
}
inline bool enemy::is_path()
{
	//обнулим карту
	for (int y = 0; y < ob_e->GetLength(0); ++y)
		for (int x = 0; x < ob_e[y]->GetLength(0); ++x)
		{
			if (ob_e[y][x] == obj::grass || ob_e[y][x] == obj::exit || ob_e[y][x] == obj::bns_1 || ob_e[y][x] == obj::bns_2) path_e[y][x] = 0;
			else path_e[y][x] = -1;
		}

	bool has_ph; //есть ли проход
	bool fnd = false; //построен ли маршрут
	path_e[cur_e->Y][cur_e->X] = 1; //стартовая точка
	int num = 1; //длина пути + 1
	bool b1, b2, b3, b4;
	//примитивным bfs найдём путь
	do
	{
		has_ph = false;
		for (int y = 0; y < ob_e->GetLength(0); ++y)
			for (int x = 0; x < ob_e[y]->GetLength(0); ++x)
				if (path_e[y][x] == num)
				{
					b1 = mark(x + 1, y, num + 1);
					b2 = mark(x, y + 1, num + 1);
					b3 = mark(x - 1, y, num + 1);
					b4 = mark(x, y - 1, num + 1);
					//если можно продвинуться хотя бы в 1 сторону
					if (b1 || b2 || b3 || b4) has_ph = true; //проход есть
				}
		if (path_e[tar_e->Y][tar_e->X] > 0) //если нашли проход до цели
		{
			fnd = true;
			break;
		}
		++num;
	} while (has_ph); //пока есть проход или цель не достигнута

	//если путь нельзя построить — выходим
	if (!fnd) return false;

	//строим маршрут перемещения
	int x = tar_e->X, y = tar_e->Y;
	pathstep = num;
	while (num > 0)
	{
		path[num-1].X = x; path[num-1].Y = y;
		if (is_rev_path(x + 1, y, num))++x;
		else if (is_rev_path(x - 1, y, num))--x;
		else if (is_rev_path(x, y + 1, num))++y;
		else if (is_rev_path(x, y - 1, num))--y;
		--num;
	}
	return true;
}
inline bool enemy::mark(int x, int y, int n)
{
	if (x < 0 || x >= ob_e[0]->GetLength(0)) return false;
	if (y < 0 || y >= ob_e->GetLength(0)) return false;
	if (path_e[y][x] > 0) return false;
	if (path_e[y][x] != -1) { path_e[y][x] = n; return true;}
	return false;
}
inline bool enemy::is_rev_path(int x, int y, int n)
{
	if (x < 0 || x >= ob_e[0]->GetLength(0)) return false;
	if (y < 0 || y >= ob_e->GetLength(0)) return false;
	return path_e[y][x] == n;
}
inline Void enemy::getnewtarg()
{
	curstep = 0;
	bool fl;
	int stp = 0;
	do
	{
		fl = true;
		path->Clear(path, 0, 50);
		tar_e->X = rnd->Next(1, ob_e[0]->GetLength(0) - 1);
		tar_e->Y = rnd->Next(1, ob_e->GetLength(0) - 1);
		if (
			(ob_e[tar_e->Y][tar_e->X] == obj::grass ||
			ob_e[tar_e->Y][tar_e->X] == obj::exit ||
			ob_e[tar_e->Y][tar_e->X] == obj::bns_1 ||
			ob_e[tar_e->Y][tar_e->X] == obj::bns_2)
			&& (cur_e->X != tar_e->X || cur_e->Y != tar_e->Y)
			) fl = false;
	} while ((fl || !is_path()) && ++stp <= 50);
	if (stp > 50) { pathstep = 0; path->Clear(path, 0, 50); }
}
inline Point^ enemy::get_enem_pos()
{
	return action_e->get_pl_pos();
};

inline Void enemy::try_go_to_targ()
{
	Point tar_p = target->get_char_pos();
	tar_e->X = tar_p.X; tar_e->Y = tar_p.Y;
	curstep = 0;
	path->Clear(path, 0, 50);
	if (!is_path()) { pathstep = 0; path->Clear(path, 0, 50); getnewtarg(); }
}
inline int enemy::get_bounty() { return bounty; };
inline Void enemy::off_TM() { timer->Enabled = false; if (timer_to_targ)timer_to_targ->Enabled = false; };
inline int enemy::get_num() { return num; };
inline PictureBox^ enemy::get_PB() { return foe; };
