/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:53:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/12 13:53:21 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	set_enemy_position(char **map, t_ent *enemy, int enemy_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (map[i] && k < enemy_count)
	{
		j = 0;
		while (map[i][j] && k < enemy_count)
		{
			if (map[i][j] == 'M')
			{
				enemy[k].row = i;
				enemy[k].col = j;
				k++;
			}
			j++;
		}
		i++;
	}
}

static void	set_player_position(char **map, t_ent *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				player->row = i;
				player->col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	count_elements(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				data->collectibles++;
			else if (map[i][j] == 'M')
				data->enemy_count++;
			j++;
		}
		i++;
	}
}

static void	set_map_size(t_map *map)
{
	int	i;

	i = 0;
	map->width = ft_strlen(map->map[i]);
	while (map->map[i++])
		map->height++;
}

void	init_map_data(t_data *data)
{
	set_map_size(&data->map);
	count_elements(data, data->map.map);
	if (data->enemy_count)
	{
		data->enemy = ft_calloc(sizeof(t_ent), data->enemy_count);
		if (!data->enemy)
			error_exit(data, "Error: Memory allocation failed\n");
	}
	set_player_position(data->map.map, &data->player);
	set_enemy_position(data->map.map, data->enemy, data->enemy_count);
}
