#include "stdafx.h"
#include "PlayerUI.h"
#include <string>

void PlayerUI::Initialize() {
	Renderable::Initialize();

	ship = parentEntity->GetComponent<ShipA>();
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

	std::string fuelString = "FUEL: ";
	for (int i = 0; i < health; i += 5) {
		fuelString += "|";
	}

	std::string bulletString = "WEAPON: ";
	if (bulletLoaded) {
		stringColor = { 0,1,0 };
		bulletString += "LOADED";
	}
	else {
		stringColor = { 1,0,0 };
		bulletString += "EMPTY";
	}
}

void PlayerUI::Destroy() {
	Renderable::Destroy();
}

void PlayerUI::Render() {
	if (ship->active) {

		App::Print(20, 740, healthString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		App::Print(20, 720, fuelString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		App::Print(20, 700, bulletString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);

		stringColor = float3::One;
		App::Print(20, 680, scrapString.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_9_BY_15);
	}
}
