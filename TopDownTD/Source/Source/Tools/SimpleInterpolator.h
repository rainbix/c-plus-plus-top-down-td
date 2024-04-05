#pragma once

//Just calculates passed time
class SimpleInterpolator
{
public:

	SimpleInterpolator(float totalTime);
	
	bool IsActive() const;
	bool IsElapsed() const;

	void ProcessTick(float deltaTime);
	void Stop();
	void Start();
	void Reset();
	void ResetWithNewTime(float newTotalTime);

	float Progress() const;

private:
	bool isActive = false;
	float curTime;
	float totalTime = 0.2f;
};
