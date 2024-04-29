#include "Interpolator.h"

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
