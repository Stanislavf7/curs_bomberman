#include "menu.h"
#include "GameForm.cpp"

using namespace System::Collections::Generic;
using namespace malysh;
using namespace IO;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	menu form;
	Application::Run(% form);
}
inline Void menu::ngBut_Click(Object^ sender, EventArgs^ e)
{
	if (textBox1->Text == "")
	{
		MessageBox::Show("Вы не указали имя!"); 
	}
	else if (textBox1->Text->Length > 8)
	{
		MessageBox::Show("Вы ввели некорректное имя!");
	}
	else
	{
		map = gcnew GameForm(1, textBox1->Text);
		map->Show();
		map->FormClosing += gcnew FormClosingEventHandler(this, &menu::menu_show);
		this->Hide();
	}
	
}
inline Void menu::recbut_Click(Object^ sender, EventArgs^ e)
{
	textBox1->Visible = false;
	label1->Visible = false;
	label2->Visible = false;
	ngBut->Visible = false;
	recbut->Visible = false;
	helpbut->Visible = false;
	exitbut->Visible = false;
	CloseLegBut->Visible = true;
	textBox2->Visible = true;
	get_high_scores();
}
inline Void menu::helpbut_Click(Object^ sender, EventArgs^ e)
{
	ngBut->Visible = false;
	recbut->Visible = false;
	helpbut->Visible = false;
	exitbut->Visible = false;
	textBox1->Visible = false;
	label1->Visible = false;
	label2->Visible = false;
	num_htp = 1;
	HTP->Visible = true;
	change_htp(num_htp);
	this->Focus();
}
inline Void menu::CloseLegBut_Click(Object^ sender, EventArgs^ e)
{
	textBox1->Visible = true;
	label1->Visible = true;
	label2->Visible = true;
	ngBut->Visible = true;
	recbut->Visible = true;
	helpbut->Visible = true;
	exitbut->Visible = true;
	CloseLegBut->Visible = false;
	textBox2->Visible = false;
}
inline Void menu::exitbut_Click(Object^ sender, EventArgs^ e)
{
	this->Close();
}
inline Void menu::menu_show(Object^ sender, FormClosingEventArgs^ e)
{
	this->Show();
}
inline Void menu::menu_KeyDown(Object^ sender, KeyEventArgs^ e)
{
	if (HTP->Visible)
		switch (e->KeyCode)
		{
			case Keys::Escape:
				close_htp();
				break;
			case Keys::Left:
				change_htp(num_htp - 1);
				break;
			case Keys::Right:
				change_htp(num_htp + 1);
				break;
			default:
				break;
		}
}
inline Void menu::close_htp()
{
	HTP->Visible = false;
	ngBut->Visible = true;
	recbut->Visible = true;
	helpbut->Visible = true;
	exitbut->Visible = true;
	textBox1->Visible = true;
	label1->Visible = true;
	label2->Visible = true;
}
inline Void menu::change_htp(int n_num)
{
	if (n_num < 1 || n_num > 5) return;
	Bitmap^ image;
	String^ s = "pict/HTP" + n_num.ToString() + ".png";
	image = gcnew Bitmap(s);
	HTP->Image = image;
	num_htp = n_num;
}
// Собственный компаратор для записей
// Собран на основе различных сообщений,
// собраных с разных форумов
ref class RecordComparer : public System::Collections::Generic::IComparer<Tuple<int, String^>^>
{
public:
	virtual int Compare(Tuple<int, String^>^ x, Tuple<int, String^>^ y)
	{
		// Сравниваем первые элементы (очки)
		if (x->Item1 != y->Item1)
			return y->Item1 - x->Item1; // Сортировка по убыванию

		// Если очки равны, сравниваем вторые элементы (имена)
		return String::Compare(x->Item2, y->Item2); // Сортировка по возрастанию
	}
};
inline Void menu::get_high_scores()
{
	String^ file = "scores\\scores.txt";
	try
	{
		StreamReader^ in = File::OpenText(file);
		List<Tuple<int, String^>^>^ lst = gcnew List<Tuple<int, String^>^>();
		array<Char>^ sep = gcnew array<Char>{' '};
		bool fl = 0;
		while (!in->EndOfStream)
		{
			fl = 1;
			String^ s = in->ReadLine();
			array<String^>^ ar = s->Split(sep, System::StringSplitOptions::RemoveEmptyEntries);
			int score = Convert::ToInt32(ar[0]);
			String^ name = ar[1];
			lst->Add(Tuple::Create(score, name));
		};
		in->Close();
		if (fl)
		{
			RecordComparer^ comparer = gcnew RecordComparer();
			lst->Sort(comparer);
			int k = 0;
			textBox2->Text = L"Очки          Игрок" + Environment::NewLine;
			int displayLimit = Math::Min(5, lst->Count); // Ограничение на отображение первых 5 записей
			for (int i = 0; i < displayLimit; ++i)
			{
				textBox2->AppendText(String::Format("{0,-8} {1,10}{2}", lst[i]->Item1, lst[i]->Item2, Environment::NewLine));
			}
		}
		else
		{
			MessageBox::Show(this, "Рекордов ещё нет", "Ошибка", MessageBoxButtons::OK);
			CloseLegBut_Click(CloseLegBut, EventArgs::Empty);
			return;
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(this, "Рекордов ещё нет", "Ошибка", MessageBoxButtons::OK);
		CloseLegBut_Click(CloseLegBut, EventArgs::Empty);
		return;
	}
}