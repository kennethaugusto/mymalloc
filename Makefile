CC = gcc
CFLAGS = -g -Wall

all: memgrind Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 Test11 Test12 Test13 Test14

mymalloc: mymalloc.c
	$(CC) $(CFLAGS) -o mm mymalloc.c

memgrind: mymalloc.c memgrind.c
	$(CC) $(CFLAGS) -c mymalloc.c
	$(CC) $(CFLAGS) -o memgrind memgrind.c mymalloc.o

Test1: Test1.c mymalloc.c
	$(CC) $(CFLAGS) -o Test1 Test1.c mymalloc.c -I.

Test2: Test2.c mymalloc.c
	$(CC) $(CFLAGS) -o Test2 Test2.c mymalloc.c -I.

Test3: Test3.c mymalloc.c
	$(CC) $(CFLAGS) -o Test3 Test3.c mymalloc.c -I.

Test4: Test4.c mymalloc.c
	$(CC) $(CFLAGS) -o Test4 Test4.c mymalloc.c -I.

Test5: Test5.c mymalloc.c
	$(CC) $(CFLAGS) -o Test5 Test5.c mymalloc.c -I.

Test6: Test6.c mymalloc.c
	$(CC) $(CFLAGS) -o Test6 Test6.c mymalloc.c -I.

Test7: Test7.c mymalloc.c
	$(CC) $(CFLAGS) -o Test7 Test7.c mymalloc.c -I.

Test8: Test8.c mymalloc.c
	$(CC) $(CFLAGS) -o Test8 Test8.c mymalloc.c -I.

Test9: Test9.c mymalloc.c
	$(CC) $(CFLAGS) -o Test9 Test9.c mymalloc.c -I.

Test10: Test10.c mymalloc.c
	$(CC) $(CFLAGS) -o Test10 Test10.c mymalloc.c -I.

Test11: Test11.c mymalloc.c
	$(CC) $(CFLAGS) -o Test11 Test11.c mymalloc.c -I.

Test12: Test12.c mymalloc.c
	$(CC) $(CFLAGS) -o Test12 Test12.c mymalloc.c -I.

Test13: Test13.c mymalloc.c
	$(CC) $(CFLAGS) -o Test13 Test13.c mymalloc.c -I.

Test14: Test14.c mymalloc.c
	$(CC) $(CFLAGS) -o Test14 Test14.c mymalloc.c -I.

clean:
	rm -f mymalloc.o memgrind Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 Test11 Test12 Test13 Test14
