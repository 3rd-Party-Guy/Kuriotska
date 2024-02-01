#pragma once

#include <unordered_map>
#include <thread>

#include "Enemy.h"

//struct EnemyHashFunc {
//	size_t operator()(const Enemy& enemy) const {
//		return enemy.GetID();
//	}
//};

class EnemyManager
{
private:
	EnemyManager();
	std::unordered_map<int, Enemy*> enemies;
	std::thread updateThread;
	bool shouldUpdate;

public:
	static EnemyManager& instance();
	const std::unordered_map<int, Enemy*>& GetEnemies() const;
	const void DamageEnemyAtPos(Vector2<int> pos, int amount);
	const bool AddEnemy(Vector2<int> position, int chaseDistance, Player* player, Map* map);							// returns true and inserts if key not found, otherwise returns false
	const bool RemoveEnemy(Enemy* enemy);																				// returns true if enemy found and removed, otherwise false
	void StartUpdate();
	void StopUpdate();
	void UpdateEnemies();
	~EnemyManager();
};