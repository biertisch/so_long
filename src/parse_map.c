/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:07:17 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 10:07:17 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	**append_line(char **map, char *line, int i)
{
	char	**new_map;
	int		j;

	new_map = ft_calloc((i + 2), sizeof(char *));
	if (!new_map)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_map[j] = map[j];
		j++;
	}
	new_map[i] = ft_strtrim(line, "\r\n");
	if (!new_map[i])
	{
		free_arr(new_map);
		return (NULL);
	}
	free (map);
	return (new_map);
}

void	parse_map(t_data *data, char *file)
{
	char	**tmp;
	char	*line;
	int		fd;
	int		i;	

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(data, "Error: Failed access to file\n");
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		tmp = append_line(data->map, line, i);
		if (!tmp)
			error_exit(data, "Error: Failed memory allocation\n");
		free(line);
		data->map = tmp;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	validate_map(data);
}
