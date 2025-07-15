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

static void	count_elements(t_data *data)
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
			else if (data->map[i][j] == 'M')
				data->enemy_count++;
			j++;
		}
		i++;
	}
}

static void	set_entities_position(t_data *data)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'P')
			{
				data->player.row = i;
				data->player.col = j;
			}
			else if (data->map[i][j] == 'M')
			{
				data->enemy[k].row = i;
				data->enemy[k].col = j;
				k++;
			}
		}
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
	count_elements(data);
	if (data->enemy_count)
	{
		data->enemy = ft_calloc(sizeof(t_ent_anim), data->enemy_count);
		if (!data->enemy)
			error_exit(data, "Error: Memory allocation failed\n");
	}
	set_entities_position(data);
}
