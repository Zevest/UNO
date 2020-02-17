CC=gcc
HEADER= include/
CFLAGS=#-I $(HEADER)
OUT= build/
SRC= main.c pile.c carte.c joueur.c play.c
OBJ=$(SRC:.c=.o)
PROGNAME=app


# \
all: done clean

#done:	$(PROGNAME) \
	$(CC) $(OBJ) -o $(PROGNAME) $(CFLAGS) 
	
#$(PROGNAME):	$(OBJ) \
	$(CC) -c $(SRC) $(CFLAGS)

#all: $(PROGNAME) clean
#	$(CC) main.o $(OBJ) $(CFLAGS) -o $(PROGNAME)
	
	
#$(PROGNAME):
#	$(CC) -c main.c $(OBJ) $(CFLAGS) 
	
#pile.o: carte.o pile.c
#	$(CC) -c pile.c carte.o $(CFLAGS) 

#carte.o: carte.c
#	$(CC) -c carte.c $(CFLAGS)


all: $(OUT)$(PROGNAME)

$(OUT)$(PROGNAME): main.c $(OUT)play.o $(OUT)pile.o $(OUT)joueur.o $(OUT)carte.o
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)carte.o: carte.c $(HEADER)carte.h 
	$(CC) $(CFLAGS) -c $< -o $@
$(OUT)pile.o: pile.c $(OUT)carte.o $(HEADER)pile.h 
	$(CC) $(CFLAGS) -c pile.c $(OUT)carte.o -o $@

$(OUT)joueur.o: joueur.c $(OUT)pile.o $(HEADER)joueur.h 
	$(CC) $(CFLAGS) -c joueur.c $(OUT)pile.o -o $@
$(OUT)play.o: play.c $(OUT)pile.o $(OUT)joueur.o $(OUT)pile.o $(OUT)carte.o $(HEADER)play.h 
	$(CC) $(CFLAGS) -c play.c $(OUT)pile.o $(OUT)joueur.o $(OUT)pile.o $(OUT)carte.o -o $@

$(OUT)%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OUT)*.o

cleanexe:
	rm $(OUT)$(PROGNAME)

