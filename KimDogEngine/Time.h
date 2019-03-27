#pragma once

class Time
{
public:
	Time();
	~Time();

private:
	static long long startTime, tstartTime, endTime, frequency;

	static double deltaTime;
	static double timeScale;

public:
	static void Init();
	static void FrameStart();
	static void FrameEnd();

	static double GetTime();
	static double GetDeltaTime();

	static double GetTimeScale();
	static void SetTimeScale(double ts);
};
