/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:02:38 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/08 19:02:38 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_frame(t_ent_anim *ent, int dir)
{
	int	frame;

	if (ent->current_dir != dir)
		frame = 0;
	else
		frame = (ent->current_frame + 1) % ent->frame_count;
	ent->current_dir = dir;
	ent->current_frame = frame;
}

static void	collect(t_data *data, int new_row, int new_col)
{
	data->collected++;
	if (data->collected == data->collectibles)
		data->unlock_exit = 1;
	data->map[new_row][new_col] = '0';
}

static void	move(t_data *data, int new_row, int new_col, int dir)
{
	mlx_put_image_to_window(data->mlx, data->win, data->black.img,
		data->win_width / 2 - 161, data->win_height - 32);
	if (new_row >= data->map_height || new_col >= data->map_width
		|| data->map[new_row][new_col] == '1')
		return ;
	update_frame(&data->player, dir);
	data->player.row = new_row;
	data->player.col = new_col;
	data->moves++;
	if (data->map[new_row][new_col] == 'C')
		collect(data, new_row, new_col);
	else if (data->map[new_row][new_col] == 'E' && data->unlock_exit == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->closed_exit.img,
			data->win_width / 2 - 161, data->win_height - 32);
	else if (data->map[new_row][new_col] == 'E' && data->unlock_exit == 1
		&& !data->game_over)
	{
		ft_printf("Total moves: %d\n", data->moves);
		ft_printf("You won the game. So long!\n");
		data->game_over = 1;
	}
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC || keycode == Q_KEY)
		close_game(param);
	if (data->game_over)
		return (0);
	if (keycode == UP_ARROW || keycode == W_KEY)
		move(data, data->player.row - 1, data->player.col, 0);
	else if (keycode == DOWN_ARROW || keycode == S_KEY)
		move(data, data->player.row + 1, data->player.col, 1);
	else if (keycode == LEFT_ARROW || keycode == A_KEY)
		move(data, data->player.row, data->player.col - 1, 2);
	else if (keycode == RIGHT_ARROW || keycode == D_KEY)
		move(data, data->player.row, data->player.col + 1, 3);
	return (0);
}
