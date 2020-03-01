#Makefile for oko-t

PROJECT= oko-t
SOURCES= glx_base.c gui.c helper.c video.c mesh.c 3ds.c audio.c fft.c camera.c db.c song.c interface.c main.c
OBJECTS= glx_base.o gui.o helper.o video.o mesh.o 3ds.o audio.o fft.o camera.o db.o song.o interface.o main.o
LFLAGS= -lpthread -lc -L/usr/X11R6/lib -lm -lGLU -lGL -lXxf86vm -lasound -laviplay
INCLUDES= #-I/usr/include/
CC= g++

	
$(PROJECT): $(OBJECTS)
	$(CC) -O2 -g $(OBJECTS) $(LFLAGS) -o $(PROJECT)
	@echo Compilation Complete

$(OBJECTS): $(SOURCES)
	@echo Compiling Sources
	$(CC) -O2 -Wall -ansi -pedantic -g -c $(INCLUDES) $(SOURCES)

clean:
	@echo Deleting up $(OBJECTS) $(PROJECT)
	rm -f *.o;rm $(PROJECT)

install:
	@echo TODO
