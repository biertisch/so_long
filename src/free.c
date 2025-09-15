/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:18:49 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/09 22:37:59 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_frames(t_data *data, t_image *frames, int frame_count)
{
	int	i;

	if (!frames)
		return ;
	i = 0;
	while (i < frame_count)
	{
		if (frames[i].img)
			mlx_destroy_image(data->mlx, frames[i].img);
		i++;
	}
	free(frames);
}

static void	free_env_and_ui(t_data *data)
{
	if (data->floor.img)
		mlx_destroy_image(data->mlx, data->floor.img);
	if (data->collect.img)
		mlx_destroy_image(data->mlx, data->collect.img);
	if (data->exit.img)
		mlx_destroy_image(data->mlx, data->exit.img);
	if (data->background.img)
		mlx_destroy_image(data->mlx, data->background.img);
	if (data->move_counter.img)
		mlx_destroy_image(data->mlx, data->move_counter.img);
	if (data->collect_counter.img)
		mlx_destroy_image(data->mlx, data->collect_counter.img);
	if (data->closed_exit_msg.img)
		mlx_destroy_image(data->mlx, data->closed_exit_msg.img);
	if (data->victory_msg.img)
		mlx_destroy_image(data->mlx, data->victory_msg.img);
	if (data->defeat_msg.img)
		mlx_destroy_image(data->mlx, data->defeat_msg.img);
	free_frames(data, data->wall.frames, data->wall.frame_count);
	free_frames(data, data->chars, CHAR_FRAMES);
}

static void	free_ent(t_data *data, t_ent *ent)
{
	int	i;

	i = 0;
	while (i < DIRECTIONS)
	{
		if (ent->frames && ent->frames[i])
			free_frames(data, ent->frames[i], ent->frame_count);
		if (ent->collect_layer && ent->collect_layer[i])
			free_frames(data, ent->collect_layer[i], ent->frame_count);
		if (ent->exit_layer && ent->exit_layer[i])
			free_frames(data, ent->exit_layer[i], ent->frame_count);
		i++;
	}
	if (ent->frames)
		free(ent->frames);
	if (ent->collect_layer)
		free(ent->collect_layer);
	if (ent->exit_layer)
		free(ent->exit_layer);
}

void	free_data(t_data *data)
{
	int	i;

	free_string_array(data->map.map);
	free_ent(data, &data->player);
	i = 0;
	while (i < data->enemy_count)
	{
		free_ent(data, &data->enemy[i]);
		i++;
	}
	free(data->enemy);
	free_env_and_ui(data);
	if (data->win.ptr)
		mlx_destroy_window(data->mlx, data->win.ptr);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	ft_bzero(data, sizeof(t_data));
}
