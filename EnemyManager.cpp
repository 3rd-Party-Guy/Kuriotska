#include <chrono>

#include "EnemyManager.h"
#include "Debugger.h"

EnemyManager::EnemyManager() : shouldUpdate(true) { }

EnemyManager::~EnemyManager() {
	enemies.clear();
}

EnemyManager& EnemyManager::instance() {
	static EnemyManager* instance = new EnemyManager();
	return *instance;
}

const std::unordered_map<int, Enemy>& EnemyManager::GetEnemies() const {
	return enemies;
}

const void EnemyManager::InsertEnemy(Enemy enemy) {
	enemies[enemy.GetID()] = enemy;
}

const bool EnemyManager::RemoveEnemy(Enemy enemy) {
	auto iter = enemies.find(enemy.GetID());
	if (iter == enemies.end())
		return false;

	enemies.erase(iter);
	return true;
}

void EnemyManager::Start() {
	shouldUpdate = true;
	updateThread = std::thread(&EnemyManager::UpdateEnemies, this);
}

void EnemyManager::Stop() {
	shouldUpdate = false;
}

void EnemyManager::UpdateEnemies() {
	while (shouldUpdate) {
		for (std::pair<const int, Enemy>& e : enemies)
			e.second.Update();

		std::chrono::milliseconds sleepDuration(500);
		std::this_thread::sleep_for(sleepDuration);
	}
}