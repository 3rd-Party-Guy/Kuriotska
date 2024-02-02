#include <chrono>

#include "EnemyManager.h"
#include "Misc.h"

Player* EnemyManager::player = nullptr;
Map* EnemyManager::map = nullptr;

EnemyManager::EnemyManager() : shouldUpdate(true) {
	spawnAmount = 25;
	timeUntilNextSpawn = 0.0;
}

EnemyManager::~EnemyManager() {
	enemies.clear();
}

EnemyManager& EnemyManager::instance() {
	static EnemyManager* instance = new EnemyManager();
	return *instance;
}

void EnemyManager::GivePlayer(Player* playerPtr) {
	player = playerPtr;
}

void EnemyManager::GiveMap(Map* mapPtr) {
	map = mapPtr;
}

const std::unordered_map<int, Enemy*>& EnemyManager::GetEnemies() const {
	return enemies;
}

const void EnemyManager::DamageEnemyAtPos(Vector2<int> pos, int amount) {
	for (std::pair<const int, Enemy*>& e : enemies) {
		if (e.second->GetPosition() != pos) continue;
		e.second->Damage(amount);
		break;
	}
}

const bool EnemyManager::AddEnemy(Vector2<int> position, int chaseDistance, Player* player, Map* map) {

	return enemies.try_emplace(Enemy::GetNextID() - 1,
			new Enemy(position, chaseDistance, player, map)).second;
}

const bool EnemyManager::RemoveEnemy(Enemy* enemy) {
	auto iter = enemies.find(enemy->GetID());
	if (iter == enemies.end())
		return false;

	enemies.erase(iter);
	return true;
}

void EnemyManager::SpawnEnemy() {
	Vector2<int> randPos(Misc::RandomInRange(0, map->sizeX - 1), Misc::RandomInRange(0, map->sizeY - 1));
	const MapNode* randNode = map->GetNode(randPos);
	if (randNode->GetType() != MapNodeType::Water)
		AddEnemy(randPos, 10, player, map);
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
		int playerLevel = player->GetLevel();
		timeUntilNextSpawn -= 0.5;

		if (timeUntilNextSpawn <= 0.01) {
			for (int i = 0; i < spawnAmount; ++i) {
				SpawnEnemy();
			}

			spawnAmount = static_cast<int>(std::ceil(pow(playerLevel, 2) / 0.25));
			timeUntilNextSpawn = pow(playerLevel, 2) / pow(playerLevel, 3) + 0.125;
		}
		
		for (std::pair<const int, Enemy*>& e : enemies)
			e.second->Update();

		std::chrono::milliseconds sleepDuration(500);
		std::this_thread::sleep_for(sleepDuration);
	}
}