#pragma once

#include "Component.h"

class Renderable : public Component {
public:
	friend class Renderer;

	void Initialize() override;

	void Update() = 0;

	void Destroy() = 0;

	virtual void Render() = 0;
};

