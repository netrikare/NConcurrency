TARGET=libNConcurrency.so
CC=g++
CFLAGS=-Wall -I. -fPIC -O3 -ggdb3
LINK=g++ -o
LDFLAGS=-shared -lpthread
SRCDIR=src
OBJDIR=obj

SRC=$(wildcard $(SRCDIR)/*.cpp)
INC=$(wildcard $(SRCDIR)/*.h)
OBJ=$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean
all: $(TARGET)

clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $@ $(LDFLAGS) $(OBJ)
	

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

