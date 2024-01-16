#pragma once

class Time {
private:
	float deltaTime = 0.0f;
	float elapsedSeconds = 0.0f;
	float timeScale = 1.0f;

public:
	static Time& Get() {
		static Time instance;
		return instance;
	}
	
	float& TimeScale() { return timeScale; }
	float DeltaTime() { return deltaTime; }
	float Elapsed() { return elapsedSeconds; }

	void Initialize();

	void Update(float frameTime);

	void Destroy();

private:
	Time() = default;
	~Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};

