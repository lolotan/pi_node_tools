PROJECT = nrf
LIBNRF = libnrf
NRFSTATICLIB = $(LIBNRF).a
NODECONFIG = node_config
NODERECEIVE = node_receive
OBJECTS = $(LIBNRF)/$(NRFSTATICLIB) spi.o gpio.o timer.o

all: $(NODECONFIG) $(NODERECEIVE)

$(NODECONFIG): $(NRFSTATICLIB) $(NODECONFIG).o $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(NODECONFIG).o $(OBJECTS) -o $(NODECONFIG)
	
$(NODERECEIVE): $(NRFSTATICLIB) $(NODERECEIVE).o $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(NODERECEIVE).o $(OBJECTS) -o $(NODERECEIVE)
	
$(NRFSTATICLIB):
	$(MAKE) -C $(LIBNRF)
	
$(NODECONFIG).o: $(NODECONFIG).c
	$(CC) $(CFLAGS) -c $(NODECONFIG).c
	
$(NODERECEIVE).o: $(NODERECEIVE).c
	$(CC) $(CFLAGS) -c $(NODERECEIVE).c
	
spi.o: spi.c
	$(CC) $(CFLAGS) -c spi.c

gpio.o: gpio.c
	$(CC) $(CFLAGS) -c gpio.c
	
timer.o: timer.c
	$(CC) $(CFLAGS) -c timer.c
	
clean:
	rm -rf *.o *.a $(NODECONFIG) $(NODERECEIVE)
	 $(MAKE) -C $(LIBNRF) clean


.PHONY: $(LIBNRF)
