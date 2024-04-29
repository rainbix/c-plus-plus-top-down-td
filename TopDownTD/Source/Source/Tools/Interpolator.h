#pragma once

#include "SimpleInterpolator.h"

//Calculates passed time along with retaining from-to interpolatable values
template <class T>
class Interpolator : public SimpleInterpolator
{
public:
	Interpolator(float totalTime, T from, T to);
	
	T From;
	T To;

	T Lerp(T (*lerp_func)(const T& f, const T& t, const float d));
};
