NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
AR = ar -r
RM = rm -f
HEAD = cub3d.h
LIBFT = ./Libft/libft.a
HEADLIBFT = ./Libft/libft.h
HEADGNL = ./get_next_line/get_next_line.h
BUILD = MLX42/build
MLX = MLX42/build/libmlx42.a  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"


SRC = main.c\
		./get_next_line/get_next_line.c\
		./parsing/start_parsing.c\
		./parsing/parsing_map.c\
		./parsing/save_vars.c\
		./parsing/check_vars.c\
		./parsing/save_player_pos.c\
		./parsing/split_map.c\
		./parsing/valide_map.c\


LIBFTSRC = ./Libft/ft_atoi.c\
		./Libft/ft_bzero.c\
		./Libft/ft_calloc.c\
		./Libft/ft_isalnum.c\
		./Libft/ft_isalpha.c\
		./Libft/ft_isprint.c\
		./Libft/ft_isdigit.c\
		./Libft/ft_isascii.c\
		./Libft/ft_itoa.c\
		./Libft/ft_memchr.c\
		./Libft/ft_memcpy.c\
		./Libft/ft_memset.c\
		./Libft/ft_memcmp.c\
		./Libft/ft_memmove.c\
		./Libft/ft_split.c\
		./Libft/ft_strlcat.c\
		./Libft/ft_strlen.c\
		./Libft/ft_strnstr.c\
		./Libft/ft_strrchr.c\
		./Libft/ft_strchr.c\
		./Libft/ft_strlcpy.c\
		./Libft/ft_strlcat.c\
		./Libft/ft_strdup.c\
		./Libft/ft_strncmp.c\
		./Libft/ft_strlcat.c\
		./Libft/ft_strtrim.c\
		./Libft/ft_substr.c\
		./Libft/ft_tolower.c\
		./Libft/ft_toupper.c\
		./Libft/ft_strmapi.c\
		./Libft/ft_striteri.c\
		./Libft/ft_strjoin.c\
		./Libft/ft_putchar_fd.c\
		./Libft/ft_putstr_fd.c\
		./Libft/ft_putendl_fd.c\
		./Libft/ft_putnbr_fd.c\
		./Libft/libft.h



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(BUILD):
	@if [ ! -d MLX42/build ]; then \
		(cd MLX42 && cmake -B build); \
	fi

$(LIBFT): $(LIBFTSRC)
	make -C ./Libft



$(NAME): $(BUILD) $(LIBFT)  $(OBJ)
	make -C MLX42/build
	$(CC) $(OBJ) $(LIBFT)   $(MLX) -o $(NAME)


%.o : %.c $(HEAD) $(HEADGNL)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) main.o
	make clean -C ./Libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) -r MLX42/build

re: fclean all

.PHONY: all bonus clean fclean re