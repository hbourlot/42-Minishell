CC = cc
LIB = tests.a
OBJ_DIR = obj/
C_FUNCTIONS = test
LINK = -L./library/ -lft
VALGRIND = valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=yes
NAME = run
LIBFT = ./library/libft.a

SRC_FILES = $(C_FUNCTIONS:=.c)

OBJ_SRC = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

all:	$(NAME)

$(NAME):		$(LIBFT) $(LIB)
				$(CC) $(LIB) $(LINK) -o $@

$(LIBFT):
			make -s -C ./library

$(LIB):		$(OBJ_SRC)
			@ar rcs $@ $^

$(OBJ_DIR)%.o: %.c
			@mkdir -p $(dir $@)
			$(CC) -c -I. $< -o $@

clean:
	@make fclean -s -C ./library
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIB)

r: all
	./$(NAME)

v: clean all
	$(VALGRIND) --leak-check=full ./$(NAME)
