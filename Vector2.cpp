#include "Vector2.h"

template <class T> Vector2<T>::Vector2(T x, T y) : x(x), y(y) { }
template <class T> Vector2<T>::Vector2() : x(), y() { }

template <class T> void Vector2<T>::SetX(T newX) { x = newX; }
template <class T> void Vector2<T>::SetY(T newY) { y = newY; }
template <class T> void Vector2<T>::Set(T newX, T newY) { x = newX;  y = newY; }
template <class T> void Vector2<T>::Set(Vector2<T> newVec) { x = newVec.GetX(); y = newVec.GetY(); }

template <class T> T Vector2<T>::GetX() const { return x; }
template <class T> T Vector2<T>::GetY() const { return y; }

template <class T>
inline void Vector2<T>::operator=(const Vector2<T>& other) {
	this->x = other.GetX();
	this->y = other.GetY();
}

template <class T>
inline bool Vector2<T>::operator==(const Vector2<T>& other) const {
	return (this->GetX() == other.GetX() && this->GetY() == other.GetY());
}

template <class T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
	return Vector2<T>(this->GetX() + other.GetX(), this->GetY() + other.GetY());
}

template <class T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
	return Vector2<T>(this->GetX() - other.GetX(), this->GetY() - other.GetY());
}

template class Vector2<int>;
template class Vector2<float>;
template class Vector2<double>;
template class Vector2<unsigned short>;