#include "stdafx.h"
#include "PlayerUI.h"
#include <string>

void PlayerUI::Initialize() {
	Renderable::Initialize();

	ship = parentEntity->GetComponent<Ship>();
}

void PlayerUI::Update() {
	health = ship->health;
	bulletLoaded = ship->bulletLoaded;
	fuel = ship->fuel;
	scrap = ship->scrap;

	healthString = "HEALTH: ";
	for (int i = 0; i < health; i += 5) {
		healthString += "o";
	}

	fuelString = "FUEL: ";
	for (int i = 0; i < fuel; i += 5) {
		fuelString += "|";
	}

	scrapString = "SCRAP: ";
	scrapString += std::to_string(scrap);

	bulletString = "WEAPON: ";
	bulletString += bulletLoaded ? "LOADED" : "EMPTY";
}

void PlayerUI::Destroy() {
	Renderable::Destroy();
}

void PlayerUI::Render() {
	if (ship->active) {
		stringColor = float3::One;
		App::Print(20, 740, healthString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		App::Print(20, 720, fuelString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		App::Print(20, 700, scrapString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		stringColor = bulletLoaded ? stringColor = { 0,1,0 } : stringColor = { 1,0,0 };
		App::Print(20, 680, bulletString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);
	}
}