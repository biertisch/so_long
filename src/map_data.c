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

static void	count_collectibles(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->collectibles++;
			j++;
		}
		i++;
	}
}

static void	set_entities_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->player.row = i;
				data->player.col = j;
			}
			else if (data->map[i][j] == 'M')
			{
				data->enemy.row = i;
				data->enemy.col = j;
			}
			j++;
		}
		i++;
	}
}

static void	set_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = ft_strlen(data->map[i]);
	while (data->map[i++])
		data->map_height++;
}

void	init_map_data(t_data *data)
{
	set_map_size(data);
	set_entities_position(data);
	count_collectibles(data);
}
