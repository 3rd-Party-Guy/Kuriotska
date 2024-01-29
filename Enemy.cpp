#include "Enemy.h"
#include "Misc.h"

size_t Enemy::nextID = 1;

Enemy::Enemy(Vector2<int> position, int chaseDistance, Player* player) : Entity(position), chaseDistance(chaseDistance),
	player(player), curState(EnemyState::IDLE),
	health(10, 0, 10, this, Event::HEALTH_EMPTY, Event::HEALTH_FULL) {
	ID = nextID++;
}

const size_t Enemy::GetID() const {
	return ID;
}

const bool Enemy::operator==(const Enemy& other) const {
	return (ID == other.GetID());
}

void Enemy::Update() {
	CheckState();
	Act();
}

void Enemy::CheckState() {
	int distance = Misc::CalculateDistanceEuclidean(player->GetPosition(), GetPosition());
	switch (curState) {
	case EnemyState::IDLE:
		if (distance <= chaseDistance)
			curState = EnemyState::CHASE;
		break;
	case EnemyState::CHASE:
		if (distance <= 1)
			curState = EnemyState::ATTACK;
		else if (distance > chaseDistance)
			curState = EnemyState::IDLE;
		break;
	case EnemyState::ATTACK:
		if (distance > 1)
			curState = EnemyState::CHASE;
		break;
	case EnemyState::FLEE:
		if (distance > chaseDistance)
			curState = EnemyState::IDLE;
		break;
	default:
		break;
	}
}

void Enemy::Act() {
	switch (curState) {
	case EnemyState::IDLE:
		break;
	case EnemyState::CHASE:
		SetPositionRel(Misc::GetUnitVecTowardsTarget(GetPosition(), player->GetPosition()));
		break;
	case EnemyState::ATTACK:
		player->Damage(1);
		break;
	case EnemyState::FLEE:
		SetPositionRel(Misc::GetUnitVecTowardsTarget(player->GetPosition(), GetPosition()));
		break;
	default:
		break;
	}
}