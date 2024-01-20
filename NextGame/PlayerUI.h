#pragma once
#include "Renderable.h"
#include "ShipA.h"

class PlayerUI : public Renderable {
private:
	ShipA* ship = nullptr;

	int health = 0;
	int fuel = 0;
	int scrap = 0;
	bool bulletLoaded = 0;

	float3 stringColor = float3::One;
	std::string healthString;
	std::string fuelString;
	std::string bulletString;
	std::string scrapString;


public:
	void Initialize();

	void Update();

	void Destroy();

	void Render() override;
};

