#include "EnemyManager.h"

EnemyManager::EnemyManager() { }

EnemyManager::~EnemyManager() {
	enemies.clear();
}

EnemyManager& EnemyManager::instance() {
	static EnemyManager* instance = new EnemyManager();
	return *instance;
}

const std::unordered_set<Enemy, EnemyHashFunc>& EnemyManager::GetEnemies() const {
	return enemies;
}

const void EnemyManager::AddEnemy(Enemy enemy) {
	enemies.insert(enemy);
}

const bool EnemyManager::RemoveEnemy(Enemy enemy) {
	auto iter = enemies.find(enemy);
	if (iter == enemies.end())
		return false;

	enemies.erase(iter);
	return true;
}