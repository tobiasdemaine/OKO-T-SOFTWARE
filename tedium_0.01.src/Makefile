MAIN=oko-t

CC=g++

CFLAGS= -DUNIX -g -Wall

LFLAGS= -lCgGL -lCg -lpthread -lc -lftgl -L/usr/X11R6/lib -lm -lGLU -lGL -lXxf86vm -lasound -laviplay 

INCLUDES= -I/usr/include/freetype2

SRCS =  oko-t.cpp 3ds.cpp fft.cpp

OBJS = $(SRCS:.cpp=.o)

$(MAIN):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN) $(LFLAGS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o *~ $(MAIN)
# DO NOT DELETE
