CC		= gcc
CFLAGS	= -Wall -O3 -std=c11
LDLIBS	= -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-audio
FILES	= $(wildcard Sources/*.c)

TronGame: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o TronGame $(LDLIBS)

erase: TronGame
	rm TronGame