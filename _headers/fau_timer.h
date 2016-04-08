#ifndef FAU_TIMER_H
#define FAU_TIMER_H

	#include <fau_common.h>
	
	typedef struct
	{
		Uint32 	ticks;
		bool 		was_started;
		bool 		is_paused;
		Uint32 	initial_tick;
		Uint32 	paused_tick;
		bool		paused;
	} timer;
	
	int timer_init(timer* tim);
	int timer_start(timer* tim);
	int timer_stop(timer* tim);
	int timer_pause(timer* tim);
	int timer_unpause(timer* tim);
	int	timer_get_ticks(timer* tim);
	bool timer_is_paused(timer* tim);
#endif
