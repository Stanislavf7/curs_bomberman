#pragma once
#include "motion.h"
#include "Player.h"

namespace malysh
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	ref class enemy
	{
	private:
		PictureBox^ foe;				//противник
		motion^ action_e;				//управление
		int step_e, num, dif, bounty;	//скорость, номер, сложность, награда
		Point^ cur_e;					//текущая позиция врага

		Player^ target;					//игрок, нужен для получения его позиции
		Point^ tar_e, ^ prev_pos;		//позиция цели, прошлая позиция
		Timer^ timer, ^ timer_to_targ;	//таймеры

		array<array<obj>^>^ ob_e;		//карта состояний

		array<array<int>^>^ path_e;		//путь до цели (примитивный BFS)
		int pathstep, curstep;			//кол-во шагов в пути, текущий шаг
		array<Point>^ path;				//путь
		static Random^ rnd;				//рандом для выбора целевой точки
	public:
		enemy() { foe = gcnew PictureBox(); };
		enemy(PictureBox^ _unit_e, array<array<PictureBox^>^>^ PB_e, array<array<obj>^>^ _ob_e, int _num, Player^ _target, int _dif, int _spd)
		{
			foe = _unit_e;
			ob_e = _ob_e;
			num = _num;
			target = _target;
			dif = _dif;
			action_e = gcnew motion();
			tar_e = gcnew Point();
			prev_pos = gcnew Point();
			pathstep = 0, curstep = 0;
			step_e = _spd;
			rnd = gcnew Random();

			path_e = gcnew array<array<int>^>(PB_e->GetLength(0));
			for (int i = 0; i < PB_e->GetLength(0); i++)
			{
				path_e[i] = gcnew array<int>(PB_e[i]->GetLength(0));
			}
			path = gcnew array<Point>(path_e->GetLength(0) * path_e[0]->GetLength(0));

			action_e = gcnew motion(_unit_e, PB_e, _ob_e, step_e);

			cur_e = action_e->get_pl_pos();
			tar_e->X = cur_e->X; tar_e->Y = cur_e->Y;
			if (dif == 1) { init_timer(); bounty = 50; }
			if (dif == 2) { init_timer2(); bounty = 100; }
			if (dif == 3) { init_timer3(); bounty = 200; }
		};
		//таймеры
		Void init_timer();	//таймеры по сложности
		Void init_timer2();
		Void init_timer3();
		Void OnTick(Object^ sender, EventArgs^ e);	//перемещение по такту и сложности
		Void OnTick2(Object^ sender, EventArgs^ e);
		Void off_TM();		//выключение таймера

		bool movefoe(Point^ targ);	//перемещение в точку
		bool is_path();				//есть ли путь до точки
		bool mark(int x, int y, int n);	//отметить точку (постройка нового пути)
		bool is_rev_path(int x, int y, int n);	//восстановление пути 

		Void getnewtarg();			//получить позицию игрока
		Void try_go_to_targ();		//попробовать дойти до игрока

		int get_num();			//получить номер врага
		PictureBox^ get_PB();	//получить PB врага
		Point^ get_enem_pos();	//получить позицию врага
		int get_bounty();		//получить награду игрока
	};
};
