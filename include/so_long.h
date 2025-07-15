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
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define MAGIC_COLOR 0xFF00FF
# define WALL_FRAMES 22
# define PLAYER_FRAMES 9
# define ENEMY_FRAMES 6
# define CHAR_FRAMES 11

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
	t_image	**collect_layer;
	t_image	**exit_layer;
	int		row;
	int		col;
	int		frame_count;
	int		current_frame;
	int		current_dir;
	int		frame_tick;
	int		tick_rate;
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
	int			collectibles;
	int			collected;
	int			unlock_exit;
	int			moves;
	int			enemy_count;
	int			game_over;
	int			end_tick;
	t_ent_anim	player;
	t_ent_anim	*enemy;
	t_env_anim	wall;
	t_image		exit;
	t_image		floor;
	t_image		collect;
	t_image		black;
	t_image		move_counter;
	t_image		collect_counter;
	t_image		closed_exit;
	t_image		victory;
	t_image		defeat;
	t_image		*chars;
}				t_data;

//draw.c
void	draw_with_transparency(t_image *dest, t_image *src);

//end.c
void	handle_game_end(t_data *data);
void	error_exit(t_data *data, char *error_msg);
int		close_game(void *param);

//enemy.c
int		move_enemy(t_data *data, t_ent_anim *enemy);

//filename.c
void	build_char_filename(char *dest, int idx);
void	build_ent_filename(char *dest, char *base, int dir, int frame);
void	build_env_filename(char *dest, char *base, int frame);

//flood_fill.c
void	flood_fill(t_data *data, char **map, int row, int col);
char	**duplicate_map(char **map, int rows);

//free.c
void	free_data(t_data *data);
void	free_arr(char **arr);

//game_loop.c
int		game_loop(t_data *data);

//image.c
void	load_wall_frames(t_data *data);
void	load_player_frames(t_data *data);
void	load_enemy_frames(t_data *data);

//map_data.c
void	init_map_data(t_data *data);

//mlx_data.c
void	init_mlx_data(t_data *data);
void	load_image(t_data *data, t_image *dest, t_image *layer, char *filename);

//parser.c
void	parse_map(t_data *data, char *file);

//player.c
int		key_handler(int keycode, void *param);
void	update_frame(t_ent_anim *ent, int dir);

//render.c
void	render_map(t_data *data);
int		render_counter(t_data *data, int n, int x);

//text.c
void	load_text(t_data *data);

//validate.c
void	validate_map(t_data *data);

#endif