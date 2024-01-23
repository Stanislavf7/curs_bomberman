#pragma once
namespace malysh
{
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	enum class mov
	{
		top, left, back, right
	};
	enum class obj
	{
		grass, brick, wall, bomb,
		pltop, plleft, pldown, plright,
		fire, fireDE, fireDT, fireLE, fireLT,
		fireRE, fireRT, fireTE, fireTT,
		exit, bns_1, bns_2, exit_bmb
	};
	ref class motion
	{
	private:
		PictureBox^ unit;		//�������� ����� � ��� �� ��������
		array<array<PictureBox^>^>^ ghost;	//�������� �����
		array<array<obj>^>^ body;			//����� ���������
		int spd;
	public:
		motion() { unit = gcnew PictureBox(); }
		motion(PictureBox^ _unit, array<array<PictureBox^>^>^ PB, array<array<obj>^>^ ob, int _spd)
		{
			unit = _unit;
			ghost = PB;
			body = ob;
			spd = _spd;
		}
		Point get_pl_pos();				//�������� ������� �����
		bool change_pos(int x, int y);	//�������� ������� �����
		bool can_move(int& x, int& y);	//�������� - ������� ������������� � �������� �����������
	};
};
