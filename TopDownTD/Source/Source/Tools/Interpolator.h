// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class Interpolator
{
public:

	Interpolator(float totalTime);

	bool IsActive();
	bool IsElapsed() const;
	void ProcessTick(float deltaTime);
	void Stop();
	void Start();
	void Reset();

private:
	bool isActive = false;
	float curTime;
	float totalTime = 0.2f;
};
