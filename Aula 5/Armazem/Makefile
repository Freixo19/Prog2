teste_armazem: teste_armazem.o pilha_contentores.o fila_contentores.o contentor.o armazem.o
	clang teste_armazem.o pilha_contentores.o fila_contentores.o contentor.o armazem.o -o teste_armazem

pilha_contentores.o: pilha_contentores.c pilha_contentores.h
	clang -c pilha_contentores.c

fila_contentores.o: fila_contentores.c fila_contentores.h
	clang -c fila_contentores.c

contentor.o: contentor.c contentor.h
	clang -c contentor.c

armazem.o: armazem.c armazem.h
	clang -c armazem.c

teste_armazem.o: teste_armazem.c pilha_contentores.h fila_contentores.h contentor.h armazem.h
	clang -c teste_armazem.c

clean:
	rm teste_armazem teste_armazem.o pilha_contentores.o fila_contentores.o contentor.o armazem.o