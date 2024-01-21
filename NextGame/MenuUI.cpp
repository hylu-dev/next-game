#include "stdafx.h"
#include "MenuUI.h"

void MenuUI::Initialize() {
	Renderable::Initialize();
}

void MenuUI::Update() {

}

void MenuUI::Destroy() {
	Renderable::Destroy();
}

void MenuUI::Render() {
	if (isStart) {
		stringColor = float3::One;
		App::Print(440, 680, "Dark Star: Showdown", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		App::Print(435, 80, "Press ENTER to start", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);

		std::string text = "Separated by a dying star.";
		App::Print(20, 740, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Two pilots from opposing nations have";
		App::Print(20, 720, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "their last chance to prove themselves.";
		App::Print(20, 700, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		stringColor = { 1, 0, 1 };
		text = "This game requires 2 players.";
		App::Print(20, 680, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	else if (isTurn) {
		stringColor = float3::One;
		App::Print(440, 680, "0 turns until next pulse", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		App::Print(435, 80, "Press ENTER to continue", stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}


	if (App::IsKeyPressed('H')) {
		stringColor = { 1, 1, 0 };
		std::string text = "Yaw: A/D";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Thrust/Reverse: W/S";
		App::Print(20, 620, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
		text = "Pitch: Space/Shift";
		App::Print(20, 600, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
	else {
		stringColor = { 0.7, 0.7, 0 };
		std::string text = "Hold H for controls";
		App::Print(20, 640, text.c_str(), stringColor.x, stringColor.y, stringColor.z, GLUT_BITMAP_8_BY_13);
	}
}

void MenuUI::StartMenu() {
	isStart = true;
	isWin = false;
	isTurn = false;
}

void MenuUI::WinMenu() {
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

