/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:57:09 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 14:57:09 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	flood_fill(char **map, t_point size, t_point start, t_found *found)
{
	if (start.row < 0 || start.row >= size.row
		|| start.col < 0 || start.col >= size.col
		|| map[start.row][start.col] == '1'
		|| map[start.row][start.col] == 'F')
		return ;
	if (map[start.row][start.col] == 'E')
		found->exit++;
	if (map[start.row][start.col] == 'C')
		found->collectibles++;
	map[start.row][start.col] = 'F';
	flood_fill(map, size, (t_point){start.row, start.col + 1}, found);
	flood_fill(map, size, (t_point){start.row, start.col - 1}, found);
	flood_fill(map, size, (t_point){start.row - 1, start.col}, found);
	flood_fill(map, size, (t_point){start.row + 1, start.col}, found);
}

static char	**duplicate_map(char **map, int rows)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(rows + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (map[i])
	{
		tmp[i] = ft_strdup(map[i]);
		if (!tmp[i])
		{
			free_arr(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

int	is_reachable(t_data *data)
{
	char	**tmp;

	tmp = duplicate_map(data->map, data->map_size.row);
	if (!tmp)
		error_exit(data, "Error: Memory allocation failed\n");
	flood_fill(tmp, data->map_size, data->player_pos, &data->found);
	free_arr(tmp);
	if (data->found.exit != 1 || data->found.collectibles != data->collectibles)
		return (0);
	data->found.exit = 0;
	data->found.collectibles = 0;
	return (1);
}
