/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:02:09 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/05 15:02:09 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include <fcntl.h>

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

typedef struct	s_data
{
	char	**map;
	int		map_width;
	int		map_height;
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	int		player_row;
	int		player_col;
	int		collectibles;
	int		collected;
	int		unlock_exit;
	int		moves;
	void	*img_floor;
	void	*img_wall;
	void	*img_player;
	void	*img_collect;
	void	*img_exit;
}			t_data;

//free.c
void	free_data(t_data *data);
void	free_arr(char **arr);

//exit.c
void	error_exit(t_data *data, char *error_msg);
int		close_game(void *param);
void	victory(t_data *data);

//parser.c
void	parse_map(t_data *data, char *file);

//validate.c
void	validate_map(t_data *data);

//flood_fill.c
void	flood_fill(t_data *data, char **map, int row, int col);
char	**duplicate_map(char **map, int rows);

//map_data.c
void	init_map_data(t_data *data);

//display_data.c
void	init_display_data(t_data *data);

//render.c
void	render_map(t_data *data);

//moves.c
int key_handler(int keycode, void *param);

#endif