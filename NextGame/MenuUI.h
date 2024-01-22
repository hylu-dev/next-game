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
	bool isDraw = false;

	bool isPulse = false;

	std::string winner;

	int pulsesLeft = 0;
	int turnsUntilPulse = 0;

public:
	void Initialize();

	void Update();

	void Destroy();

	void Render() override;

	void StartMenu();

	void WinMenu(std::string name);

	void DrawMenu();

	void TurnMenu();
};
