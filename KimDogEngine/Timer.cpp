#include "stdafx.h"
#include "Timer.h"

Timer::Timer(float _delay, bool _isLoop) :startTime(GetTickCount64() / 1000.0f), elapsedTime(GetTickCount64() / 1000.0f), delay(_delay),
isLoop(_isLoop), isStopped(false), isEnable(false)
{
}

Timer::~Timer()
{
}

float Timer::GetStartTime()
{
	return startTime;
}

void Timer::SetStartTime(float time)
{
	startTime = time;
}

float Timer::GetElapsedTime()
{
	return elapsedTime;
}

void Timer::SetElapsedTime(float time)
{
	elapsedTime = time;
}

float Timer::GetDelay()
{
	return delay;
}

void Timer::SetDelay(float _delay)
{
	delay = _delay;
}

bool Timer::GetLoop()
{
	return isLoop;
}

void Timer::SetLoop(bool loop)
{
	isLoop = loop;
}

bool Timer::GetStopped()
{
	return isStopped;
}

void Timer::SetStopped(bool stopped)
{
	isStopped = stopped;
}

bool Timer::GetEnable()
{
	return isEnable;
}

void Timer::SetEnable(bool enable)
{
	startTime = GetTickCount64() / 1000.0f;
	elapsedTime = GetTickCount64() / 1000.0f;
	isEnable = enable;
}

float Timer::GetNowTime()
{
	if (isStopped)
		startTime = GetTickCount64() / 1000.0f - (elapsedTime - startTime);
	elapsedTime = GetTickCount64() / 1000.0f;
	return elapsedTime - startTime;
}

bool Timer::GetDone()
{
	if (GetNowTime() > delay && isEnable)
	{
		if (isLoop)
			startTime = GetTickCount64() / 1000.0f;
		return true;
	}
	return false;
}