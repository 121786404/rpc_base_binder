CC		:= gcc
# CC		:= arm-linux-gnueabihf-gcc


APPS = service_manager test test_server

all : $(APPS)

service_manager : service_manager.o binder.o
	$(CC) -o $@ $^

test : test.o binder.o
	$(CC) -o $@ $^

test_server : test_server.o binder.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -I.. -c -o $@ $<

clean:
	rm $(APPS) -f; rm -f *.o
