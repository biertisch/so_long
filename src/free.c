/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:18:49 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/07 15:18:49 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

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

static void	free_2d_frames(t_data *data, t_image **frames, int frame_count)
{
	int	i;

	if (!frames)
		return ;
	i = 0;
	while (i < 4)
	{
		free_frames(data, frames[i], frame_count);
		i++;
	}
	free(frames);
}

static void	free_images(t_data *data)
{
	if (data->floor.img)
		mlx_destroy_image(data->mlx, data->floor.img);
	if (data->collect.img)
		mlx_destroy_image(data->mlx, data->collect.img);
	if (data->exit.img)
		mlx_destroy_image(data->mlx, data->exit.img);
	if (data->text_background.img)
		mlx_destroy_image(data->mlx, data->text_background.img);
	if (data->text_moves.img)
		mlx_destroy_image(data->mlx, data->text_moves.img);
	if (data->text_closed_exit.img)
		mlx_destroy_image(data->mlx, data->text_closed_exit.img);
	if (data->text_victory.img)
		mlx_destroy_image(data->mlx, data->text_victory.img);
	if (data->text_defeat.img)
		mlx_destroy_image(data->mlx, data->text_defeat.img);		
	free_frames(data, data->wall.frames, data->wall.frame_count);
	free_frames(data, data->chars, 10);
	free_2d_frames(data, data->player.frames, data->player.frame_count);
	free_2d_frames(data, data->player.exit_layer, data->player.frame_count);
	free_2d_frames(data, data->enemy.frames, data->enemy.frame_count);
	free_2d_frames(data, data->enemy.collect_layer, data->enemy.frame_count);
	free_2d_frames(data, data->enemy.exit_layer, data->enemy.frame_count);
}

void	free_data(t_data *data)
{
	free_arr(data->map);
	free_images(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	ft_bzero(data, sizeof(t_data));
}
