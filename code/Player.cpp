#include "Player.h"
#include "motion.cpp"

using namespace malysh;

inline Void Player::moveplayer(mov key)
{
	switch (key)
	{
	case mov::top:
		action_p->change_pos(0, -spd_p);
		break;
	case mov::left:
		action_p->change_pos(-spd_p, 0);
		break;
	case mov::back:
		action_p->change_pos(0, spd_p);
		break;
	case mov::right:
		action_p->change_pos(spd_p, 0);
		break;
	}
};
inline Point Player::get_char_pos()
{
	return action_p->get_pl_pos();
}
inline PictureBox^ Player::get_PB()
{
	return mainchar;
}
inline bool Player::try_place_bomb(de_explose^ func_a)
{
	if (bomb_on_map + 1 > bomb_cnt) return false;
	bomb_p[bomb_on_map] = gcnew bomb(get_char_pos(),bomb_on_map);
	bomb_p[bomb_on_map]->set_delegate(func_a);
	bomb_p[bomb_on_map]->init_timer();
	++bomb_on_map;

	return true;
}
inline Void Player::remove_bomb(bomb^ cur_bomb)
{
	bomb_p[cur_bomb->get_num()] = nullptr;
	--bomb_on_map;
}
inline int Player::get_bomb_power()
{
	return bomb_power;
}
inline Void Player::set_bomb_power(int n_power)
{
	bomb_power = n_power;
}
inline Void Player::set_bomb_cnt(int n_cnt)
{
	bomb_cnt = n_cnt;
	bomb_p = gcnew array<bomb^>(bomb_cnt);
}