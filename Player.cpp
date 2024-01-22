#include "Player.h"

void Player::MoveAbs(int x, int y) {
	SetPositionAbs(x, y);
}

void Player::MoveRel(int xVel, int yVel) {
	SetPositionRel(xVel, yVel);
}

Player::Player() {
	hp = startHP;
	SetPositionAbs(10, 10);
}