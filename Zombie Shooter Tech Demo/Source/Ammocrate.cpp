#include "Ammocrate.h"

void Ammocrate::pickup(Player& t_player)
{
	t_player.ammoInReserve += 23;
	active = false;

}

