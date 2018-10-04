#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void *inc_x(void* x) {
	int* x_ptr = (int*) x;
	
	for(int i=0;i<100;i++) {
		*x_ptr = *x_ptr + 1;
	}
	return NULL;
}

int main(int argc, char **argv) {
	pthread_t inc_thread;
	pthread_t inc_thread_2;
	int x=0;

	pthread_create(&inc_thread, NULL,inc_x, &x);
	pthread_create(&inc_thread_2, NULL,inc_x, &x);

	if(pthread_join(inc_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}
	printf("x: %d\n", x);
}