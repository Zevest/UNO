CC=gcc
HEADER=include/
CFLAGS=-Wall -I$(HEADER)
OUT= build/
SRCDIR=src/
SRC=util.c pile.c carte.c joueur.c play.c main.c csvloader.c
TESTFOLDER=test/
TESTCSVFILE=res/test.csv
TRACEFILE=trace_execution.txt
ECHO=echo
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

$(OUT)pile.test: $(TESTFOLDER)pile_test.c $(OUT)pile.o $(OUT)carte.o $(OUT)util.o
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)play.test: $(TESTFOLDER)play_test.c $(OUT)pile.o $(OUT)carte.o $(OUT)play.o $(OUT)util.o
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)csvloader.test: $(TESTFOLDER)csvloader_test.c $(OUT)csvloader.o $(OUT)util.o
	$(CC) $(CFLAGS) $^ -o $@


test: $(OUT)pile.test $(OUT)play.test $(OUT)csvloader.test
	$(OUT)pile.test > $(TESTFOLDER)$(TRACEFILE)
	$(OUT)play.test >> $(TESTFOLDER)$(TRACEFILE)
	($(OUT)csvloader.test $(TESTCSVFILE)) 1>> $(TESTFOLDER)$(TRACEFILE) 2>> $(TESTFOLDER)$(TRACEFILE)
	$(ECHO) "TOUS EST OK" >> $(TESTFOLDER)$(TRACEFILE)
	$(ECHO) "Fin des test"
	


clean:
	$(RM) $(OUT)*.o $(OUT)$(PROGNAME) $(OUT)*.test
	

run:	$(OUT)$(PROGNAME)
	$(OUT)$(PROGNAME)

