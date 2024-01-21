#pragma once
#include "Renderable.h"
#include "Ship.h"

class MenuUI : public Renderable {
public:
	float3 stringColor = float3::One;
	std::string text;

	bool isStart = true;
	bool isWin = false;
	bool isTurn = false;

	std::string winner;

	int pulsesLeft = 0;

public:
	void Initialize();

	void Update();

	void Destroy();

	void Render() override;

	void ClearMenu();

	void StartMenu();

	void WinMenu(std::string name);

	void TurnMenu(Ship* ship);

	void Restart();
};
