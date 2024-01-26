#pragma once

#include <unordered_set>

#include "Enemy.h"

struct EnemyHashFunc {
	size_t operator()(const Enemy& enemy) const {
		return enemy.GetID();
	}
};

class EnemyManager
{
private:
	EnemyManager();
	std::unordered_set<Enemy, EnemyHashFunc> enemies;
public:
	static EnemyManager& instance();
	const std::unordered_set<Enemy, EnemyHashFunc>& GetEnemies() const;
	const void AddEnemy(Enemy enemy);
	const bool RemoveEnemy(Enemy enemy);						// returns true if enemy found and removed, otherwise false
	~EnemyManager();
};