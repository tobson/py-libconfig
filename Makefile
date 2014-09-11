CFLAGS += -Wall -std=c99
CFLAGS += -MMD

objects := $(patsubst %.c, %.o, $(wildcard *.c libconfig/*.c))

main: $(objects)

deps := $(objects:.o=.d)

-include $(deps)

clean:
	rm -f main *.o libconfig/*.o
