//
// Created by Roberto Boldini on 11/04/21.
//

/*
**	Norminette V3 Status: OK!
*/

#ifndef BATTLE_H
# define BATTLE_H

# include "cub3d.h"

int		ft_init_battle(t_game *game);
int		ft_if_catching(t_game *game);
int		ft_run_render_battle(t_game *game);
void	ft_render_ownhp(t_game *game);
void	ft_render_enemyhp(t_game *game);
int		attack_player(t_game *game);
int		ft_attack_opponent(t_game *game);

#endif
