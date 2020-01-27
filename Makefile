CC=gcc
CFLAGS=
SRC= main.c pile.c carte.c
OBJ=$(SRC:.c=.o)
PROGNAME=app



all: done clean

done:	$(PROGNAME)
	$(CC) $(OBJ) -o $(PROGNAME) $(CFLAGS) 
	
$(PROGNAME):	$(OBJ)
	$(CC) -c $(SRC) $(CFLAGS)

#all: $(PROGNAME) clean
#	$(CC) main.o $(OBJ) $(CFLAGS) -o $(PROGNAME)
	
	
#$(PROGNAME):
#	$(CC) -c main.c $(OBJ) $(CFLAGS) 
	
#pile.o: carte.o pile.c
#	$(CC) -c pile.c carte.o $(CFLAGS) 

#carte.o: carte.c
#	$(CC) -c carte.c $(CFLAGS)

clean:
	rm ./*.o

