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

static void	free_ent_frames(t_data *data, t_ent_anim *entity)
{
	int	i;
	int	j;
	
	if (entity->on_exit_frame.img)
		mlx_destroy_image(data->mlx, entity->on_exit_frame.img);
	if (!entity->frames)
		return ;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < entity->frame_count)
		{
			if (entity->frames[i][j].img)
				mlx_destroy_image(data->mlx, entity->frames[i][j].img);
			j++;
		}
		free(entity->frames[i]);
		i++;
	}
	free(entity->frames);
}

static void	free_env_frames(t_data *data, t_env_anim *obj)
{
	int	i;
	
	if (!obj->frames)
		return ;
	i = 0;
	while (i < obj->frame_count)
	{
		if (obj->frames[i].img)
			mlx_destroy_image(data->mlx, obj->frames[i].img);
		i++;
	}
	free(obj->frames);
}

static void	free_images(t_data *data)
{
	if (data->floor.img)
		mlx_destroy_image(data->mlx, data->floor.img);
	if (data->collect.img)
		mlx_destroy_image(data->mlx, data->collect.img);
	free_env_frames(data, &data->wall);
	free_env_frames(data, &data->exit);
	free_ent_frames(data, &data->player);
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
