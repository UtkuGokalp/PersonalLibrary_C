#include "state_machine.h"
#include <stddef.h>

STATE_MACHINE_RESULT StateMachineStart(state_machine_t* sm)
{
	if (sm == NULL || sm->states == NULL)
	{
		return STATE_MACHINE_RESULT_NULL_PTR;
	}
	if (sm->initial_state_index >= sm->state_count)
	{
		return STATE_MACHINE_RESULT_OUT_OF_BOUNDS;
	}
	sm->current_state = &(sm->states[sm->initial_state_index]);
	return STATE_MACHINE_RESULT_SUCCESS;
}

STATE_MACHINE_RESULT Tick(state_machine_t* sm)
{
	if (sm == NULL)
	{
		return STATE_MACHINE_RESULT_NULL_PTR;
	}

	state_t* curr = sm->current_state;
	if (
	curr == NULL ||
	curr->func == NULL ||
	curr->transition_check == NULL
	)
	{
		return STATE_MACHINE_RESULT_NULL_PTR;
	}

	curr->func(curr->func_args);
	if (curr->transition_check(curr->transition_args))
	{
		sm->current_state = curr->next;
	}
	return STATE_MACHINE_RESULT_SUCCESS;
}
