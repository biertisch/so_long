/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
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

static void	set_player_pos(char **map, int *row, int *col)
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
				*row = i;
				*col = j;
			}
			j++;
		}
		i++;
	}
}

static void	set_map_size(char **map, int *width, int *height)
{
	int	i;

	i = 0;
	*width = ft_strlen(map[i]);
	*height = 0;
	while (map[i++])
		(*height)++;
}

void	init_map_data(t_data *data)
{
	set_map_size(data->map, &data->map_width, &data->map_height);
	set_player_pos(data->map, &data->player_row, &data->player_col);
	count_collectibles(data->map, &data->collectibles);
}
