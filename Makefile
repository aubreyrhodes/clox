src = $(wildcard *.c)
obj = $(src:.c=.o)

clox: $(obj)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	@rm -f *.o clox
