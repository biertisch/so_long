/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:05:02 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 13:05:02 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	count_collectibles(char **map, int *collectibles)
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
				(*collectibles)++;
			j++;
		}
		i++;
	}
}

static void	set_player_pos(char **map, t_point *position)
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
				position->row = i;
				position->column = j;
			}
			j++;
		}
		i++;
	}
}

static void	set_map_size(char **map, t_point *map_size)
{
	int	i;

	i = 0;
	map_size->column = ft_strlen(map[i]);
	map_size->row = 0;
	while (map[i++])
		map_size->row++;
}

void	init_map_data(t_data *data)
{
	set_map_size(data->map, &data->map_size);
	set_player_pos(data->map, &data->player_pos);
	count_collectibles(data->map, &data->collectibles);
}
