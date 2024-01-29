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
	std::unordered_map<int, Enemy> enemies;
	std::thread updateThread;
	bool shouldUpdate;

public:
	static EnemyManager& instance();
	const std::unordered_map<int, Enemy>& GetEnemies() const;
	const bool AddEnemy(Enemy enemy);							// returns true and inserts if key not found, otherwise returns false
	const bool RemoveEnemy(Enemy enemy);						// returns true if enemy found and removed, otherwise false
	void Start();
	void Stop();
	void UpdateEnemies();
	~EnemyManager();
};