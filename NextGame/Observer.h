#pragma once

#include "Entity.h"

enum GameEvent {
	PLAYERA_WIN,
	PLAYERB_WIN,
	STAR_PULSE,
};

class Observer {
public:
	virtual void onNotify(const Entity* entity, GameEvent event) = 0;
};