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

void	update_ent_frame(t_ent *ent, int new_dir)
{
	int	new_frame;

	if (ent->current_dir != new_dir)
		new_frame = 0;
	else
		new_frame = (ent->current_frame + 1) % ent->frame_count;
	ent->current_dir = new_dir;
	ent->current_frame = new_frame;
}

static void	collect(t_data *data, int new_row, int new_col)
{
	data->collected++;
	if (data->collected == data->collectibles)
		data->unlock_exit = 1;
	data->map.map[new_row][new_col] = '0';
}

static void	move(t_data *data, int new_row, int new_col, int dir)
{
	if (new_row >= data->map.height || new_col >= data->map.width
		|| data->map.map[new_row][new_col] == '1')
		return ;
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->background.img,
		data->win.width / 2 - 161, data->win.height - 32);
	update_ent_frame(&data->player, dir);
	data->player.row = new_row;
	data->player.col = new_col;
	data->moves++;
	if (data->map.map[new_row][new_col] == 'C')
		collect(data, new_row, new_col);
	else if (data->map.map[new_row][new_col] == 'E' && !data->unlock_exit)
		mlx_put_image_to_window(data->mlx, data->win.ptr,
			data->closed_exit_msg.img, data->win.width / 2 - 161,
			data->win.height - 32);
	else if (data->map.map[new_row][new_col] == 'E' && data->unlock_exit
		&& !data->game_over)
	{
		data->game_over = VICTORY;
		ft_printf("Total moves: %d\n", data->moves);
		ft_printf("You won the game. So long!\n");
	}
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		close_game(param);
	if (data->game_over)
		return (0);
	if (keycode == KEY_UP || keycode == KEY_W)
		move(data, data->player.row - 1, data->player.col, DIR_UP);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(data, data->player.row + 1, data->player.col, DIR_DOWN);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(data, data->player.row, data->player.col - 1, DIR_LEFT);
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(data, data->player.row, data->player.col + 1, DIR_RIGHT);
	return (0);
}
