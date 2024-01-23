#pragma once
#include "bomb.h"
#include "motion.h"

namespace malysh
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	ref class Player
	{
	private:
		//игрок
		PictureBox^ mainchar;		//изображение
		int spd_p;					//скорость
		motion^ action_p;			//управление
		Point^ cur_p;//текущая позиция
		//бомбы
		array<bomb^>^ bomb_p;		//запас бомб
		int bomb_cnt, bomb_on_map;	//кол-во бомб у игрока, кол-во бомб на карте
		int bomb_power;				//мощность бомб
	public:
		Player() { mainchar = gcnew PictureBox(); };
		Player(PictureBox^ pl, array<array<PictureBox^>^>^ PB_p, array<array<obj>^>^ ob_p, int _bomb_cnt, int _bomb_power)
		{
			spd_p = 3;
			mainchar = pl;
			action_p = gcnew motion(pl, PB_p, ob_p, spd_p);
			cur_p = gcnew Point();

			bomb_cnt = _bomb_cnt;
			bomb_power = _bomb_power;
			bomb_p = gcnew array<bomb^>(bomb_cnt);
		}

		Void moveplayer(mov key);					//перемещение игрока

		bool try_place_bomb(de_explose^ func_a);	//попытка установки бомбы
		Void remove_bomb(bomb^ cur_bomb);			//удаление взорванной бомбы

		PictureBox^ get_PB();						//вернуть PB игрока
		Point get_char_pos();						//вернуть позицию игрока
		int get_bomb_power();						//вернуть силу бомб
		Void set_bomb_power(int n_power);			//установить силу бомб
		Void set_bomb_cnt(int n_cnt);				//установить кол-во бомб у игрока
	};
};