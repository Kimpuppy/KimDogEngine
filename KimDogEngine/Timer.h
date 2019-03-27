#pragma once

class Timer
{
public:
	Timer(float _delay, bool _isLoop);
	~Timer();

private:
	float startTime;
	float elapsedTime;
	float delay;

	bool isLoop;
	bool isStopped;
	bool isEnable;

public:
	float GetStartTime();
	void SetStartTime(float time);

	float GetElapsedTime();
	void SetElapsedTime(float time);

	float GetDelay();
	void SetDelay(float _delay);

	bool GetLoop();
	void SetLoop(bool loop);

	bool GetStopped();
	void SetStopped(bool stopped);

	bool GetEnable();
	void SetEnable(bool enable);

	float GetNowTime();

	bool GetDone();
};
