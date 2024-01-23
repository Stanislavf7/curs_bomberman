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
			Timer^ timer;				//таймер до взрыва
			de_explose^ func_frm_GF;	//делегат функции GF
			//принимает функцию взрыва, т.е. изменение картинок на поле и их состояний
			int num;					//номер бомбы
			Point^ cur_pos;				//позиция бомбы
			Void OnTick(Object^ sender, EventArgs^ e);	//действия по истечению таймера
			Void boom();				//функция запускающая функцию из делегата
		public:
			bomb(Point^ pos, int _num)
			{
				timer = gcnew Timer();
				cur_pos = pos;
				num = _num;
			};
			Void init_timer();			//запуска таймера до взрыва
			Void set_delegate(de_explose^ func);		//установить функцию в делегат
			int get_num() { return num; }				//получить номер бомбы
			Point^ get_bomb_pos();		//получить позицию бомбы
		};
};
