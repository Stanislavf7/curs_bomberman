#pragma once
#include "Player.h"
#include "enemy.h"

namespace malysh
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	//������� �����, �������� �� �������� ������� ���� � �������������� ������ � �����
	ref class GameForm : public Form
	{
	public:
		GameForm(int _lvl, String^ name)
		{
			player_name = name;		// ������� ��� ������
			lvl = _lvl;				//����� ���� ������ ���������� � ������ 1
			InitializeComponent();	//������� ��� ��������
			init_game();			//�������������� ������� ����
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
		//������� ����
		Panel^ panelgame;		//������ �������� ����
		int Gridsz;				//������ �����
		const int sizeX = 23;	//���-�� ����� �� ����
		const int sizeY = 15;
		array<array<PictureBox^>^>^ pict; //�������� � �������
		array<array<obj>^>^ e_pict;		  //��������� �����

		int lvl;				//����� ������
		int exit;				//�����(��������� ��� ���������� ������) 
		Point ex_point;			//������� ������(���������� ��� ������ ����)
		int bns_1;				//�����(��������� ��� ���������� ������) 
		Point bns_1_point;		//������� ������1(���������� ��� ������ ����)
		int bns_2;				//�����(��������� ��� ���������� ������) 
		Point bns_2_point;		//������� ������2(���������� ��� ������ ����)
		
		Player^ character;				//�����
		int bmb_cnt, bmb_pow;			//������ � ������
		int player_score, bonus_score;	//���� ������, �������� ����
		String^ player_name;
		
		array<enemy^>^ mobs;	//�����
		int e_cnt;				//���-�� ������ �� ������

		//�������
		Timer^ timer_clr = gcnew Timer();	//������ ������� ����
		Timer^ timer_chk = gcnew Timer();	//������ �������� ��������� ������
		Timer^ timer_cng = gcnew Timer();	//������ ��������� (��� ������� �������� �������)
		Timer^ timer_scr = gcnew Timer();	//������ ������������� �������� ����

		PictureBox^ zat;			//�������� "���������"
		bool GameSost, nextlevel;	//������ ���������� ��������� ����							  
		
		//������
		MenuStrip^ menuStrip1;
		System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
		ToolStripMenuItem^ ����ToolStripMenuItem;
		ToolStripMenuItem^ ���������ToolStripMenuItem;
		ToolStripSeparator^ toolStripSeparator1;
		ToolStripMenuItem^ �����ToolStripMenuItem;

		IContainer^ components;
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameForm::typeid));
			this->panelgame = (gcnew System::Windows::Forms::Panel());
			this->zat = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->�����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->����ToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1104, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->���������ToolStripMenuItem,
					this->toolStripSeparator1, this->�����ToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->���������ToolStripMenuItem->Text = L"����� ����";
			this->���������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::���������ToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(133, 6);
			// 
			// �����ToolStripMenuItem
			// 
			this->�����ToolStripMenuItem->Name = L"�����ToolStripMenuItem";
			this->�����ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->�����ToolStripMenuItem->Text = L"�����";
			this->�����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::�����ToolStripMenuItem_Click);
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
			this->Text = L"������� ����";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zat))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//�������������
		Void init_game();			//������ ���� ��������
		Void makegrid(int Gredsz);	//�������� ����
		Void makeunits(int sz);		//�������� ������
		PictureBox^ createpic(Point p, int sz, obj cl_ch); // �������� ������ ����
		Void set_zat(int lvl);		//������ �� ������ ��������� ������

		//��������� ��������� ����
		Void changepic(Point p, obj pic);	//��������� �������� � ������ � � ���������
		Void GameForm_KeyDown(Object^ sender, KeyEventArgs^ e);	//������������ ������
		Void explose(bomb^ cur_bomb);		//����� � ����������
		Void try_explose(Point vec, int len, Point^ from);	//��������� ������
		Void stop_fire();					//������ ���� �� ����
		Void msg_EndGame(int res);			//������� ������ � ���������� ��� ����
		Void ���������ToolStripMenuItem_Click(Object^ sender, EventArgs^ e);//������� ������������ ����
		Void �����ToolStripMenuItem_Click(Object^ sender, EventArgs^ e);	//������� � ����

		//����������
		Void move(mov key); //��������� ������� ������
		Void place_bomb();		//��������� �����
		Void init_timer();		//������������� ������ ������ �� ����
		Void timer_Tick(Object^ sender, EventArgs^ e); //������� ������� ����
		Void init_timer_chk();  //������������� �������, ��������� �� �������
		Void timer_chk_Tick(Object^ sender, EventArgs^ e); //������� ������� ����
		Void init_timer_cng(int lvl); //������ ��� ��������� ����
		Void timer_cng_Tick(Object^ sender, EventArgs^ e); //������� ������� ����
		Void init_timer_scr();  //������������� �������, ��������� �� ��������� ������
		Void timer_scr_Tick(Object^ sender, EventArgs^ e); //������� ������� ����	
	};
};
