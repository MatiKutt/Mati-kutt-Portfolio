#include "Player.h"
#include "pickupWeapon.h"
#include "..\include\pickupHandler.h"






bool pickupHandler::checkCollisions(Player& t_player, pickupWeapon& t_pickup)
{
	if (t_pickup.collider->checkCollisionsWithPlayer(t_player))
	{
		pickupType t_type = t_pickup.type;
		{
			switch (t_type)
			{
			default:
				break;
			case pickupType::Ammo:
				t_player.reload();
				break;
			case pickupType::Health:
				t_player.addHealth();
				break;

			case pickupType::Pint:
				t_player.addPints();
				break;



			}
		}
	}
	return t_pickup.collider->checkCollisionsWithPlayer(t_player);
}
