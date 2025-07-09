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

# define TILE_SIZE 32
# define ESC 65307
# define Q_KEY 113
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define L_ARROW 65361
# define R_ARROW 65363
# define U_ARROW 65362
# define D_ARROW 65364
# define MAGIC_COLOR 0xFF00FF

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_data
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
	t_image	floor;
	t_image	wall;
	t_image	player;
	t_image	collect;
	t_image	exit;
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

//mlx_data.c
void	init_display_data(t_data *data);

//transparency.c
void	draw_with_transparency(t_image *dest, t_image *src);

//render.c
void	render_map(t_data *data);
int		resize_handler(void *param);

//move.c
int		key_handler(int keycode, void *param);

#endif