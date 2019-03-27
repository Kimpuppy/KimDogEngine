#include "stdafx.h"
#include "Time.h"

long long Time::startTime, Time::tstartTime, Time::endTime, Time::frequency;

double Time::deltaTime;
double Time::timeScale;

Time::Time()
{
}

Time::~Time()
{
}

void Time::Init()
{
	timeScale = 1.0f;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	QueryPerformanceCounter((LARGE_INTEGER *)&tstartTime);
}

void Time::FrameStart()
{
	QueryPerformanceCounter((LARGE_INTEGER *)&startTime);
}

void Time::FrameEnd()
{
	QueryPerformanceCounter((LARGE_INTEGER *)&endTime);
	deltaTime = (double)(endTime - startTime) / (double)frequency * timeScale;
}

double Time::GetTime()
{
	return (double)(endTime - tstartTime) / (double)frequency * timeScale;
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::GetTimeScale()
{
	return timeScale;
}

void Time::SetTimeScale(double ts)
{
	timeScale = ts;
}