CC		:= gcc
# CC		:= arm-linux-gnueabihf-gcc


APPS = test

all : $(APPS)


test : cal.o binder.o test.o
	$(CC) -o $@ $^


%.o : %.c
	$(CC) -I.. -c -o $@ $<

clean:
	rm $(APPS) -f; rm -f *.o
