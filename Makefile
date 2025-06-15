TARGET = CollectorsHub

SRC = main.c session.c system_admin.c system.c ascii_graphics.c menu.c users.c user.c collections.c collection.c products.c product.c

CC = gcc

CFLAGS = -Wall -g

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
