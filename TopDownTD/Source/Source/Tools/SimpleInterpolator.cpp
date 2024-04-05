#include "SimpleInterpolator.h"

SimpleInterpolator::SimpleInterpolator(float totalTime)
{
	Reset();
	this->totalTime = totalTime;
}

bool SimpleInterpolator::IsActive() const
{
	return isActive;
}

bool SimpleInterpolator::IsElapsed() const
{
	return curTime > totalTime;
}

void SimpleInterpolator::ProcessTick(float deltaTime)
{
	if (!isActive)
		return;

	curTime += deltaTime;
}

void SimpleInterpolator::ResetWithNewTime(float newTotalTime)
{
	this->totalTime = newTotalTime;
	Reset();
}

float SimpleInterpolator::Progress() const
{
	return curTime / totalTime;
}

void SimpleInterpolator::Stop()
{
	isActive = false;
}

void SimpleInterpolator::Start()
{
	Reset();
	
	isActive = true;
}

void SimpleInterpolator::Reset()
{
	curTime = 0;
}