TARGET = checksum
CFLAGS = -Wall -fsanitize=address -O2

all:$(TARGET)

checksum:checksum.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)
