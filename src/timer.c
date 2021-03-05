# include "cub3d.h"

# define MILLIS_PER_TICK 50

void			set_current_timer(t_timer *timer)
{
	struct timespec	current_time;

	clock_gettime(CLOCK_REALTIME, &current_time);
	timer->last_update = current_time.tv_sec * INT64_C(1000) + current_time.tv_nsec / 1000000;
}

void			update_timer(t_timer *timer)
{
	struct timespec	current_time;
	int64_t			current_millis;

	clock_gettime(CLOCK_REALTIME, &current_time);
	current_millis = current_time.tv_sec * INT64_C(1000) + current_time.tv_nsec / 1000000;
	timer->elapsed_ticks = (current_millis - timer->last_update) / MILLIS_PER_TICK;
}