CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func/
CFLAGS=-std=c99 --coverage -I$(INCPATH) -Wall -Wpedantic -Werror -Wextra
LFLAGS=--coverage
.PHONY: clean
.NOTPARALLEL: release debug 

release: CFLAGS=-std=c99 -I$(INCPATH) -o2
release: LFLAGS=-o2
release: $(OUTPATH)release.lastbuildstate app.exe

debug: CFLAGS=-std=c99 -I$(INCPATH) -o2
debug: LFLAGS=-o2
debug:$(OUTPATH)debug.lastbuildstate app.exe

$(OUTPATH)debug.lastbuildstate:
	rm -fv *.exe
	mkdir -p $(OUTPATH)
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)release.lastbuildstate
	touch $(OUTPATH)debug.lastbuildstate

$(OUTPATH)release.lastbuildstate:
	rm -fv *.exe
	mkdir -p $(OUTPATH)
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)debug.lastbuildstate
	touch $(OUTPATH)release.lastbuildstate
	
app.exe: $(OUTPATH)array.o $(OUTPATH)division.o $(OUTPATH)input.o $(OUTPATH)main.o
	$(CC) $(LFLAGS) -o app.exe  $(OUTPATH)array.o $(OUTPATH)division.o $(OUTPATH)input.o $(OUTPATH)main.o

$(OUTPATH)main.o: $(SRCPATH)main.c 
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c -o$(OUTPATH)main.o 

$(OUTPATH)array.o: $(SRCPATH)array.c
	$(CC) $(CFLAGS) -c $(SRCPATH)array.c -o$(OUTPATH)array.o 

$(OUTPATH)division.o: $(SRCPATH)division.c
	$(CC) $(CFLAGS) -c $(SRCPATH)division.c -o$(OUTPATH)division.o 

$(OUTPATH)input.o: $(SRCPATH)input.c
	$(CC) $(CFLAGS) -c $(SRCPATH)input.c -o$(OUTPATH)input.o 

clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)*.lastbuildstate