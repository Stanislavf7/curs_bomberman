#pragma once
#include "GameForm.h"

namespace malysh 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class menu : public Form
	{
		public:
			menu(void)
			{
				InitializeComponent();
			}
		protected:
			~menu()
			{
				if (components)
				{
					delete components;
				}
			}
		private: 
			System::Windows::Forms::Label^ label1;			//
			TextBox^ textBox1;								//���� ����� ����� ������
			System::Windows::Forms::Label^ label2;			//

			Button^ ngBut;			//������ ����� ����
			GameForm^ map;			//��������� �� ������ ������ ������� ����

			Button^ recbut;			//������ ������� ��������
			TextBox^ textBox2;		//������� ��������
			Button^ CloseLegBut;	//������ �������� ������� ��������

			Button^ helpbut;		//������ �������
			PictureBox^ HTP;		//��������� �� �������� ��� �������
			int num_htp;			//����� �������� � �������

			Button^ exitbut;		//������ ������
			System::ComponentModel::Container^ components;
		#pragma region Windows Form Designer generated code	
			void InitializeComponent(void)
			{
				this->ngBut = (gcnew System::Windows::Forms::Button());
				this->recbut = (gcnew System::Windows::Forms::Button());
				this->helpbut = (gcnew System::Windows::Forms::Button());
				this->exitbut = (gcnew System::Windows::Forms::Button());
				this->CloseLegBut = (gcnew System::Windows::Forms::Button());
				this->HTP = (gcnew System::Windows::Forms::PictureBox());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HTP))->BeginInit();
				this->SuspendLayout();
				// 
				// ngBut
				// 
				this->ngBut->Location = System::Drawing::Point(240, 90);
				this->ngBut->Name = L"ngBut";
				this->ngBut->Size = System::Drawing::Size(120, 50);
				this->ngBut->TabIndex = 0;
				this->ngBut->Text = L"����� ����";
				this->ngBut->UseVisualStyleBackColor = true;
				this->ngBut->Click += gcnew System::EventHandler(this, &menu::ngBut_Click);
				// 
				// recbut
				// 
				this->recbut->Location = System::Drawing::Point(240, 146);
				this->recbut->Name = L"recbut";
				this->recbut->Size = System::Drawing::Size(120, 50);
				this->recbut->TabIndex = 1;
				this->recbut->Text = L"�������";
				this->recbut->UseVisualStyleBackColor = true;
				this->recbut->Click += gcnew System::EventHandler(this, &menu::recbut_Click);
				// 
				// helpbut
				// 
				this->helpbut->Location = System::Drawing::Point(240, 202);
				this->helpbut->Name = L"helpbut";
				this->helpbut->Size = System::Drawing::Size(120, 50);
				this->helpbut->TabIndex = 2;
				this->helpbut->Text = L"��� ������";
				this->helpbut->UseVisualStyleBackColor = true;
				this->helpbut->Click += gcnew System::EventHandler(this, &menu::helpbut_Click);
				// 
				// exitbut
				// 
				this->exitbut->Location = System::Drawing::Point(240, 258);
				this->exitbut->Name = L"exitbut";
				this->exitbut->Size = System::Drawing::Size(120, 50);
				this->exitbut->TabIndex = 3;
				this->exitbut->Text = L"�����";
				this->exitbut->UseVisualStyleBackColor = true;
				this->exitbut->Click += gcnew System::EventHandler(this, &menu::exitbut_Click);
				// 
				// CloseLegBut
				// 
				this->CloseLegBut->Location = System::Drawing::Point(462, 396);
				this->CloseLegBut->Name = L"CloseLegBut";
				this->CloseLegBut->Size = System::Drawing::Size(110, 33);
				this->CloseLegBut->TabIndex = 4;
				this->CloseLegBut->Text = L"�����";
				this->CloseLegBut->UseVisualStyleBackColor = true;
				this->CloseLegBut->Visible = false;
				this->CloseLegBut->Click += gcnew System::EventHandler(this, &menu::CloseLegBut_Click);
				// 
				// HTP
				// 
				this->HTP->Location = System::Drawing::Point(80, 10);
				this->HTP->Name = L"HTP";
				this->HTP->Size = System::Drawing::Size(420, 420);
				this->HTP->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				this->HTP->TabIndex = 5;
				this->HTP->TabStop = false;
				this->HTP->Visible = false;
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(13, 13);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(85, 13);
				this->label1->TabIndex = 6;
				this->label1->Text = L"�������������";
				// 
				// textBox1
				// 
				this->textBox1->Location = System::Drawing::Point(13, 30);
				this->textBox1->Name = L"textBox1";
				this->textBox1->Size = System::Drawing::Size(85, 20);
				this->textBox1->TabIndex = 7;
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(13, 57);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(120, 13);
				this->label2->TabIndex = 8;
				this->label2->Text = L"(�� ����� 8 ��������)";
				// 
				// textBox2
				// 
				this->textBox2->Font = (gcnew System::Drawing::Font(L"Courier New", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(204)));
				this->textBox2->Location = System::Drawing::Point(139, 57);
				this->textBox2->Multiline = true;
				this->textBox2->Name = L"textBox2";
				this->textBox2->ReadOnly = true;
				this->textBox2->Size = System::Drawing::Size(308, 333);
				this->textBox2->TabIndex = 9;
				this->textBox2->Text = L"����          �����";
				this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				this->textBox2->Visible = false;
				// 
				// menu
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(584, 441);
				this->Controls->Add(this->textBox2);
				this->Controls->Add(this->label2);
				this->Controls->Add(this->textBox1);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->HTP);
				this->Controls->Add(this->CloseLegBut);
				this->Controls->Add(this->exitbut);
				this->Controls->Add(this->helpbut);
				this->Controls->Add(this->recbut);
				this->Controls->Add(this->ngBut);
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->MaximizeBox = false;
				this->MinimizeBox = false;
				this->Name = L"menu";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"���������";
				this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &menu::menu_KeyDown);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HTP))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
		#pragma endregion
														//����������� �������
			Void ngBut_Click(Object^ sender, EventArgs^ e);
			Void recbut_Click(Object^ sender, EventArgs^ e);
			Void helpbut_Click(Object^ sender, EventArgs^ e);
			Void CloseLegBut_Click(Object^ sender, EventArgs^ e);
			Void exitbut_Click(Object^ sender, EventArgs^ e);
			Void menu_show(Object^ sender, FormClosingEventArgs^ e);
			Void menu_KeyDown(Object^ sender, KeyEventArgs^ e);
														//������� ������ �� ��������
			Void close_htp();
			Void change_htp(int n_num);
														//������� ������ � �������� ��������	
			Void get_high_scores();
	};
}
