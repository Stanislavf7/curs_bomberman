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
		//�����
		PictureBox^ mainchar;		//�����������
		int spd_p;					//��������
		motion^ action_p;			//����������
		Point^ cur_p;//������� �������
		//�����
		array<bomb^>^ bomb_p;		//����� ����
		int bomb_cnt, bomb_on_map;	//���-�� ���� � ������, ���-�� ���� �� �����
		int bomb_power;				//�������� ����
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

		Void moveplayer(mov key);					//����������� ������

		bool try_place_bomb(de_explose^ func_a);	//������� ��������� �����
		Void remove_bomb(bomb^ cur_bomb);			//�������� ���������� �����

		PictureBox^ get_PB();						//������� PB ������
		Point get_char_pos();						//������� ������� ������
		int get_bomb_power();						//������� ���� ����
		Void set_bomb_power(int n_power);			//���������� ���� ����
		Void set_bomb_cnt(int n_cnt);				//���������� ���-�� ���� � ������
	};
};