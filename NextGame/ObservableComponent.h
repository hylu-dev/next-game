#pragma once

#include "Component.h"
#include "Observer.h"
#include "Entity.h"
#include <vector>

class ObservableComponent : public Component {
private:
	std::vector<Observer*> observers;

protected:
	void notify(GameEvent event) {
		for (int i = 0; i < observers.size(); i++) {
			observers[i]->onNotify(parentEntity, event);
		}
	}

public:
	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;

	void addObserver(Observer* observer) { observers.push_back(observer); }
};

