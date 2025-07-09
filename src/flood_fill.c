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

void	flood_fill(t_data *data, char **map, int row, int col)
{
	if (row < 0 || row >= data->map_height || col < 0 || col >= data->map_width
		|| map[row][col] == '1' || map[row][col] == 'F')
		return ;
	if (map[row][col] == 'E')
		data->unlock_exit++;
	if (map[row][col] == 'C')
		data->collected++;
	map[row][col] = 'F';
	flood_fill(data, map, row, col + 1);
	flood_fill(data, map, row, col - 1);
	flood_fill(data, map, row - 1, col);
	flood_fill(data, map, row + 1, col);
}

char	**duplicate_map(char **map, int rows)
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
