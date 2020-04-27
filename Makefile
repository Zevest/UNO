CC=gcc
HEADER= include/
CFLAGS=#-I $(HEADER)
OUT= build/
SRC= main.c pile.c carte.c joueur.c play.c
OBJ=$(SRC:.c=.o)
PROGNAME=app
RM=rm


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

$(OUT)$(PROGNAME): main.c $(OUT)csvloader.o $(OUT)play.o $(OUT)pile.o $(OUT)joueur.o $(OUT)carte.o 
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)carte.o: carte.c $(HEADER)carte.h 
	$(CC) $(CFLAGS) -c carte.c -o $@

$(OUT)pile.o: pile.c $(OUT)carte.o $(HEADER)pile.h 
	$(CC) $(CFLAGS) -c pile.c -o $@

$(OUT)joueur.o: joueur.c $(OUT)pile.o $(HEADER)joueur.h 
	$(CC) $(CFLAGS) -c joueur.c -o $@

$(OUT)csvloader.o: csvloader.c $(HEADER)csvloader.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)play.o: play.c $(OUT)joueur.o $(OUT) csvloader.o $(HEADER)play.h 
	$(CC) $(CFLAGS) -c play.c -o $@


#$(OUT)%.o: %.c $(HEADER)%.h
#	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OUT)*.o

cleanexe:
	$(RM) $(OUT)$(PROGNAME)

