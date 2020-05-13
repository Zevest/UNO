CC=gcc
HEADER= include/
CFLAGS=-Wall#-I $(HEADER)
OUT= build/
SRCDIR = src/
SRC=  pile.c carte.c joueur.c play.c main.c csvloader.c
OBJ=$(SRC:.c=.o)
PROGNAME=UNO.exe
RM=rm -rf

all: $(OUT)$(PROGNAME)



$(OUT)$(PROGNAME): $(addprefix $(OUT), $(OBJ))
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)main.o:	$(addprefix $(SRCDIR), main.c)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)carte.o: $(addprefix $(SRCDIR), carte.c) $(HEADER)carte.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)pile.o: $(addprefix $(SRCDIR), pile.c) $(OUT)carte.o $(HEADER)pile.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)joueur.o: $(addprefix $(SRCDIR), joueur.c) $(OUT)pile.o $(HEADER)joueur.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)csvloader.o: $(addprefix $(SRCDIR), csvloader.c) $(HEADER)csvloader.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)play.o:$(addprefix $(SRCDIR), play.c) $(HEADER)play.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OUT)*.o $(OUT)$(PROGNAME)
	

run:	$(OUT)$(PROGNAME)
	$(OUT)$(PROGNAME)

