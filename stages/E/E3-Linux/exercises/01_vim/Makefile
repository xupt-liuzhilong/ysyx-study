CC := gcc
CFLAGS := -Wall -Wextra -g

TARGET := test
SRC := test.c

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY:run debug clean
