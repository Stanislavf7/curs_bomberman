#include "GameForm.h"
#include "Player.cpp"
#include "enemy.cpp"
using namespace malysh;
using namespace IO;

inline Void GameForm::makegrid(int Gridsz)
{
	Random^ rnd = gcnew Random();

	panelgame->Controls->Clear();

	// —оздаем двумерный массив PictureBox
	pict = gcnew array<array<PictureBox^>^>(sizeY);
	e_pict = gcnew array<array<obj>^>(sizeY);
	array<Point>^ arr = gcnew array<Point>(30);
	int k = 0;

	for (int i = 0; i < pict->Length; i++)
	{
		pict[i] = gcnew array<PictureBox^>(sizeX);
		e_pict[i] = gcnew array<obj>(sizeX);
		for (int j = 0; j < pict[i]->Length; j++)
		{
			Point p = Point(j, i);
			if (p.X == 0 || p.X == sizeX-1 || p.Y == 0 || p.Y == sizeY - 1) e_pict[p.Y][p.X] = obj::wall;
			else if ((p.X % 2 == 0) && (p.Y % 2 == 0)) e_pict[p.Y][p.X] = obj::wall;
			else if ((j == 1 && i == 1) || (j == 2 && i == 1) || (j == 1 && i == 2))e_pict[p.Y][p.X] = obj::grass;
			else
			{
				int tmp = rnd->Next() % 100 + 1;
				if (lvl == 1 && tmp > 82) 
				{ 
					e_pict[p.Y][p.X] = obj::brick;
					if (k < 20) { arr[k] = p; ++k; }
				}
				else if ((lvl == 2 || lvl == 3) && tmp > 74)
				{
					e_pict[p.Y][p.X] = obj::brick;
					if (k < 20) { arr[k] = p; ++k; }
				}
				else e_pict[p.Y][p.X] = obj::grass;
			}
			pict[p.Y][p.X] = createpic(p, Gridsz, e_pict[p.Y][p.X]);
			changepic(p, e_pict[p.Y][p.X]);
			panelgame->Controls->Add(pict[p.Y][p.X]);

		}
	}
	//дополнительные изменени€
	//бонусы, выход, правильный старт 
	int tmp;
	for (int i = 0; i < 3; ++i)
	{
		if (exit)
		{
			do
			{
				tmp = rnd->Next() % 20;
			} while (arr[tmp].X == 0);
			ex_point = arr[tmp];
			--exit;
		}
		else if (bns_1 && lvl>1)
		{
			do 
			{
				tmp = rnd->Next() % 30;
			} while (arr[tmp].X == 0 || arr[tmp] == ex_point);
			bns_1_point = arr[tmp];
			--bns_1;
		}
		else if (bns_2 && lvl>2)
		{
			do
			{
				tmp = rnd->Next() % 30;
			} while (arr[tmp].X == 0 || arr[tmp] == ex_point || arr[tmp] == bns_1_point);
			bns_2_point = arr[tmp];
			--bns_2;
		}
	}
}
inline Void GameForm::makeunits(int sz)
{
	//необходимые члены
	Random^ rnd = gcnew Random();
	Bitmap^ imagepl, ^ subimg;
	Point st_p = Point(1, 1);
	PictureBox^ unit = gcnew PictureBox();

	//создание игрока
	//позици€ игрока
	unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
	unit->Size = System::Drawing::Size(sz, sz);
	//подгрузка картинок
	imagepl = gcnew Bitmap("pict/pltop.png");
	subimg = gcnew Bitmap("pict/grass.png");
	unit->Image = dynamic_cast<Image^>(imagepl);
	unit->BackgroundImage = dynamic_cast<Image^>(subimg);
	unit->SizeMode = PictureBoxSizeMode(1);
	//вывод персонажа на панель
	panelgame->Controls->Add(unit);
	unit->BringToFront();
	character = gcnew Player(unit, pict, e_pict, bmb_cnt, bmb_pow);

	//создание врагов
	if (lvl == 1)
	{
		for (int count = 0; count < e_cnt; ++count)
		{
			unit = gcnew PictureBox();
			//позици€ врага
			bool fl = true;
			while (fl)
			{
				int tmp_x = rnd->Next() % (sizeX - 7);
				int tmp_y = rnd->Next() % (sizeY - 7);
				st_p = Point(6 + tmp_x, 6 + tmp_y);
				if (e_pict[st_p.Y][st_p.X] == obj::grass) fl = false;
			}
			unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
			unit->Size = System::Drawing::Size(sz, sz);
			//подгрузка картинок
			imagepl = gcnew Bitmap("pict/ballred.png");
			subimg = gcnew Bitmap("pict/grass.png");
			unit->Image = dynamic_cast<Image^>(imagepl);
			unit->BackgroundImage = dynamic_cast<Image^>(subimg);
			unit->SizeMode = PictureBoxSizeMode(1);
			//вывод персонажа на панель
			panelgame->Controls->Add(unit);
			unit->BringToFront();
			mobs[count] = gcnew enemy(unit, pict, e_pict, count, character, 1, 3);
		}
	}
	if (lvl == 2)
	{
		int count = 0;
		for (count; count < e_cnt/2; ++count)
		{
			unit = gcnew PictureBox();
			//позици€ врага
			bool fl = true;
			while (fl)
			{
				int tmp_x = rnd->Next() % (sizeX - 7);
				int tmp_y = rnd->Next() % (sizeY - 7);
				st_p = Point(6 + tmp_x, 6 + tmp_y);
				if (e_pict[st_p.Y][st_p.X] == obj::grass) fl = false;
			}
			unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
			unit->Size = System::Drawing::Size(sz, sz);
			//подгрузка картинок
			imagepl = gcnew Bitmap("pict/ballred.png");
			subimg = gcnew Bitmap("pict/grass.png");
			unit->Image = dynamic_cast<Image^>(imagepl);
			unit->BackgroundImage = dynamic_cast<Image^>(subimg);
			unit->SizeMode = PictureBoxSizeMode(1);
			//вывод персонажа на панель
			panelgame->Controls->Add(unit);
			unit->BringToFront();
			mobs[count] = gcnew enemy(unit, pict, e_pict, count, character, 1, 3);
		}
		for (count; count < e_cnt; ++count)
		{
			unit = gcnew PictureBox();
			//позици€ врага
			bool fl = true;
			while (fl)
			{
				int tmp_x = rnd->Next() % (sizeX - 7);
				int tmp_y = rnd->Next() % (sizeY - 7);
				st_p = Point(6 + tmp_x, 6 + tmp_y);
				if (e_pict[st_p.Y][st_p.X] == obj::grass) fl = false;
			}
			unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
			unit->Size = System::Drawing::Size(sz, sz);
			//подгрузка картинок
			imagepl = gcnew Bitmap("pict/blue.png");
			subimg = gcnew Bitmap("pict/grass.png");
			unit->Image = dynamic_cast<Image^>(imagepl);
			unit->BackgroundImage = dynamic_cast<Image^>(subimg);
			unit->SizeMode = PictureBoxSizeMode(1);
			//вывод персонажа на панель
			panelgame->Controls->Add(unit);
			unit->BringToFront();
			mobs[count] = gcnew enemy(unit, pict, e_pict, count, character, 2, 3);
		}
	}
	if (lvl == 3)
	{
		int count = 0;
		for (count; count < e_cnt-1; ++count)
		{
			unit = gcnew PictureBox();
			//позици€ врага
			bool fl = true;
			while (fl)
			{
				int tmp_x = rnd->Next() % (sizeX - 7);
				int tmp_y = rnd->Next() % (sizeY - 7);
				st_p = Point(6 + tmp_x, 6 + tmp_y);
				if (e_pict[st_p.Y][st_p.X] == obj::grass) fl = false;
			}
			unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
			unit->Size = System::Drawing::Size(sz, sz);
			//подгрузка картинок
			imagepl = gcnew Bitmap("pict/blue.png");
			subimg = gcnew Bitmap("pict/grass.png");
			unit->Image = dynamic_cast<Image^>(imagepl);
			unit->BackgroundImage = dynamic_cast<Image^>(subimg);
			unit->SizeMode = PictureBoxSizeMode(1);
			//вывод персонажа на панель
			panelgame->Controls->Add(unit);
			unit->BringToFront();
			mobs[count] = gcnew enemy(unit, pict, e_pict, count, character, 2, 3);
		}
		for (count; count < e_cnt; ++count)
		{
			unit = gcnew PictureBox();
			//позици€ врага
			bool fl = true;
			while (fl)
			{
				int tmp_x = rnd->Next() % (sizeX - 7);
				int tmp_y = rnd->Next() % (sizeY - 7);
				st_p = Point(6 + tmp_x, 6 + tmp_y);
				if (e_pict[st_p.Y][st_p.X] == obj::grass) fl = false;
			}
			unit->Location = Point(st_p.X * (sz), st_p.Y * (sz));
			unit->Size = System::Drawing::Size(sz, sz);
			//подгрузка картинок
			imagepl = gcnew Bitmap("pict/purp.png");
			subimg = gcnew Bitmap("pict/grass.png");
			unit->Image = dynamic_cast<Image^>(imagepl);
			unit->BackgroundImage = dynamic_cast<Image^>(subimg);
			unit->SizeMode = PictureBoxSizeMode(1);
			//вывод персонажа на панель
			panelgame->Controls->Add(unit);
			unit->BringToFront();
			mobs[count] = gcnew enemy(unit, pict, e_pict, count, character, 3, 3);
		}
	}
}

inline PictureBox^ GameForm::createpic(Point p, int sz, obj pic)
{
	PictureBox^ tmp = gcnew PictureBox();

	tmp->Location = Point(p.X * sz, p.Y * sz);
	tmp->Size = System::Drawing::Size(sz, sz);
	tmp->SizeMode = PictureBoxSizeMode(1); //StretchImage
	

	return tmp;
}
inline Void GameForm::changepic(Point p, obj n_pic)
{
	Bitmap^ image,^ subimg;
	PictureBox^ player;
	if (character) player = character->get_PB();
	//загрузим необходимую картинку
	switch (n_pic)
	{
	case obj::brick:
		image = gcnew Bitmap("pict/brick.png");
		pict[p.Y][p.X]->Image = image;
		break;
	case obj::wall:
		image = gcnew Bitmap("pict/wall.png");
		pict[p.Y][p.X]->Image = image;
		break;
	case obj::bomb:
		image = gcnew Bitmap("pict/bomb.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::exit_bmb:
		image = gcnew Bitmap("pict/bomb.png");
		subimg = gcnew Bitmap("pict/exit.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::exit:
		image = gcnew Bitmap("pict/exit.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fire:
		image = gcnew Bitmap("pict/fire.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireDE:
		image = gcnew Bitmap("pict/fireDE.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireDT:
		image = gcnew Bitmap("pict/fireDT.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireLE:
		image = gcnew Bitmap("pict/fireLE.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireLT:
		image = gcnew Bitmap("pict/fireLT.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireRE:
		image = gcnew Bitmap("pict/fireRE.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireRT:
		image = gcnew Bitmap("pict/fireRT.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireTE:
		image = gcnew Bitmap("pict/fireTE.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::fireTT:
		image = gcnew Bitmap("pict/fireTT.png");
		subimg = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		pict[p.Y][p.X]->BackgroundImage = subimg;
		break;
	case obj::pltop:
		image = gcnew Bitmap("pict/PLback.png");
		player->Image = image;
		break;
	case obj::pldown:
		image = gcnew Bitmap("pict/PLtop.png");
		player->Image = image;
		break;
	case obj::plleft:
		image = gcnew Bitmap("pict/PLleft.png");
		player->Image = image;
		break;
	case obj::plright:
		image = gcnew Bitmap("pict/PLright.png");
		player->Image = image;
		break;
	case obj::bns_1:
		image = gcnew Bitmap("pict/bns_1.png");
		pict[p.Y][p.X]->Image = image;
		break;
	case obj::bns_2:
		image = gcnew Bitmap("pict/bns_2.png");
		pict[p.Y][p.X]->Image = image;
		break;
	default:
		image = gcnew Bitmap("pict/grass.png");
		pict[p.Y][p.X]->Image = image;
		break;
	}
	//помен€ем состо€ние
	e_pict[p.Y][p.X] = n_pic;
}

inline Void GameForm::GameForm_KeyDown(Object^ sender, KeyEventArgs^ e)
{
	if (GameSost)
	{
		switch (e->KeyCode)
		{
		case Keys::W:
			changepic(Point(0, 0), obj::pltop);
			move(malysh::mov::top); break;
		case Keys::D:
			changepic(Point(0, 0), obj::plright);
			move(malysh::mov::right); break;
		case Keys::S:
			changepic(Point(0, 0), obj::pldown);
			move(malysh::mov::back); break;
		case Keys::A:
			changepic(Point(0, 0), obj::plleft);
			move(malysh::mov::left); break;
		case Keys::Space:
			place_bomb(); break;
		}
	};
}
inline Void GameForm::move(malysh::mov key)
{
	character->moveplayer(key);
	Point p = character->get_char_pos();
	if (!e_cnt)
	{
		if (p.X == ex_point.X && p.Y == ex_point.Y) msg_EndGame(1);
	}
	if (p.X == bns_1_point.X && p.Y == bns_1_point.Y) 
	{
		character->set_bomb_cnt(++bmb_cnt);
		changepic(p, obj::grass);
		bns_1_point = Point(0, 0);
	}
	if (p.X == bns_2_point.X && p.Y == bns_2_point.Y) 
	{
		character->set_bomb_power(++bmb_pow);
		changepic(p, obj::grass);
		bns_2_point = Point(0, 0);
	}
}
inline Void GameForm::place_bomb()
{
	
	Point cur_pl_p = character->get_char_pos();
	if (e_pict[cur_pl_p.Y][cur_pl_p.X] == obj::bomb) return;
	if (character->try_place_bomb(gcnew de_explose(this, &GameForm::explose)))
		if (e_pict[cur_pl_p.Y][cur_pl_p.X] == obj::exit)changepic(cur_pl_p, obj::exit_bmb);
		else changepic(cur_pl_p, obj::bomb);
}

inline Void GameForm::explose(bomb^ cur_bomb)
{
	int len_expl = character->get_bomb_power();
	Point^ b_p = cur_bomb->get_bomb_pos();
	if (e_pict[b_p->Y][b_p->X] == obj::exit_bmb)
		changepic(Point(b_p->X, b_p->Y), obj::exit);
	else changepic(Point(b_p->X, b_p->Y), obj::fire);
	try_explose(Point(0, 1), len_expl, b_p);
	try_explose(Point(1, 0), len_expl, b_p);
	try_explose(Point(0, -1), len_expl, b_p);
	try_explose(Point(-1, 0), len_expl, b_p);

	character->remove_bomb(cur_bomb);
	init_timer();

	for each (enemy^ mob in mobs)
	{
		if (mob)
		{
			Point^ p_e = mob->get_enem_pos();
			if (e_pict[p_e->Y][p_e->X] == obj::fire ||
				e_pict[p_e->Y][p_e->X] == obj::fireTE ||
				e_pict[p_e->Y][p_e->X] == obj::fireDE ||
				e_pict[p_e->Y][p_e->X] == obj::fireRE ||
				e_pict[p_e->Y][p_e->X] == obj::fireLE ||
				e_pict[p_e->Y][p_e->X] == obj::fireTT ||
				e_pict[p_e->Y][p_e->X] == obj::fireRT ||
				e_pict[p_e->Y][p_e->X] == obj::fireDT ||
				e_pict[p_e->Y][p_e->X] == obj::fireLT)
			{
				player_score += mob->get_bounty();
				mob->off_TM();
				mobs[mob->get_num()] = nullptr;
				panelgame->Controls->Remove(mob->get_PB());
				delete(mob);
				--e_cnt;
			}
		}
	}
}
inline Void GameForm::try_explose(Point vec, int len, Point^ from)
{
	if (vec.X > 0)
	{
		for (int i = 1; i <= len; ++i)
		{
			if (e_pict[from->Y][from->X + i] == obj::wall) break;
			if (e_pict[from->Y][from->X + i] == obj::brick || e_pict[from->Y][from->X + i] == obj::exit ||
				e_pict[from->Y][from->X + i] == obj::bns_1 || e_pict[from->Y][from->X + i] == obj::bns_2 || i == len)
			{
				if (ex_point.X == from->X + i && ex_point.Y == from->Y) changepic(Point(from->X + i, from->Y), obj::exit);
				else if (bns_1_point.X == from->X + i && bns_1_point.Y == from->Y) changepic(Point(from->X + i, from->Y), obj::bns_1);
				else if (bns_2_point.X == from->X + i && bns_2_point.Y == from->Y) changepic(Point(from->X + i, from->Y), obj::bns_2);
				else changepic(Point(from->X + i, from->Y), obj::fireRE);
				break;
			}
			changepic(Point(from->X + i, from->Y), obj::fireRT);
		}
	}
	if (vec.X < 0)
	{
		for (int i = 1; i <= len; ++i)
		{
			if (e_pict[from->Y][from->X - i] == obj::wall) break;
			if (e_pict[from->Y][from->X - i] == obj::brick || e_pict[from->Y][from->X - i] == obj::exit ||
				e_pict[from->Y][from->X - i] == obj::bns_1 || e_pict[from->Y][from->X - i] == obj::bns_2 || i == len)
			{
				if (ex_point.X == from->X - i && ex_point.Y == from->Y) changepic(Point(from->X - i, from->Y), obj::exit);
				else if (bns_1_point.X == from->X - i && bns_1_point.Y == from->Y) changepic(Point(from->X - i, from->Y), obj::bns_1);
				else if (bns_2_point.X == from->X - i && bns_2_point.Y == from->Y) changepic(Point(from->X - i, from->Y), obj::bns_2);
				else changepic(Point(from->X - i, from->Y), obj::fireLE);
				break;
			}
			changepic(Point(from->X - i, from->Y), obj::fireLT);
		}
	}
	if (vec.Y > 0)
	{
		for (int i = 1; i <= len; ++i)
		{
			if (e_pict[from->Y + i][from->X] == obj::wall) break;
			if (e_pict[from->Y + i][from->X] == obj::brick || e_pict[from->Y + i][from->X] == obj::exit ||
				e_pict[from->Y + i][from->X] == obj::bns_1 || e_pict[from->Y + i][from->X] == obj::bns_2 || i == len)
			{
				if (ex_point.X == from->X && ex_point.Y == from->Y + i) changepic(Point(from->X, from->Y + i), obj::exit);
				else if (bns_1_point.X == from->X && bns_1_point.Y == from->Y + i) changepic(Point(from->X, from->Y + i), obj::bns_1);
				else if (bns_2_point.X == from->X && bns_2_point.Y == from->Y + i) changepic(Point(from->X, from->Y + i), obj::bns_2);
				else changepic(Point(from->X, from->Y + i), obj::fireDE);
				break;
			}
			changepic(Point(from->X, from->Y + i), obj::fireDT);
		}
	}
	if (vec.Y < 0)
	{
		for (int i = 1; i <= len; ++i)
		{
			if (e_pict[from->Y - i][from->X] == obj::wall) break;
			if (e_pict[from->Y - i][from->X] == obj::brick || e_pict[from->Y - i][from->X] == obj::exit ||
				e_pict[from->Y - i][from->X] == obj::bns_1 || e_pict[from->Y - i][from->X] == obj::bns_2 || i == len)
			{
				if (ex_point.X == from->X && ex_point.Y == from->Y - i) changepic(Point(from->X, from->Y - i), obj::exit);
				else if (bns_1_point.X == from->X && bns_1_point.Y == from->Y - i) changepic(Point(from->X, from->Y - i), obj::bns_1);
				else if (bns_2_point.X == from->X && bns_2_point.Y == from->Y - i) changepic(Point(from->X, from->Y - i), obj::bns_2);
				else changepic(Point(from->X, from->Y - i), obj::fireTE);
				break;
			}
			changepic(Point(from->X, from->Y - i), obj::fireTT);
		}
	}
}
inline Void GameForm::init_timer()
{
	timer_clr->Enabled = true;
	timer_clr->Interval = 1000;
	timer_clr->Tick += gcnew System::EventHandler(this, &malysh::GameForm::timer_Tick);
}
inline Void GameForm::timer_Tick(Object^ sender, EventArgs^ e)
{
	timer_clr->Enabled = false;
	stop_fire();
}
inline Void GameForm::stop_fire()
{
	for (int y = 1; y < sizeY; ++y)
		for (int x = 1; x < sizeX; ++x)
			if (e_pict[y][x] == obj::fire ||
				e_pict[y][x] == obj::fireDE ||
				e_pict[y][x] == obj::fireLE ||
				e_pict[y][x] == obj::fireRE ||
				e_pict[y][x] == obj::fireTE ||
				e_pict[y][x] == obj::fireDT ||
				e_pict[y][x] == obj::fireLT ||
				e_pict[y][x] == obj::fireRT ||
				e_pict[y][x] == obj::fireTT
				) changepic(Point(x, y), obj::grass);
}
inline Void GameForm::init_timer_chk()
{
	timer_chk->Enabled = true;
	if (lvl == 1) timer_chk->Interval = 50;
	if (lvl == 1) timer_chk->Tick += gcnew System::EventHandler(this, &malysh::GameForm::timer_chk_Tick);
}
inline Void GameForm::timer_chk_Tick(Object^ sender, EventArgs^ e)
{
	if (nextlevel && (timer_cng->Enabled == false))
	{
		++lvl;
		set_zat(lvl);
		init_game();
	}
	Point pp = character->get_char_pos();
	if (e_pict[pp.Y][pp.X] == obj::fire ||
		e_pict[pp.Y][pp.X] == obj::fireDE ||
		e_pict[pp.Y][pp.X] == obj::fireRE ||
		e_pict[pp.Y][pp.X] == obj::fireTE ||
		e_pict[pp.Y][pp.X] == obj::fireLE ||
		e_pict[pp.Y][pp.X] == obj::fireDT ||
		e_pict[pp.Y][pp.X] == obj::fireRT ||
		e_pict[pp.Y][pp.X] == obj::fireTT ||
		e_pict[pp.Y][pp.X] == obj::fireLT
		) { GameSost = false; timer_chk->Enabled = false; msg_EndGame(0); }
	for each (enemy^ mob in mobs)
	{
		if (mob && (mob->get_enem_pos()->X == pp.X && mob->get_enem_pos()->Y == pp.Y))
		{ GameSost = false; timer_chk->Enabled = false; msg_EndGame(0); }
	}
}
inline Void GameForm::msg_EndGame(int res)
{
	timer_scr->Enabled = false;
	if (res == 0)
	{
		init_timer_cng(4);
		MessageBox::Show("¬аш результат: " + player_score.ToString());
		String^ mes = String::Format("{0,-8} {1,10}\n", player_score, player_name);
		StreamWriter^ out = gcnew StreamWriter("scores\\scores.txt",true);
		out->Write(mes);
		out->Close();
	}
	if (res == 1) 
	{
		if(bonus_score > 0) player_score += bonus_score;
		if (lvl == 3)
		{ 
			set_zat(6);
			MessageBox::Show("¬аш результат: " + player_score.ToString()); 
			String^ mes = String::Format("{0,-8} {1,10}\n", player_score, player_name);
			StreamWriter^ out = gcnew StreamWriter("scores\\scores.txt", true);
			out->Write(mes);
			out->Close();
		}
		else { nextlevel = true; init_timer_cng(5); }
	}
}
inline Void GameForm::init_timer_cng(int res)
{
	set_zat(res);
	timer_cng->Enabled = true;
	timer_cng->Interval = 3000;
	timer_cng->Tick += gcnew System::EventHandler(this, &malysh::GameForm::timer_cng_Tick);
}
inline Void GameForm::timer_cng_Tick(Object^ sender, EventArgs^ e)
{
	timer_cng->Enabled = false;
	zat->Hide();
}
inline Void GameForm::set_zat(int res)
{
	Bitmap^ image;
	if (res == 1)image = gcnew Bitmap("pict/stage_1.png");
	if (res == 2)image = gcnew Bitmap("pict/stage_2.png");
	if (res == 3)image = gcnew Bitmap("pict/stage_3.png");
	if (res == 4)image = gcnew Bitmap("pict/Game_over.png");
	if (res == 5) { image = gcnew Bitmap("pict/Congrats.png"); GameSost = false; }
	if (res == 6) { image = gcnew Bitmap("pict/Game_end.png"); GameSost = false; }
	zat->Image = image;
	zat->Show();
	zat->BringToFront();
}
inline Void GameForm::init_timer_scr()
{
	timer_scr->Enabled = true;
	if (lvl == 1) timer_scr->Interval = 1000;
	if (lvl == 1) timer_scr->Tick += gcnew System::EventHandler(this, &GameForm::timer_scr_Tick);
}
inline Void GameForm::timer_scr_Tick(Object^ sender, EventArgs^ e)
{
	--bonus_score;
}
inline Void GameForm::init_game()
{
	init_timer_cng(lvl); //поставим экран с текущим уровнем
	//в это врем€ будем измен€ть игровое поле
	//установим кол-во врагов
	if (lvl == 1) { e_cnt = 3; bmb_pow = 1; bmb_cnt = 1; player_score = 0; } //инф. о бомбах мен€етс€ только на 1-ом уровне
	if (lvl == 2) e_cnt = 4;
	if (lvl == 3) e_cnt = 4;
	mobs = gcnew array<enemy^>(e_cnt);
	//обновим выход и бонусы
	exit = 1; bns_1 = 1; bns_2 = 1;
	bonus_score = 205;
	//определим размер €чеек пол€
	if ((panelgame->Width / sizeX) < (panelgame->Height / sizeY))
		Gridsz = panelgame->Width / sizeX;
	else
		Gridsz = panelgame->Height / sizeY;
	//заполним всЄ картинками
	makegrid(Gridsz);
	makeunits(Gridsz);
	//запустим таймер, который будет отслеживать игрока
	init_timer_chk();
	init_timer_scr();
	//изменим булевые переменные
	GameSost = true;
	nextlevel = false;
}
inline Void GameForm::нова€»граToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	lvl = 1;
	init_game();
}
inline Void GameForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}