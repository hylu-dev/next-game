#pragma once

class Time {
private:
	float deltaTime;
	float elapsedSeconds;

public:
	static Time& Get() {
		static Time instance;
		return instance;
	}

	float DeltaTime() { return deltaTime; };
	float Elapsed() { return elapsedSeconds; };

	void Initialize();

	void Update(float frameTime);

	void Destroy();

private:
	Time() = default;
	~Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};

