#include "EnemyState.h"

EnemyState::EnemyState(Enemy* me, std::vector<EnemyStateCondition*> conditions) : conditions(conditions), me(me) { }

void EnemyState::CheckConditions() {
	for (const EnemyStateCondition* condition : conditions) {
		if (condition->Check()) {
			me->SetState(condition->GetNewState());
		}
	}
}