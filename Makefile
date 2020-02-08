a.out: sanity_client.o best_fit.o
	gcc sanity_client.o best_fit.o

sanity_client.o: sanity_client.c header.h
	gcc -c sanity_client.c

best_fit.o: best_fit.c header.h
	gcc -c best_fit.c

