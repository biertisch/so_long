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

static void	update_moves(t_data *data)
{
	data->moves++;
	ft_printf("Moves: %d\n", data->moves);
}

static void	update_player_frame(t_data *data, int dir)
{
	int	frame;

	if (data->player.current_dir != dir)
		frame = 0;
	else
		frame = (data->player.current_frame + 1) % PLAYER_FRAMES;
	data->player.current_dir = dir;
	data->player.current_frame = frame;
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
	if (new_row >= data->map_height || new_col >= data->map_width
		|| data->map[new_row][new_col] == '1')
		return ;
	else if (data->map[new_row][new_col] == 'C')
		collect(data, new_row, new_col);
	else if (data->map[new_row][new_col] == 'E' && data->unlock_exit == 0)
		ft_printf("Are you sure you collected everything?\n");
	else if (data->map[new_row][new_col] == 'E' && data->unlock_exit == 1)
		victory(data);
	update_player_frame(data, dir);
	data->player_row = new_row;
	data->player_col = new_col;
	update_moves(data);
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == U_ARROW || keycode == W_KEY)
		move(data, data->player_row - 1, data->player_col, 0);
	else if (keycode == D_ARROW || keycode == S_KEY)
		move(data, data->player_row + 1, data->player_col, 1);
	else if (keycode == L_ARROW || keycode == A_KEY)
		move(data, data->player_row, data->player_col - 1, 2);
	else if (keycode == R_ARROW || keycode == D_KEY)
		move(data, data->player_row, data->player_col + 1, 3);
	else if (keycode == ESC || keycode == Q_KEY)
		close_game(param);
	return (0);
}
