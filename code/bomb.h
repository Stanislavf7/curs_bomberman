#pragma once
namespace malysh
{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;

		ref class bomb;

		delegate void de_explose(bomb^);

		ref class bomb
		{
		private:
			Timer^ timer;				//������ �� ������
			de_explose^ func_frm_GF;	//������� ������� GF
			//��������� ������� ������, �.�. ��������� �������� �� ���� � �� ���������
			int num;					//����� �����
			Point^ cur_pos;				//������� �����
			Void OnTick(Object^ sender, EventArgs^ e);	//�������� �� ��������� �������
			Void boom();				//������� ����������� ������� �� ��������
		public:
			bomb(Point^ pos, int _num)
			{
				timer = gcnew Timer();
				cur_pos = pos;
				num = _num;
			};
			Void init_timer();			//������� ������� �� ������
			Void set_delegate(de_explose^ func);		//���������� ������� � �������
			int get_num() { return num; }				//�������� ����� �����
			Point^ get_bomb_pos();		//�������� ������� �����
		};
};
