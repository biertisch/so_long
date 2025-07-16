/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:10:30 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/09 11:10:30 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	handle_game_end(t_data *data)
{
	if (!data->end_tick)
		render_map(data, data->map.map);
	if (data->game_over == VICTORY && !data->end_tick)
		mlx_put_image_to_window(data->mlx, data->win.ptr, data->victory_msg.img,
			data->win.width / 2 - 190, data->win.height / 2 - 105);
	else if (data->game_over == DEFEAT && !data->end_tick)
		mlx_put_image_to_window(data->mlx, data->win.ptr, data->defeat_msg.img,
			data->win.width / 2 - 190, data->win.height / 2 - 105);
	data->end_tick++;
	if (data->end_tick >= 25000)
		close_game((void *)data);
}

int	close_game(void *param)
{
	free_data((t_data *)param);
	exit(0);
	return (0);
}

void	error_exit(t_data *data, char *error_msg)
{
	if (data)
		free_data(data);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	exit(1);
}
