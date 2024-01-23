#include "bomb.h"

using namespace malysh;

inline Void bomb::init_timer()
{
	timer = gcnew Timer();
	timer->Enabled = true;
	timer->Interval = 3000;
	timer->Tick += gcnew System::EventHandler(this, &malysh::bomb::OnTick);
}

inline Void bomb::OnTick(System::Object^ sender, System::EventArgs^ e)
{
	boom();
	timer->Enabled = false;
	return;
}

inline Void bomb::set_delegate(de_explose^ func)
{
	func_frm_GF = func;
}

inline Void bomb::boom()
{
	func_frm_GF(this);
}
inline Point^ bomb::get_bomb_pos() { return cur_pos; };
;