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

# define TILE_SIZE 64
# define ESC 65307
# define Q_KEY 113
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define U_ARROW 65362
# define D_ARROW 65364
# define L_ARROW 65361
# define R_ARROW 65363
# define MAGIC_COLOR 0xFF00FF
# define EXIT_FRAMES 24
# define WALL_FRAMES 22
# define PLAYER_FRAMES 9

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

typedef struct s_env_anim
{
	t_image	*frames;
	int		frame_count;
	int		current_frame;
	int		frame_tick;
	int		tick_rate;
}			t_env_anim;

typedef struct s_ent_anim
{
	t_image	**frames;
	t_image	on_exit_frame;
	int		frame_count;
	int		current_frame;
	int		current_dir;
	int		frame_tick;
	int		frame_rate;
}			t_ent_anim;

typedef struct s_data
{
	char		**map;
	int			map_width;
	int			map_height;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			player_row;
	int			player_col;
	int			collectibles;
	int			collected;
	int			unlock_exit;
	int			moves;
	t_ent_anim	player;
	t_env_anim	exit;
	t_env_anim	wall;
	t_image		floor;
	t_image		collect;
}				t_data;

//free.c
void	free_data(t_data *data);
void	free_arr(char **arr);

//end.c
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

//data.c
void	init_map_data(t_data *data);
void	init_mlx_data(t_data *data);

//image.c
void	load_image(t_data *data, t_image *dest, int layers, char *filename);
void	load_exit_frames(t_data *data);
void	load_wall_frames(t_data *data);
void	load_player_frames(t_data *data);

//filename.c
void	build_ent_filename(char *dest, char *base, int dir, int frame);
void	build_env_filename(char *dest, char *base, int frame);

//draw.c
void	draw_with_transparency(t_image *dest, t_image *src);
t_image	process_raw_image(t_data *data, char *filename);
void	create_image_buffer(t_data *data, t_image *dest);

//render.c
void	render_map(t_data *data);

//game_loop.c
int		game_loop(t_data *data);

//player.c
int		key_handler(int keycode, void *param);

#endif