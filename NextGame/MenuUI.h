#pragma once
#include "Renderable.h"
#include "Ship.h"

class MenuUI : public Renderable {
public:
	float3 stringColor = float3::One;

	bool isStart = true;
	bool isWin = false;
	bool isTurn = false;

	Ship* activeShip;

public:
	void Initialize();

	void Update();

	void Destroy();

	void Render() override;

	void StartMenu();

	void WinMenu();

	void TurnMenu(Ship* ship);

	void Restart();
};
