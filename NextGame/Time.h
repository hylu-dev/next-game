#pragma once

#include <chrono>

class Time {
private:
	std::chrono::duration<float> deltaTime = std::chrono::duration<float>(0.0f);
	std::chrono::duration<float> elapsedSeconds = std::chrono::duration<float>(0.0f);
	std::chrono::time_point<std::chrono::system_clock> beginTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;

public:
	static Time& Get() {
		static Time instance;
		return instance;
	}

	float DeltaTime() { return deltaTime.count(); };
	float Elapsed() { return elapsedSeconds.count(); };

	void Initialize();

	void Update();

	void Destroy();

private:
	Time() = default;
	~Time() = default;
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};

