CC = g++
CFLAGS = -O2
BUILDDIR = ./build
TARGET = $(BUILDDIR)/main.out

all: clean $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) $^

clean:  
	rm -f $(TARGET)  

run: $(TARGET)  
	$(TARGET)