src=$(wildcard ./*.c)
object=$(patsubst %.c, %.o, $(src))
target=main
CC=gcc
CPPFLAGS=-I./

$(target):$(object)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -o $@ -c $< $(CPPFLAGS) 

.PHONY:clean
clean:
	-rm -f $(target) $(object)
