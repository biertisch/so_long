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

static void	free_image(void *mlx, void *img)
{
	if (mlx && img)
		mlx_destroy_image(mlx, img);
}

static void	free_images(t_data *data)
{
	free_image(data->mlx, data->img_floor);
	free_image(data->mlx, data->img_wall);
	free_image(data->mlx, data->img_player);
	free_image(data->mlx, data->img_collect);
	free_image(data->mlx, data->img_exit);
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
