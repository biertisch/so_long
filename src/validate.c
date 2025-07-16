/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:09:19 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 11:09:19 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	is_reachable(t_data *data)
{
	char	**tmp;

	tmp = duplicate_map(data->map.map, data->map.height);
	if (!tmp)
		error_exit(data, "Error: Memory allocation failed\n");
	flood_fill(data, tmp, data->player.row, data->player.col);
	free_arr(tmp);
	if (data->unlock_exit != 1 || data->collected != data->collectibles)
		return (0);
	data->unlock_exit = 0;
	data->collected = 0;
	return (1);
}

static int	has_valid_elements(char **map)
{
	int		elements[3];
	char	*row;

	ft_bzero(elements, sizeof(elements));
	while (*map)
	{
		row = *map;
		while (*row)
		{
			if (!ft_strchr("01PECM", *row))
				return (0);
			if (*row == 'P')
				elements[0]++;
			if (*row == 'E')
				elements[1]++;
			if (*row == 'C')
				elements[2]++;
			row++;
		}
		map++;
	}
	if (elements[0] != 1 || elements[1] != 1 || elements[2] < 1)
		return (0);
	return (1);
}

static int	is_enclosed(char **map)
{
	int	i;
	int	j;
	int	last_col;
	int	last_row;

	last_col = ft_strlen(map[0]) - 1;
	last_row = 0;
	while (map[last_row])
		last_row++;
	last_row--;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || j == 0 || i == last_row || j == last_col)
				&& map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_rectangular(char **map)
{
	size_t	len;

	len = ft_strlen(*map);
	while (*map)
	{
		if (ft_strlen(*map) != len)
			return (0);
		map++;
	}
	return (1);
}

void	validate_map(t_data *data)
{
	if (!data->map.map || !*data->map.map)
		error_exit(data, "Error: Invalid map (empty)\n");
	if (!is_rectangular(data->map.map))
		error_exit(data, "Error: Invalid map (not rectangular)\n");
	if (!is_enclosed(data->map.map))
		error_exit(data, "Error: Invalid map (not enclosed)\n");
	if (!has_valid_elements(data->map.map))
		error_exit(data, "Error: Invalid map (invalid elements)\n");
	init_map_data(data);
	if (!is_reachable(data))
		error_exit(data, "Error: Invalid map (unreachable exit/collectible)\n");
	if (data->map.width * TILE_SIZE > 1920
		|| (data->map.height + 1) * TILE_SIZE > 1080)
		error_exit(data, "Error: Invalid map (too big)\n");
}
