#include "stdafx.h"
#include "PlayerUI.h"
#include <string>

void PlayerUI::Initialize() {
	Renderable::Initialize();

	ship = parentEntity->GetComponent<Ship>();
	assert(ship != nullptr);
}

void PlayerUI::Update() {
	health = ship->health;
	ammo = ship->ammo;
	fuel = ship->fuel;
	scrap = ship->scrap;

	healthString = "HEALTH: ";
	for (int i = 0; i < health; i += 10) {
		healthString += "o";
	}

	fuelString = "FUEL: ";
	for (int i = 0; i < fuel; i += 5) {
		fuelString += "|";
	}

	bulletString = "AMMO: ";
	bulletString += std::to_string(ammo);

	scrapString = "SCRAP: ";
	scrapString += std::to_string(scrap);
}

void PlayerUI::Destroy() {
	Renderable::Destroy();
}

void PlayerUI::Render() {
	if (ship->active) {
		stringColor = float3::One;
		App::Print(20, 740, healthString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		App::Print(20, 720, fuelString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		stringColor = ammo > 0 ? stringColor = { 0,1,0 } : stringColor = { 1,0,0 };
		App::Print(20, 700, bulletString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);
		stringColor = float3::One;
		App::Print(20, 680, scrapString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);
	}
}
