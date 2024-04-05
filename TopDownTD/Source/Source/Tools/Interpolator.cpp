#include "Interpolator.h"

template <class T>
Interpolator<T>::Interpolator(float totalTime, T from, T to): SimpleInterpolator(totalTime)
{
	From = from;
	To = to;
}