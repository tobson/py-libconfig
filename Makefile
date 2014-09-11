CFLAGS += -Wall -std=c99

LIBCONFIG = $(HOME)/macports
CFLAGS += -I$(LIBCONFIG)/include
LDFLAGS += -L$(LIBCONFIG)/lib -lconfig

main: read_config.o

clean:
	rm -f *.o main
