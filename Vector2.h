#pragma once
template<class T>
class Vector2
{
private:
	T x, y;
public:
	T GetX() const;
	T GetY() const;
	Vector2(T x, T y);
};