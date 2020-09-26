SRC = $(wildcard *.c)
ELF = $(SRC:%.c=%)

#CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

LDFLAGS += -lm

all:$(ELF)

$(ELF):%:%.c
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) $(ELF) *.txt
