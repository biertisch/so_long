/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:09:38 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/15 22:40:53 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	build_ent_filename(char *dest, const char *base, int dir, int frame)
{
	char	*prefix;
	char	*extension;
	int		i;
	int		j;

	prefix = "textures/ent/";
	extension = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	while (*base)
		dest[i++] = *base++;
	dest[i++] = '_';
	dest[i++] = '0' + dir;
	dest[i++] = '_';
	dest[i++] = '0' + frame;
	j = 0;
	while (extension[j])
		dest[i++] = extension[j++];
	dest[i] = '\0';
}

static void	load_ent_frames(t_data *data, t_ent *ent, const char *ent_name,
	int extra_layer)
{
	char	path[64];
	int		dir;
	int		frame;

	dir = 0;
	while (dir < DIRECTIONS)
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

static void	allocate_ent_frames(t_data *data, t_ent *ent, int extra_layer)
{
	int		dir;

	ent->frames = ft_calloc(sizeof(t_image *), DIRECTIONS);
	ent->exit_layer = ft_calloc(sizeof(t_image *), DIRECTIONS);
	if (extra_layer)
		ent->collect_layer = ft_calloc(sizeof(t_image *), DIRECTIONS);
	if (!ent->frames || !ent->exit_layer
		|| (extra_layer && !ent->collect_layer))
		error_exit(data, "Error: Memory allocation failed\n");
	dir = 0;
	while (dir < DIRECTIONS)
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

void	init_ent(t_data *data)
{
	int	i;

	data->player.frame_count = PLAYER_FRAMES;
	data->player.current_dir = DIR_DOWN;
	allocate_ent_frames(data, &data->player, 0);
	load_ent_frames(data, &data->player, "player", 0);
	i = 0;
	while (i < data->enemy_count)
	{
		data->enemy[i].frame_count = ENEMY_FRAMES;
		data->enemy[i].current_dir = DIR_LEFT;
		data->enemy[i].last_move = get_time_ms();
		data->enemy[i].move_interval_ms = 250;
		allocate_ent_frames(data, &data->enemy[i], 1);
		load_ent_frames(data, &data->enemy[i], "enemy", 1);
		i++;
	}
}
