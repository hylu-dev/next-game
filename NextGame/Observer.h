#pragma once

#include "Entity.h"

enum GameEvent {
	PLAYERA_WIN,
	PLAYERB_WIN,
	STAR_PULSE,
	SUPERNOVA
};

class Observer {
public:
	virtual void OnNotify(const Entity* entity, GameEvent event) = 0;
};