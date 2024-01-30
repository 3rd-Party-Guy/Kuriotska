#include <chrono>

#include "EnemyManager.h"

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

const void EnemyManager::DamageEnemyAtPos(Vector2<int> pos, int amount) {
	for (std::pair<const int, Enemy>& e : enemies) {
		if (e.second.GetPosition() != pos) continue;
		e.second.Damage(amount);
	}
}

const bool EnemyManager::AddEnemy(Enemy enemy) {
	return enemies.try_emplace(enemy.GetID(), enemy).second;
}

const bool EnemyManager::RemoveEnemy(Enemy* enemy) {
	auto iter = enemies.find(enemy->GetID());
	if (iter == enemies.end())
		return false;

	enemies.erase(iter);
	return true;
}

void EnemyManager::StartUpdate() {
	shouldUpdate = true;
	updateThread = std::thread(&EnemyManager::UpdateEnemies, this);
}

void EnemyManager::StopUpdate() {
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