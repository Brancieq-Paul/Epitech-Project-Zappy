##
## EPITECH PROJECT, 2021
## zappy
## File description:
## Makefile
##

RULES = ai server

.SILENT all: $(RULES)

ai:
	make -C ai
	cp ai/zappy_ai .

server:
	make -C server all
	cp server/zappy_server .

clean:
	make -C ai clean
	make -C server clean

fclean:
	make -C ai fclean
	make -C server fclean
	rm -f zappy_ai zappy_server

re: fclean all

.PHONY: $(RULES)