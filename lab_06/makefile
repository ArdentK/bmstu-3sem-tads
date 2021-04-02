CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func/
CFLAGS=-std=c99 -I$(INCPATH) -Wall
LFLAGS=--coverage
SRCS = (SRCPATH)*.c
.PHONY: clean
.NOTPARALLEL: release debug 

release: CFLAGS=-std=c99 -I$(INCPATH) -Wall  -o2
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
	
app.exe: $(OUTPATH)main.o $(OUTPATH)io.o $(OUTPATH)time_lapse.o $(OUTPATH)tree.o $(OUTPATH)hash.o $(OUTPATH)file.o $(INCPATH)defines.h
	$(CC) $(LFLAGS) -o app.exe $(OUTPATH)main.o $(OUTPATH)io.o $(OUTPATH)time_lapse.o $(OUTPATH)tree.o $(OUTPATH)file.o $(OUTPATH)hash.o 

$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c -o$(OUTPATH)main.o 

$(OUTPATH)io.o: $(SRCPATH)io.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)io.c -o$(OUTPATH)io.o 

$(OUTPATH)time_lapse.o: $(SRCPATH)time_lapse.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)time_lapse.c -o$(OUTPATH)time_lapse.o 

$(OUTPATH)tree.o: $(SRCPATH)tree.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)tree.c -o$(OUTPATH)tree.o 

$(OUTPATH)hash.o: $(SRCPATH)hash.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)hash.c -o$(OUTPATH)hash.o 

$(OUTPATH)file.o: $(SRCPATH)file.c $(INCPATH)defines.h
	$(CC) $(CFLAGS) -c $(SRCPATH)file.c -o$(OUTPATH)file.o 

clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)*.lastbuildstate