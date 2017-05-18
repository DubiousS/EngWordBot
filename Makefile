TARGET := bin/bot_telegram
TARGET_TEST := bin/bot_test
CC := gcc
CFLAGS :=  -Wall -Werror -c
LFLAGS := -I thirdparty -I src -c

 
all: $(TARGET) $(TARGET_TEST)

$(TARGET): build/src/main.o build/src/server.o build/src/output.o build/src/language.o
		$(CC) build/src/main.o build/src/server.o build/src/output.o build/src/language.o -o $@ -lssl -lcrypto

$(TARGET_TEST): build/test/function_test.o build/test/main.o build/src/language.o build/src/server.o
		$(CC) build/test/function_test.o build/test/main.o build/src/language.o build/src/server.o -o $@ -lssl -lcrypto


build/src/main.o: src/main.c
		$(CC) $(CFLAGS) src/main.c -o $@ 

build/src/server.o: src/server.c
		$(CC) $(CFLAGS) src/server.c -o $@ 

build/src/output.o: src/output.c
		$(CC) $(CFLAGS) src/output.c -o $@

build/src/language.o: src/language.c
		$(CC) $(CFLAGS) src/language.c -o $@


build/test/function_test.o: test/function_test.c       
		$(CC) $(LFLAGS) test/function_test.c -o $@ 

build/test/main.o: test/main.c 
		$(CC) -I thirdparty -c test/main.c -o $@


.PHONY: all clean

clean:	
	rm -f build/src/*.o
	rm -f build/test/*.o
	rm -f bin/*