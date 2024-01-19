#include "Vector2.h"

template <class T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) { }
template <class T>
T Vector2<T>::GetX() const { return x; }
template <class T>
T Vector2<T>::GetY() const { return y; }

template class Vector2<float>;
template class Vector2<int>;
template class Vector2<double>;