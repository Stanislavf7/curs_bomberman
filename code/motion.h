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
		PictureBox^ unit;		//картинка юнита и все ео свойства
		array<array<PictureBox^>^>^ ghost;	//картинки ячеек
		array<array<obj>^>^ body;			//карта состояний
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
		Point get_pl_pos();				//получить позицию юнита
		bool change_pos(int x, int y);	//изменить позицию юнита
		bool can_move(int& x, int& y);	//проверка - можноли переместиться в выбраном направлении
	};
};
