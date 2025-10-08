CC = g++
PROGRAMA = main.cpp
PROCESO = ejecutable.out

CompilaryEjecutar:
	$(CC) $(PROGRAMA) -o $(PROCESO)
	./$(PROCESO)
	rm $(PROCESO)
clean:
	rm $(PROCESO)
