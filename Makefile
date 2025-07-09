NAME = so_long

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = mlx/
MLX = $(MLX_DIR)libmlx.a

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR),\
		main.c free.c exit.c parser.c validate.c flood_fill.c\
		map_data.c mlx_data.c transparency.c render.c move.c)

OBJ_DIR = obj/
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude -I$(LIBFT_DIR)include -I$(MLX_DIR) 
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) obj $(OBJ) 
	$(CC) $(OBJ) $(LFLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all run clean fclean re