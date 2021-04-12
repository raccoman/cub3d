# include "../headers/cub3d.h"

# define MILLIS_PER_TICK 50

int64_t		current_milliseconds()
{
	struct timespec	current_time;

	clock_gettime(CLOCK_REALTIME, &current_time);
	return (current_time.tv_sec * INT64_C(1000) + current_time.tv_nsec / 1000000);
}

void			update_timer(t_timer *timer)
{
	int64_t			current_millis;

	current_millis = current_milliseconds();
	timer->elapsed_ticks = MIN(10, (current_millis - timer->last_update) / MILLIS_PER_TICK);
	if (timer->elapsed_ticks != 0) timer->last_update = current_millis;
}