TARGET := bin/bot_telegram
CC := gcc
CFLAGS :=  -Wall -Werror -c
LFLAGS := -I thirdparty -I src -c

 
all: $(TARGET)

$(TARGET): build/src/main.o build/src/server.o build/src/output.o build/src/language.o
		$(CC) build/src/main.o build/src/server.o build/src/output.o build/src/language.o -o $@ -lssl -lcrypto


build/src/main.o: src/main.c
		$(CC) $(CFLAGS) src/main.c -o $@ 

build/src/server.o: src/server.c
		$(CC) $(CFLAGS) src/server.c -o $@ 

build/src/output.o: src/output.c
		$(CC) $(CFLAGS) src/output.c -o $@

build/src/language.o: src/language.c
		$(CC) $(CFLAGS) src/language.c -o $@

.PHONY: all clean
clean:	
	rm -f build/src/*.o
	rm -f bin/*