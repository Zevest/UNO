CC=gcc
HEADER=include/
CFLAGS=-Wall -I$(HEADER)
OUT= build/
SRCDIR=src/
SRC=util.c pile.c carte.c joueur.c play.c main.c csvloader.c
TESTFOLDER=test/

OBJ=$(SRC:.c=.o)
PROGNAME=UNO.exe
RM=rm -rf

all: $(OUT)$(PROGNAME)



$(OUT)$(PROGNAME): $(addprefix $(OUT), $(OBJ))
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)main.o:	$(addprefix $(SRCDIR), main.c) $(OUT)util.o
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)carte.o: $(addprefix $(SRCDIR), carte.c) $(HEADER)carte.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)pile.o: $(addprefix $(SRCDIR), pile.c) $(OUT)util.o $(OUT)carte.o $(HEADER)pile.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)joueur.o: $(addprefix $(SRCDIR), joueur.c) $(OUT)pile.o $(HEADER)joueur.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)csvloader.o: $(addprefix $(SRCDIR), csvloader.c) $(OUT)util.o $(HEADER)csvloader.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)play.o:$(addprefix $(SRCDIR), play.c) $(OUT)util.o $(HEADER)play.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)util.o:$(addprefix $(SRCDIR), util.c) $(HEADER)util.h
	$(CC) $(CFLAGS) -c $< -o $@

testpile: $(TESTFOLDER)pile_test.c $(OUT)pile.o $(OUT)carte.o $(OUT)util.o
	$(CC) $(CFLAGS) $^ -o $(OUT)$@

testplay: $(TESTFOLDER)play_test.c $(OUT)pile.o $(OUT)carte.o $(OUT)play.o $(OUT)util.o
	$(CC) $(CFLAGS) $^ -o $(OUT)$@


clean:
	$(RM) $(OUT)*.o $(OUT)$(PROGNAME)
	

run:	$(OUT)$(PROGNAME)
	$(OUT)$(PROGNAME)

