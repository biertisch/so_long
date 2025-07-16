/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:55:47 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/16 09:55:47 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	build_env_filename(char *dest, const char *base, int frame)
{
	const char	*prefix;
	const char	*suffix;
	int			i;

	prefix = "textures/env/";
	suffix = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	while (*base)
		dest[i++] = *base++;
	dest[i++] = '_';
	if (frame >= 10)
		dest[i++] = '0' + (frame / 10);
	dest[i++] = '0' + (frame % 10);
	while (*suffix)
		dest[i++] = *suffix++;
	dest[i] = '\0';
}

static void	load_wall_frames(t_data *data, t_env_anim *wall)
{
	char	path[64];
	int		i;

	wall->frames = ft_calloc(sizeof(t_image), WALL_FRAMES);
	if (!wall->frames)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < WALL_FRAMES)
	{
		build_env_filename(path, "wall", i);
		load_image(data, &wall->frames[i], NULL, path);
		i++;
	}
	wall->frame_count = WALL_FRAMES;
	wall->tick_rate = 100;
}

void	init_env(t_data *data)
{
	load_image(data, &data->floor, NULL, "textures/env/floor.xpm");
	load_image(data, &data->collect, NULL, "textures/env/collectible.xpm");
	load_image(data, &data->exit, NULL, "textures/env/exit.xpm");
	load_wall_frames(data, &data->wall);
}
