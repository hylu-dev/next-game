#include "stdafx.h"
#include "MenuUI.h"
#include <string>

void MenuUI::Initialize() {
	Renderable::Initialize();
}

void MenuUI::Update() {

}

void MenuUI::Destroy() {
	Renderable::Destroy();
}

void MenuUI::Render() {
	text.clear();
	if (isStart) {
		stringColor = { 1, 0, 1 };
		App::Print(440, 680, "Dark Star", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		App::Print(440, 680, "         :", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		App::Print(440, 680, "          Showdown", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		App::Print(435, 80, "Press ENTER to start", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		text = "Separated by a dying star.";
		App::Print(20, 740, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Two pilots from opposing nations have";
		App::Print(20, 720, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "their last chance to prove themselves.";
		App::Print(20, 700, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 0, 1 };
		text = "This game requires 2 players.";
		App::Print(20, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (isTurn) {
		stringColor = { 1, 1, 0 };
		text = std::to_string(pulsesLeft);
		text += " pulses until supernova";
		App::Print(420, 700, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		text = std::to_string(turnsUntilPulse);
		text += " turns until next pulse";
		App::Print(420, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (isWin) {
		stringColor = { 1, 1, 0 };
		text = winner;
		text += " wins";
		App::Print(440, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		text = "Press BACK to restart";
		App::Print(435, 80, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (isDraw) {
		stringColor = float3::One;
		text = "Both pilots have perished within the supernova";
		App::Print(350, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		text = "Press BACK to restart";
		App::Print(435, 80, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (!isStart && !isWin && !isDraw) {
		stringColor = { 1, 1, 0 };
		text = "Press ENTER to end turn";
		App::Print(435, 80, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}


	if (App::IsKeyPressed('H')) {
		stringColor = { 1, 1, 0 };
		text = "Ship Controls";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		text = "Yaw: A/D";
		App::Print(20, 620, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Thrust/Reverse: W/S";
		App::Print(20, 600, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Pitch: Space/Shift";
		App::Print(20, 580, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Fire Weapon: F";
		App::Print(20, 560, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);

		stringColor = { 1, 1, 0 };
		text = "Spend resourcees: 100 Scrap each";
		App::Print(20, 520, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		text = "Upgrade Weapon: 1";
		App::Print(20, 500, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Upgrade Speed: 2";
		App::Print(20, 480, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Repair 20 points: 3";
		App::Print(20, 460, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Replenish 20 Fuel: 4";
		App::Print(20, 440, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);

		stringColor = { 1, 1, 0 };
		text = "Tips";
		App::Print(20, 400, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = float3::One;
		text = "After a pulse, ALL players regain fuel and take 20 damage";
		App::Print(20, 380, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "A pulse will pull everything closer together";
		App::Print(20, 360, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "You can trigger a pulse by shooting the star but it ends your turn";
		App::Print(20, 340, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Upgrade your ship before engaging the enemy";
		App::Print(20, 320, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Flying into the star hurts...";
		App::Print(20, 300, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	else {
		stringColor = { 1, 1, 0 };
		std::string text = "Hold H for help";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
}

void MenuUI::StartMenu() {
	isStart = true;
	isWin = false;
	isTurn = false;
	isDraw = false;
}

void MenuUI::WinMenu(std::string name) {
	winner = name;
	isStart = false;
	isWin = true;
	isTurn = false;
	isDraw = false;
}

void MenuUI::DrawMenu() {
	isStart = false;
	isWin = false;
	isTurn = false;
	isDraw = true;
}

void MenuUI::TurnMenu() {
	isStart = false;
	isWin = false;
	isTurn = true;
	isDraw = false;
}

