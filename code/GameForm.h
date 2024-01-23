#pragma once
#include "Player.h"
#include "enemy.h"

namespace malysh
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	//главный класс, отвечает за создание игровго поля и взаимодействие игрока с игрой
	ref class GameForm : public Form
	{
	public:
		GameForm(int _lvl, String^ name)
		{
			player_name = name;		// получим имя игрока
			lvl = _lvl;				//новая игра всегда начинается с уровня 1
			InitializeComponent();	//включим все элементы
			init_game();			//инициализируем игровое поле
		}
	protected:
		~GameForm()
		{
			if (components)
			{
				delete components;
				timer_chk->Enabled = false;
				timer_clr->Enabled = false;
				timer_cng->Enabled = false;
				timer_scr->Enabled = false;
			}
		}
	private:
		//игровое поле
		Panel^ panelgame;		//панель игрового поля
		int Gridsz;				//размер ячеек
		const int sizeX = 23;	//кол-во ячеек на поле
		const int sizeY = 15;
		array<array<PictureBox^>^>^ pict; //картинки в ячейках
		array<array<obj>^>^ e_pict;		  //состояние ячеек

		int lvl;				//номер уровня
		int exit;				//выход(необходим для построения уровня) 
		Point ex_point;			//позиция выхода(необходима для логики игры)
		int bns_1;				//выход(необходим для построения уровня) 
		Point bns_1_point;		//позиция бонуса1(необходима для логики игры)
		int bns_2;				//выход(необходим для построения уровня) 
		Point bns_2_point;		//позиция бонуса2(необходима для логики игры)
		
		Player^ character;				//игрок
		int bmb_cnt, bmb_pow;			//данные о бомбах
		int player_score, bonus_score;	//очки игрока, бонусные очки
		String^ player_name;
		
		array<enemy^>^ mobs;	//враги
		int e_cnt;				//кол-во врагов на уровне

		//таймеры
		Timer^ timer_clr = gcnew Timer();	//таймер очистки огня
		Timer^ timer_chk = gcnew Timer();	//таймер проверки состояния игрока
		Timer^ timer_cng = gcnew Timer();	//таймер занавески (для плавной загрузки уровней)
		Timer^ timer_scr = gcnew Timer();	//таймер отсчитывающий бонусные очки

		PictureBox^ zat;			//картинка "занавеска"
		bool GameSost, nextlevel;	//булевы переменные состояния игры							  
		
		//кнопки
		MenuStrip^ menuStrip1;
		System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
		ToolStripMenuItem^ играToolStripMenuItem;
		ToolStripMenuItem^ новаяИграToolStripMenuItem;
		ToolStripSeparator^ toolStripSeparator1;
		ToolStripMenuItem^ выходToolStripMenuItem;

		IContainer^ components;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameForm::typeid));
			this->panelgame = (gcnew System::Windows::Forms::Panel());
			this->zat = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->играToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->новаяИграToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zat))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panelgame
			// 
			this->panelgame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panelgame->Location = System::Drawing::Point(0, 30);
			this->panelgame->Name = L"panelgame";
			this->panelgame->Size = System::Drawing::Size(1280, 720);
			this->panelgame->TabIndex = 2;
			// 
			// zat
			// 
			this->zat->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->zat->Location = System::Drawing::Point(0, 20);
			this->zat->Name = L"zat";
			this->zat->Size = System::Drawing::Size(1104, 730);
			this->zat->TabIndex = 4;
			this->zat->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->играToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1104, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// играToolStripMenuItem
			// 
			this->играToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->новаяИграToolStripMenuItem,
					this->toolStripSeparator1, this->выходToolStripMenuItem
			});
			this->играToolStripMenuItem->Name = L"играToolStripMenuItem";
			this->играToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->играToolStripMenuItem->Text = L"Игра";
			// 
			// новаяИграToolStripMenuItem
			// 
			this->новаяИграToolStripMenuItem->Name = L"новаяИграToolStripMenuItem";
			this->новаяИграToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->новаяИграToolStripMenuItem->Text = L"Новая игра";
			this->новаяИграToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::новаяИграToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(133, 6);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::выходToolStripMenuItem_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1104, 750);
			this->Controls->Add(this->panelgame);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->zat);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GameForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"игровое поле";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zat))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//инициализация
		Void init_game();			//запуск всех объектов
		Void makegrid(int Gredsz);	//создание поля
		Void makeunits(int sz);		//создание юнитов
		PictureBox^ createpic(Point p, int sz, obj cl_ch); // создание ячейки поля
		Void set_zat(int lvl);		//скроем от игрока отрисовку уровня

		//изменение состояний игры
		Void changepic(Point p, obj pic);	//изменение картинки в ячейки и её состояния
		Void GameForm_KeyDown(Object^ sender, KeyEventArgs^ e);	//передвижение игрока
		Void explose(bomb^ cur_bomb);		//взрыв и разрушение
		Void try_explose(Point vec, int len, Point^ from);	//отрисовка взрыва
		Void stop_fire();					//чистка поля от огня
		Void msg_EndGame(int res);			//сообщим игроку о результате его игры
		Void новаяИграToolStripMenuItem_Click(Object^ sender, EventArgs^ e);//горячая перезагрузка игры
		Void выходToolStripMenuItem_Click(Object^ sender, EventArgs^ e);	//вернёмся в меню

		//управление
		Void move(mov key); //изменение позиции игрока
		Void place_bomb();		//установка бомбы
		Void init_timer();		//инициализация таймер чистки от огня
		Void timer_Tick(Object^ sender, EventArgs^ e); //события таймера выше
		Void init_timer_chk();  //инициализация таймера, следящего за игроком
		Void timer_chk_Tick(Object^ sender, EventArgs^ e); //события таймера выше
		Void init_timer_cng(int lvl); //таймер для отрисовки поля
		Void timer_cng_Tick(Object^ sender, EventArgs^ e); //события таймера выше
		Void init_timer_scr();  //инициализация таймера, следящего за бонусными очками
		Void timer_scr_Tick(Object^ sender, EventArgs^ e); //события таймера выше	
	};
};
