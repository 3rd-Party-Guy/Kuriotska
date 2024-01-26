#include "Enemy.h"
#include "Misc.h"

size_t Enemy::nextID = 1;

Enemy::Enemy(Vector2<int> position, int attackDistance, Entity* player) : Entity(position), attackDistance(attackDistance), player(player) {
	isChasing = false;
	ID = nextID++;
}

bool Enemy::IsPlayerWithinDistance() const {
	return (Misc::CalculateDistanceEuclidean(GetPosition(), player->GetPosition()) <= attackDistance);
}

const size_t Enemy::GetID() const {
	return ID;
}

const bool Enemy::operator==(const Enemy& other) const {
	return (ID == other.GetID());
}