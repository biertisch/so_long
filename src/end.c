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

void	defeat(t_data *data)
{
	data->game_over = 1;
	mlx_put_image_to_window(data->mlx, data->win, data->text_defeat.img, data->win_width / 2 - 110, data->win_height - 32);
	ft_printf("Total moves: %d\n", data->moves);
	ft_printf("You lost the game. So long!\n");

}

void	victory(t_data *data)
{
	data->game_over = 1;
	mlx_put_image_to_window(data->mlx, data->win, data->text_victory.img, data->win_width / 2 - 117, data->win_height - 32);
	ft_printf("Total moves: %d\n", data->moves);
	ft_printf("You won the game. So long!\n");
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
