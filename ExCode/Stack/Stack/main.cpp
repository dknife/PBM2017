#include "Stack.h"
#include <iostream>

int main(int argc, char **argv) {
	Queue myQ;

	myQ.add(1);
	myQ.add(2);
	myQ.add(3);
	myQ.add(4);
	myQ.display();
	myQ.add(5);
	myQ.display();

	int v;
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);
	v = myQ.remove();
	printf("removed %d\n", v);

	return 0;
}