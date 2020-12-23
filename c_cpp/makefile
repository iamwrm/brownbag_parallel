all: mp mt
run: mp_run mt_run

mp: mp1.c
	gcc mp1.c -Wall -o mp1
mp_run: mp
	./mp1

mt: mt1.c
	gcc mt1.c -Wall -o mt1 -pthread
mt_run: mt
	./mt1

mp2: mp2.c
	gcc mp2.c -Wall -o mp2
mp2_run: mp2
	./mp2