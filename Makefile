all: midi1tx

midi1tx: midi1_tx.c midi1_tx.h
	cc -c midi1_tx.c -o midi1_tx.o

clean:
	rm -rf *.o