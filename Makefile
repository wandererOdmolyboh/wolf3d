
NAME		= wolf3d

#	compiler
CC			= gcc
FLAGS		= -Wall -Wextra -Werror

#	files
SRC			=  main.c find_w_f.c cast_text.c intitial_value.c leaks.c raycast.c\
work_w_pixels.c manegment.c file_reader.c check_txt.c valid_maps.c

OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#	directories
INC_DIR		= ./inc/
OBJ_DIR		= ./obj/
SRC_DIR		= ./src/
FRM_DIR		= frameworks

#	ft library
FT			= ./libft/
FT_LIB		= $(addprefix $(FT), libft.a)
FT_INC		= -I $(FT)
FT_LNK		= -L $(FT) -lft

#	SDL

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	SDL_LNK	= -l SDL2 -l SDL2_image
else
	SDL_INC	= -I $(CURDIR)/$(FRM_DIR)/SDL2.framework/Headers \
				-I $(CURDIR)/$(FRM_DIR)/SDL2_image.framework/Headers \
				-F $(CURDIR)/$(FRM_DIR)

	SDL_LNK	= -F $(CURDIR)/$(FRM_DIR) \
				-rpath $(CURDIR)/$(FRM_DIR) \
				-framework SDL2 -framework SDL2_image 
endif

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(FT_LIB):
	@make -C $(FT)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) $(FT_INC) $(SDL_INC) -o $@ -c $<
	@echo "(+) $@"

$(NAME):$(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(FT_LNK) -I $(INC_DIR) $(SDL_INC) $(SDL_LNK)\
	-lm -o $(NAME)
	@echo "$(NAME) ready to win!"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(FT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(FT) fclean

re: fclean all