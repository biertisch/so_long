/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:02:38 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/08 19:02:38 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


static void	victory(t_data *data)
{
	ft_printf("You won the game. So long!\n");
	close_game((void *)data);
}

static void	update_moves(t_data *data)
{
	data->moves++;
	ft_printf("Moves: %d\n", data->moves);
}

static void	update_old_tile(t_data *data, int old_row, int old_col)
{
	if (data->map[old_row][old_col] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img_exit,
			data->player_pos.col * data->tile_size,
			data->player_pos.row * data->tile_size);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor,
			data->player_pos.col * data->tile_size,
			data->player_pos.row * data->tile_size);
	
}

static void	update_collectibles(t_data *data, int new_row, int new_col)
{
	data->found.collectibles++;
	if (data->found.collectibles == data->collectibles)
		data->found.exit = 1;
	data->map[new_row][new_col] = '0';
}

void	move(t_data *data, int new_row, int new_col)
{
	if (new_row >= data->map_size.row || new_col >= data->map_size.col
		|| data->map[new_row][new_col] == '1')
		return ;
	else if (data->map[new_row][new_col] == 'C')
		update_collectibles(data, new_row, new_col);
	else if (data->map[new_row][new_col] == 'E' && data->found.exit == 1)
		victory(data);
	update_old_tile(data, data->player_pos.row, data->player_pos.col);
	mlx_put_image_to_window(data->mlx, data->win, data->img_player,
		new_col * data->tile_size, new_row * data->tile_size);
	data->player_pos.row = new_row;
	data->player_pos.col = new_col;
	update_moves(data);
}

int key_handler(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65361 || keycode == 	97)
		move(data, data->player_pos.row, data->player_pos.col - 1);
	else if (keycode == 65363 || keycode == 100)
		move(data, data->player_pos.row, data->player_pos.col + 1);
	else if (keycode == 65362 || keycode == 119)
		move(data, data->player_pos.row - 1, data->player_pos.col);
	else if (keycode == 65364 || keycode == 115)
		move(data, data->player_pos.row + 1, data->player_pos.col);
	else if (keycode == 65307 || keycode == 113)
		close_game(param);
	return (0);
}

int	close_game(void *param)
{
	free_data((t_data *)param);
	exit(0);
	return (0);
}

