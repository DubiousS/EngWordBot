FOLDER := src/
FOLDER_TWO := build/
SRC := main.c
SRCH :=  
SOURCE := $(addprefix $(FOLDER), $(SRC) $(SRCH))
SOURCE_O := $(addprefix $(FOLDER_TWO), $(SRC))
TARGET := bin/main
CC := gcc
CFLAGS := -Wall -Werror -c

 
all: $(SOURCE) $(TARGET)

$(TARGET): $(SOURCE:.c=.o)
	$(CC) $(SOURCE_O:.c=.o) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $(FOLDER_TWO)$(notdir $@)

.PHONY: all clean
clean:
	rm -f *.o
	rm -f bin/*