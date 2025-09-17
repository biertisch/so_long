/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:07:17 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/17 08:36:34 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	validate_extension(t_data *data, char *filename)
{
	while (*filename == '.' || *filename == '/')
		filename++;
	while (*filename && *filename != '.')
		filename++;
	if (ft_strncmp(filename, ".ber", 4))
		error_exit(data, "Error: Invalid file extension\n");
}

static char	**append_line(char **map, char *line, int i)
{
	char	**new_map;
	int		j;

	new_map = ft_calloc(sizeof(char *), i + 2);
	if (!new_map)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if (map)
			new_map[j] = map[j];
		j++;
	}
	new_map[i] = ft_strtrim(line, "\r\n");
	if (!new_map[i])
	{
		free_string_array(new_map);
		return (NULL);
	}
	free (map);
	return (new_map);
}

void	parse_map(t_data *data, char *filename)
{
	char	**tmp;
	char	*line;
	int		fd;
	int		i;

	validate_extension(data, filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(data, "Error: Failed access to file\n");
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		tmp = append_line(data->map.map, line, i);
		if (!tmp)
			error_exit(data, "Error: Failed memory allocation\n");
		free(line);
		data->map.map = tmp;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
