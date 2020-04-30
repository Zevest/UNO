CC=gcc
HEADER= include/
CFLAGS=-Wall#-I $(HEADER)
OUT= build/
SRC=  pile.c carte.c joueur.c play.c main.c csvloader.c
OBJ=$(SRC:.c=.o)
PROGNAME=UNO.exe
RM=rm -rf

all: $(OUT)$(PROGNAME)


$(OUT)$(PROGNAME): $(addprefix $(OUT), $(OBJ))
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)main.o:	main.c
	$(CC) $(CFLAGS) -c main.c -o $@

$(OUT)carte.o: carte.c $(HEADER)carte.h 
	$(CC) $(CFLAGS) -c carte.c -o $@

$(OUT)pile.o: pile.c $(OUT)carte.o $(HEADER)pile.h 
	$(CC) $(CFLAGS) -c pile.c -o $@

$(OUT)joueur.o: joueur.c $(OUT)pile.o $(HEADER)joueur.h 
	$(CC) $(CFLAGS) -c joueur.c -o $@

$(OUT)csvloader.o: csvloader.c $(HEADER)csvloader.h
	$(CC) $(CFLAGS) -c csvloader.c -o $@

$(OUT)play.o: play.c $(HEADER)play.h 
	$(CC) $(CFLAGS) -c play.c -o $@

clean:
	$(RM) $(OUT)*.o $(OUT)$(PROGNAME)
	

run:	$(OUT)$(PROGNAME)
	$(OUT)$(PROGNAME)

