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
		PictureBox^ foe;				//���������
		motion^ action_e;				//����������
		int step_e, num, dif, bounty;	//��������, �����, ���������, �������
		Point^ cur_e;					//������� ������� �����

		Player^ target;					//�����, ����� ��� ��������� ��� �������
		Point^ tar_e, ^ prev_pos;		//������� ����, ������� �������
		Timer^ timer, ^ timer_to_targ;	//�������

		array<array<obj>^>^ ob_e;		//����� ���������

		array<array<int>^>^ path_e;		//���� �� ���� (����������� BFS)
		int pathstep, curstep;			//���-�� ����� � ����, ������� ���
		array<Point>^ path;				//����
		static Random^ rnd;				//������ ��� ������ ������� �����
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
		//�������
		Void init_timer();	//������� �� ���������
		Void init_timer2();
		Void init_timer3();
		Void OnTick(Object^ sender, EventArgs^ e);	//����������� �� ����� � ���������
		Void OnTick2(Object^ sender, EventArgs^ e);
		Void off_TM();		//���������� �������

		bool movefoe(Point^ targ);	//����������� � �����
		bool is_path();				//���� �� ���� �� �����
		bool mark(int x, int y, int n);	//�������� ����� (��������� ������ ����)
		bool is_rev_path(int x, int y, int n);	//�������������� ���� 

		Void getnewtarg();			//�������� ������� ������
		Void try_go_to_targ();		//����������� ����� �� ������

		int get_num();			//�������� ����� �����
		PictureBox^ get_PB();	//�������� PB �����
		Point^ get_enem_pos();	//�������� ������� �����
		int get_bounty();		//�������� ������� ������
	};
};
