#include <faudef.h>

int 
timer_init(timer* tim)
{
	tim->initial_tick = 0;
	tim->paused_tick = 0;
	tim->paused = false;
	tim->was_started = false;
	return 0;
}

int
timer_start(timer* tim)
{
	tim->was_started = true;
	tim->paused = false;
	tim->initial_tick = SDL_GetTicks();
	tim->paused_tick = 0;
	return 0;
}

int
timer_stop(timer* tim)
{
	tim->was_started = false;
	tim->paused = false;
	tim->initial_tick = 0;
	tim->paused_tick = 0;
	return 0;
}

int 
timer_pause(timer* tim)
{
	if ( tim->was_started && !tim->paused)
	{
		tim->paused = true;
		tim->paused_tick = SDL_GetTicks() - tim->initial_tick;
		tim->initial_tick = 0;
	}
	return 0;
}

int 
timer_unpause(timer* tim)
{
	if (tim->was_started && tim->paused)
	{
		tim->paused = false;
		tim->initial_tick = SDL_GetTicks() - tim->paused_tick;
		tim->paused_tick = 0;
	}
	return 0;
}

int	
timer_get_ticks(timer* tim)
{
	Uint32 time = 0;
	
	if ( tim->was_started )
	{
		if ( tim->paused )
		{
			time = tim->paused_tick;
		}
		else
		{
			time = SDL_GetTicks() - tim->initial_tick;
		}
	}
	return time;
}

bool
timer_is_paused(timer* tim)
{
	return tim->paused && tim->was_started;
}
