##
## EPITECH PROJECT, 2021
## zappy
## File description:
## Makefile
##

CC			=	gcc

MAIN		=	$(addprefix $(SRC_D), main.c)
OBJ_M		=	$(MAIN:.c=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.c=.o)
SRC_D		=	src/
SRC_F		=	accept_client.c					\
				add_client.c					\
				create_client.c					\
				destroy_client.c				\
				create_server.c					\
				destroy_server.c				\
				remove_client.c					\
				server_run.c					\
				handle_input.c					\
				error_handling.c				\
				time_functions.c 				\
				create_cmds.c 					\
				handle_buffer.c					\
				add_team.c 						\
				send_responses.c 				\
				graphical_management.c 			\
				create_ia_client.c 				\
				life_management.c 				\
				eggs_management.c 				\
				send_events_new_ia.c 			\
				ressources_management.c 		\
				map/create_map.c 				\
				map/create_tile_links.c			\
				map/content_functions.c 		\
				map/get_needed_ressources.c 	\
				map/map_generate_ressources.c 	\
				commands/ia_commands/look_cmd/get_north_vision_line.c \
				commands/ia_commands/look_cmd/get_south_vision_line.c \
				commands/ia_commands/look_cmd/get_west_vision_line.c \
				commands/ia_commands/look_cmd/get_east_vision_line.c \
				commands/ia_commands/look_cmd/look_cmd.c \
				commands/ia_commands/look_cmd/ressources_functions.c \
				commands/ia_commands/incantation_cmd/incantation_cmd.c \
				commands/ia_commands/incantation_cmd/incantation_checks.c \
				commands/ia_commands/forward_cmd.c 	\
				commands/ia_commands/left_cmd.c 	\
				commands/ia_commands/right_cmd.c 	\
				commands/ia_commands/inventory_cmd.c 	\
				commands/ia_commands/connect_nbr_cmd.c 	\
				commands/ia_commands/take_cmd.c 	\
				commands/ia_commands/set_cmd.c 	\
				commands/ia_commands/eject_cmd.c 	\
				commands/ia_commands/broadcast_cmd.c 	\
				commands/ia_commands/fork_cmd.c 	\
				graph_cmd.c \
				graph_cmd2.c \
				graph_cmd3.c \
				graph_cmd4.c \
				graph_cmd5.c \

UT_SRC		=	$(addprefix $(UT_SRC_D), $(UT_SRC_F))
UT_OBJ		=	$(UT_SRC:.c=.o)
UT_SRC_D	=	tests/
UT_SRC_F	=

INC			=	-I./inc

CFLAGS		=	$(DBFLAGS) $(WFLAGS) $(INC) $(LDFLAGS)

WFLAGS		=	-Wall -Wextra -Werror

DBFLAGS		=	-g -g3 -ggdb

LDFLAGS		=	-L./lib/ -lmy

LDFLAGS_UT  =	-lcriterion --coverage

BIN			=	zappy_server

UT_BIN		=	unit_tests

all: $(BIN)

.PHONY: all
$(BIN): makelib $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_M) $(OBJ) $(LDFLAGS)

makelib:
	make -C ./lib/my/ all

.PHONY: tests_run
tests_run: clean $(OBJ) $(UT_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS_UT) -o $(UT_BIN) $(OBJ) $(UT_OBJ) $(LDFLAGS)
	./$(UT_BIN)

.PHONY: coverage
coverage:
	gcovr -r . --exclude-directories tests
	gcovr -b --exclude-directories tests

.PHONY: clean
clean:
	rm -f $(OBJ) $(OBJ_M)
	rm -f $(OBJ_UT)
	rm -f *.gc*

.PHONY: fclean
fclean: clean
	rm -f $(BIN)
	rm -f $(BIN_UT)

.PHONY: re
re: fclean all