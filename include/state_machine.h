#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>
#include <stdbool.h>

typedef void(*state_func)(void*);
typedef bool(*transition_check_func)(void*);

typedef enum STATE_MACHINE_RESULT
{
	STATE_MACHINE_RESULT_SUCCESS = 0,
	STATE_MACHINE_RESULT_NULL_PTR,
	STATE_MACHINE_RESULT_OUT_OF_BOUNDS,
			
} STATE_MACHINE_RESULT;

typedef struct state_t
{
	struct state_t* next;
	state_func func;
	void* func_args;
	transition_check_func transition_check;
	void* transition_args;
} state_t;

typedef struct state_machine_t
{
	uint16_t initial_state_index;
	uint16_t state_count;
	state_t* states;
	state_t* current_state;
} state_machine_t;

STATE_MACHINE_RESULT StateMachineStart(state_machine_t* sm);
STATE_MACHINE_RESULT Tick(state_machine_t* sm);

#endif
