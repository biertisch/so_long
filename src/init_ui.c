/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:03:51 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/16 10:03:51 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	build_char_filename(char *dest, int idx)
{
	const char	*prefix;
	const char	*suffix;
	int			i;

	prefix = "textures/ui/char_";
	suffix = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	if (idx >= 10)
		dest[i++] = '0' + (idx / 10);
	dest[i++] = '0' + (idx % 10);
	while (*suffix)
		dest[i++] = *suffix++;
	dest[i] = '\0';
}

static void	load_text_image(t_data *data, t_image *text, char *filename)
{
	text->img = mlx_xpm_file_to_image(data->mlx, filename, &text->width,
			&text->height);
	if (!text->img)
		error_exit(data, "Error: Failed to load image\n");
}

void	init_ui(t_data *data)
{
	char	path[64];
	int		i;

	load_text_image(data, &data->background, "textures/ui/background.xpm");
	load_text_image(data, &data->move_counter, "textures/ui/move_counter.xpm");
	load_text_image(data, &data->collect_counter,
		"textures/ui/collect_counter.xpm");
	load_text_image(data, &data->closed_exit_msg,
		"textures/ui/closed_exit_msg.xpm");
	load_text_image(data, &data->victory_msg, "textures/ui/victory_msg.xpm");
	load_text_image(data, &data->defeat_msg, "textures/ui/defeat_msg.xpm");
	data->chars = ft_calloc(sizeof(t_image), CHAR_FRAMES);
	if (!data->chars)
		error_exit(data, "Error: Memory allocation failed\n");
	i = 0;
	while (i < CHAR_FRAMES)
	{
		build_char_filename(path, i);
		load_text_image(data, &data->chars[i], path);
		i++;
	}
}
