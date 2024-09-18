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
	void SetFromTo(const T& newFrom, const T& newTo);
	
};

// The separation of the template class definition and its member function implementations into different files
// resulted in files not being compiled now and then.
// In C++, template definitions and their implementations must be in the same file.
// This is because the compiler needs to see the full definition of the template in order to generate code for each instantiation of the template.

template <class T>
Interpolator<T>::Interpolator(float totalTime, T from, T to): SimpleInterpolator(totalTime)
{
	From = from;
	To = to;
}

template <class T>
T Interpolator<T>::Lerp(T(* lerp_func)(const T& f, const T& t, const float d))
{
	return lerp_func(From, To, Progress());
}

template <class T>
void Interpolator<T>::SetFromTo(const T& newFrom, const T& newTo)
{
	From = newFrom;
	To = newTo;
}



