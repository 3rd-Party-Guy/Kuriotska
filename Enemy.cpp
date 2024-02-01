#include "Enemy.h"
#include "EnemyManager.h"
#include "Misc.h"

int Enemy::nextID = 1;

int Enemy::GetNextID() {
	return nextID;
}

Enemy::Enemy(Vector2<int> position, int chaseDistance, Player* player, Map* map) : Actor(position, 5, false, map),
	chaseDistance(chaseDistance), curState(EnemyState::IDLE), player(player) {
	ID = nextID++;
}

const int Enemy::GetID() const {
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
			curState = (GetHealth() < 1) ? EnemyState::FLEE : 
						EnemyState::CHASE;
		break;
	case EnemyState::CHASE:
		if (distance <= 1)
			curState = EnemyState::ATTACK;
		else if (distance > chaseDistance)
			curState = EnemyState::IDLE;

		if (GetHealth() < 2)
			curState = EnemyState::FLEE;
		break;
	case EnemyState::ATTACK:
		if (distance > 1)
			curState = EnemyState::CHASE;
		if (GetHealth() < 2)
			curState = EnemyState::FLEE;
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
		TryChasePlayer();
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

void Enemy::TryChasePlayer() {
	Vector2<int> toPlayerUnit(Misc::GetUnitVecTowardsTarget(GetPosition(), player->GetPosition()));
	const MapNode* nextMapNode = map->GetNode(GetPosition() + toPlayerUnit);

	if (nextMapNode->GetType() == MapNodeType::Water) return;
	if (!nextMapNode->isFree) return;

	SetPositionRel(toPlayerUnit);
}

void Enemy::OnDeath() {
	Actor::OnDeath();
	player->GetKill();
	EnemyManager::instance().RemoveEnemy(this);
}