#pragma once

// I chose a simple enum state instead of an FSM because of the simplicity of the NPC AI.
// Trying to keep things simple and readable has often resulted in better performance in
// my experience

enum class EnemyState {
	IDLE,
	CHASE,
	ATTACK,
	FLEE
};