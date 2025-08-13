src=$(wildcard *.c)
objs=$(patsubst %.c,%.o,$(src))
target=main

$(target):$(objs)
	gcc -o $@ $^ -L../mylib -ltest2

%.o:%.c
	gcc -c $< -I../include

.PHONY:clean
clean:
	-rm -f $(target) $(objs)
