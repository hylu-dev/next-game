#pragma once
class Renderable
{
public:
	friend class Renderer;

	virtual void Initialize();

	virtual void Render() = 0;
};

