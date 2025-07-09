/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
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

static void	update_old_tile(t_data *data, int old_row, int old_col)
{
	if (data->map[old_row][old_col] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img_exit,
			data->player_col * TILE_SIZE,
			data->player_row * TILE_SIZE);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor,
			data->player_col * TILE_SIZE,
			data->player_row * TILE_SIZE);
}

static void	update_collectibles(t_data *data, int new_row, int new_col)
{
	data->collected++;
	if (data->collected == data->collectibles)
		data->unlock_exit = 1;
	data->map[new_row][new_col] = '0';
}

static void	move(t_data *data, int new_row, int new_col)
{
	if (new_row >= data->map_height || new_col >= data->map_width
		|| data->map[new_row][new_col] == '1')
		return ;
	else if (data->map[new_row][new_col] == 'C')
		update_collectibles(data, new_row, new_col);
	else if (data->map[new_row][new_col] == 'E' && data->unlock_exit == 1)
		victory(data);
	update_old_tile(data, data->player_row, data->player_col);
	mlx_put_image_to_window(data->mlx, data->win, data->img_player,
		new_col * TILE_SIZE, new_row * TILE_SIZE);
	data->player_row = new_row;
	data->player_col = new_col;
	update_moves(data);
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65361 || keycode == 97)
		move(data, data->player_row, data->player_col - 1);
	else if (keycode == 65363 || keycode == 100)
		move(data, data->player_row, data->player_col + 1);
	else if (keycode == 65362 || keycode == 119)
		move(data, data->player_row - 1, data->player_col);
	else if (keycode == 65364 || keycode == 115)
		move(data, data->player_row + 1, data->player_col);
	else if (keycode == 65307 || keycode == 113)
		close_game(param);
	return (0);
}
