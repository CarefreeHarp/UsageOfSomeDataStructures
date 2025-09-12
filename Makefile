CC = g++
PROGRAMA = main.cpp
PROCESO = ejecutable.out


all:
	rm $(PROCESO)
	$(CC) $(PROGRAMA) -o $(PROCESO)
	./$(PROCESO)