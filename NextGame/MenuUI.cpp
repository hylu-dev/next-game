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
		stringColor = float3::One;
		App::Print(440, 680, "Dark Star: Showdown", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
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
		App::Print(420, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (isWin) {
		stringColor = { 1, 1, 0 };
		text = winner;
		text += " has won!";
		App::Print(420, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		text = "Press ENTER to restart";
		App::Print(435, 80, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	if (!isStart && !isWin) {
		stringColor = { 1, 1, 0 };
		text = "Press ENTER to end turn";
		App::Print(435, 80, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}


	if (App::IsKeyPressed('H')) {
		stringColor = float3::One;
		text = "Movement";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		text = "Yaw: A/D";
		App::Print(20, 620, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Thrust/Reverse: W/S";
		App::Print(20, 600, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Pitch: Space/Shift";
		App::Print(20, 580, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);

		stringColor = float3::One;
		text = "Upgrade Systems for 100 Scrap";
		App::Print(20, 540, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 1, 0 };
		text = "Upgrade Speed: 1";
		App::Print(20, 520, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Upgrade Speed: 2";
		App::Print(20, 500, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Repair 10 points: 3";
		App::Print(20, 480, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Replenish 10 Fuel: 4";
		App::Print(20, 460, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	else {
		stringColor = { 1, 1, 0 };
		std::string text = "Hold H for controls";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
}

void MenuUI::ClearMenu() {
	isStart = false;
	isWin = false;
	isTurn = false;
}

void MenuUI::StartMenu() {
	isStart = true;
	isWin = false;
	isTurn = false;
}

void MenuUI::WinMenu(std::string name) {
	winner = name;
	isStart = false;
	isWin = true;
	isTurn = false;
}

void MenuUI::TurnMenu(Ship* ship) {
	isStart = false;
	isWin = false;
	isTurn = true;
}


void MenuUI::Restart() {
	isStart = true;
	isWin = false;
}

