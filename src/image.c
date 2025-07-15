/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:05:02 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 13:05:02 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_wall_frames(t_data *data)
{
	char	path[64];
	int		i;

	data->wall.frames = ft_calloc(sizeof(t_image), WALL_FRAMES);
	if (!data->wall.frames)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < WALL_FRAMES)
	{
		build_env_filename(path, "wall", i);
		load_image(data, &data->wall.frames[i], NULL, path);
		i++;
	}
	data->wall.frame_count = WALL_FRAMES;
	data->wall.tick_rate = 100;
}

static void	load_ent_frames(t_data *data, t_ent_anim *ent, char *ent_name,
	int extra_layer)
{
	char	path[64];
	int		dir;
	int		frame;

	dir = 0;
	while (dir < 4)
	{
		frame = 0;
		while (frame < ent->frame_count)
		{
			build_ent_filename(path, ent_name, dir, frame);
			load_image(data, &ent->frames[dir][frame], NULL, path);
			load_image(data, &ent->exit_layer[dir][frame], &data->exit, path);
			if (extra_layer)
				load_image(data, &ent->collect_layer[dir][frame],
					&data->collect, path);
			frame++;
		}
		dir++;
	}
}

static void	allocate_ent_frames(t_data *data, t_ent_anim *ent, int extra_layer)
{
	int		dir;

	ent->frames = ft_calloc(sizeof(t_image *), 4);
	ent->exit_layer = ft_calloc(sizeof(t_image *), 4);
	if (extra_layer)
		ent->collect_layer = ft_calloc(sizeof(t_image *), 4);
	if (!ent->frames || !ent->exit_layer
		|| (extra_layer && !ent->collect_layer))
		error_exit(data, "Error: Memory allocation failed\n");
	dir = 0;
	while (dir < 4)
	{
		ent->frames[dir] = ft_calloc(sizeof(t_image), ent->frame_count);
		ent->exit_layer[dir] = ft_calloc(sizeof(t_image), ent->frame_count);
		if (extra_layer)
			ent->collect_layer[dir]
				= ft_calloc(sizeof(t_image), ent->frame_count);
		if (!ent->frames[dir] || !ent->exit_layer[dir]
			|| (extra_layer && !ent->collect_layer[dir]))
			error_exit(data, "Error: Memory allocation failed\n");
		dir++;
	}
}

void	load_enemy_frames(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->enemy_count)
	{
		data->enemy[i].frame_count = ENEMY_FRAMES;
		data->enemy[i].current_dir = 2;
		data->enemy[i].tick_rate = 100;
		allocate_ent_frames(data, &data->enemy[i], 1);
		load_ent_frames(data, &data->enemy[i], "enemy", 1);
		i++;
	}
}

void	load_player_frames(t_data *data)
{
	data->player.frame_count = PLAYER_FRAMES;
	data->player.current_dir = 1;
	allocate_ent_frames(data, &data->player, 0);
	load_ent_frames(data, &data->player, "player", 0);
}
