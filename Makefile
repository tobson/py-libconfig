CFLAGS = -Wall -std=c99 -I$(HOME)/macports/include
LDFLAGS = -L$(HOME)/macports/lib -lconfig

main: read_config.o

clean:
	rm -f *.o main
