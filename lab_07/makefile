CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func/
CFLAGS=-std=c99 -I$(INCPATH) -Wall
LFLAGS=--coverage
.PHONY: clean
.NOTPARALLEL: release debug 

release: CFLAGS=-std=c99 -I$(INCPATH) -Wall -o2
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
	
app.exe: $(OUTPATH)io.o $(OUTPATH)main.o $(OUTPATH)graph_matrix_func.o $(INCPATH)defines.h
	$(CC) $(LFLAGS) -o app.exe  $(OUTPATH)io.o $(OUTPATH)main.o $(OUTPATH)graph_matrix_func.o

$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c -o$(OUTPATH)main.o 

$(OUTPATH)io.o: $(SRCPATH)io.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)io.c -o$(OUTPATH)io.o 

$(OUTPATH)graph_matrix_func.o: $(SRCPATH)graph_matrix_func.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)graph_matrix_func.c -o$(OUTPATH)graph_matrix_func.o 

clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)*.lastbuildstate