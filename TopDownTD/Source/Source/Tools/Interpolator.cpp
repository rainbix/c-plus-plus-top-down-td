// Fill out your copyright notice in the Description page of Project Settings.


#include "Interpolator.h"

Interpolator::Interpolator(float totalTime)
{
	Reset();
	this->totalTime = totalTime;
}

bool Interpolator::IsActive()
{
	return isActive;
}

bool Interpolator::IsElapsed() const
{
	return curTime > totalTime;
}

void Interpolator::ProcessTick(float deltaTime)
{
	if (!isActive)
		return;

	curTime += deltaTime;
}

void Interpolator::ResetWithNewTime(float newTotalTime)
{
	this->totalTime = newTotalTime;
	Reset();
}

float Interpolator::Progress() const
{
	return curTime / totalTime;
}

void Interpolator::Stop()
{
	isActive = false;
}

void Interpolator::Start()
{
	Reset();
	
	isActive = true;
}

void Interpolator::Reset()
{
	curTime = 0;
}
