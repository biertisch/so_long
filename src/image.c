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

	data->wall.frames = malloc(sizeof(t_image) * WALL_FRAMES);
	if (!data->wall.frames)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < WALL_FRAMES)
	{
		build_env_filename(path, "wall", i);
		load_image(data, &data->wall.frames[i], 1, path);
		i++;
	}
	data->wall.frame_count = WALL_FRAMES;
	data->wall.tick_rate = 100;
}

void	load_exit_frames(t_data *data)
{
	char	path[64];
	int		i;

	data->exit.frames = malloc(sizeof(t_image) * EXIT_FRAMES);
	if (!data->exit.frames)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < EXIT_FRAMES)
	{
		build_env_filename(path, "exit", i);
		load_image(data, &data->exit.frames[i], 1, path);
		i++;
	}
	data->exit.frame_count = EXIT_FRAMES;
	data->exit.tick_rate = 50;
}

void	load_player_frames(t_data *data)
{
	char	path[64];
	int		dir;
	int		frame;

	data->player.frames = malloc(sizeof(t_image *) * 4);
	if (!data->player.frames)
		error_exit(data, "Error: Memory allocation failed\n");
	dir = 0;
	while (dir < 4)
	{
		data->player.frames[dir] = malloc(sizeof(t_image) * PLAYER_FRAMES);
		if (!data->player.frames[dir])
			error_exit(data, "Error: Memory allocation failed\n");
		frame = 0;
		while (frame < PLAYER_FRAMES)
		{
			build_ent_filename(path, "player", dir, frame);
			load_image(data, &data->player.frames[dir][frame], 1, path);
			frame++;
		}
		dir++;
	}
	data->player.frame_count = PLAYER_FRAMES;
	data->player.current_dir = 1;
}

void	load_image(t_data *data, t_image *dest, int layers, char *filename)
{
	t_image	src;

	src = process_raw_image(data, filename);
	create_image_buffer(data, dest);
	if (layers >= 1)
		draw_with_transparency(dest, &data->floor);
	if (layers == 2)
		draw_with_transparency(dest,
			&data->exit.frames[data->exit.current_frame]);
	draw_with_transparency(dest, &src);
	mlx_destroy_image(data->mlx, src.img);
}
