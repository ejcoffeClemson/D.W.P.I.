CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=LAB10

OBJS := driver.c ppm_utils.c

all: build

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)



clean:
	rm -f $(TARGET)
	rm -rf bin

run: build
	./LAB10 median output.ppm
debug: build
	gdb --args LAB10 average output.ppm # this gdb command presets all your args for you
	# just type make debug and the 'run' in gdb will run for you
