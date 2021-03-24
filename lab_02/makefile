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
	
app.exe: $(OUTPATH)in_out.o $(OUTPATH)delete.o $(OUTPATH)sort.o $(OUTPATH)main.o $(OUTPATH)time_lapse.o
	$(CC) $(LFLAGS) -o app.exe  $(OUTPATH)in_out.o $(OUTPATH)sort.o $(OUTPATH)delete.o $(OUTPATH)main.o $(OUTPATH)time_lapse.o

$(OUTPATH)main.o: $(SRCPATH)main.c 
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c -o$(OUTPATH)main.o 

$(OUTPATH)in_out.o: $(SRCPATH)in_out.c
	$(CC) $(CFLAGS) -c $(SRCPATH)in_out.c -o$(OUTPATH)in_out.o 
	
$(OUTPATH)sort.o: $(SRCPATH)sort.c
	$(CC) $(CFLAGS) -c $(SRCPATH)sort.c -o$(OUTPATH)sort.o 

$(OUTPATH)delete.o: $(SRCPATH)delete.c
	$(CC) $(CFLAGS) -c $(SRCPATH)delete.c -o$(OUTPATH)delete.o 

$(OUTPATH)time_lapse.o: $(SRCPATH)time_lapse.c
	$(CC) $(CFLAGS) -c $(SRCPATH)time_lapse.c -o$(OUTPATH)time_lapse.o

clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	rm -fv $(OUTPATH)*.lastbuildstate