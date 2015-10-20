CC = g++

CFLAGS = -g -Wall

TARGET = spinner

LIBS = -framework OpenGL -framework GLUT

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)

