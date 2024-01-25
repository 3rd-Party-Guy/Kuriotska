#pragma once

template<class T>
class Vector2
{
private:
	T x, y;
public:
	T GetX() const;
	T GetY() const;
	void SetX(T newX);
	void SetY(T newY);
	void Set(T newX, T newY);
	void Set(Vector2<T> newVec);
	Vector2();
	Vector2(T x, T y);

	inline void operator=(const Vector2<T>& other);
	inline bool operator==(const Vector2<T>& other) const;
	inline Vector2<T> operator+(const Vector2<T>& other) const;
	inline Vector2<T> operator-(const Vector2<T>& other) const;
};