/* Producer Consumer Problem */
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int * buf, count = -1, in = -1, out = -1, buf_size, n_prod, n_cons;
pthread_t *producers, *consumers;

void print_buffer(){
	printf("Buffer (count = %d): ", count);
	for(int i = 0; i < buf_size; i++)
		printf("\t%d", buf[i]);
	printf("\n");
}

int produce(pthread_t self){
	int i = 0;
	int item = 1 + rand() % 10;
	while(!pthread_equal(producers[i], self) && i < n_prod)
		i++;
	printf("Producer %d produced item: %d\n", i + 1, item);
	return item;
}

void consume(int item, pthread_t self){
	int i = 0;
	while(!pthread_equal(consumers[i], self) && i < n_cons)
		i++;
	printf("Consumer %d consumed item: %d\n", i + 1, item);
	buf[out] = -1;
	print_buffer();
}

void * producer(){
	int itemP;
	while(1){
		itemP = produce(pthread_self());
		while(count == buf_size){}
		buf[in] = itemP;
		in = (in + 1) % buf_size;
		count++;
		sleep(1);
	}
	return NULL;
}

void * consumer(){
	int itemC;
	while(1){
		while(count == 0){}
		itemC = buf[out];
		consume(itemC, pthread_self());
		out = (out + 1) % buf_size;
		count--;
		sleep(1);
	}
	return NULL;
}

int main(){
	printf("Enter number of Producers: ");
	scanf("%d", &n_prod);
	printf("Enter number of Consumers: ");
	scanf("%d", &n_cons);
	printf("Enter size of buffer: ");
	scanf("%d", &buf_size);
	producers = (pthread_t *)malloc(n_prod * sizeof(pthread_t));
	consumers = (pthread_t *)malloc(n_cons * sizeof(pthread_t));
	buf = (int *)malloc(buf_size * sizeof(int));
	for(int i = 0; i < buf_size; i++)
		buf[i] = -1;
	for(int i = 0; i < n_prod; i++)
		pthread_create(&producers[i], NULL, producer, NULL);
	for(int i = 0; i < n_cons; i++)
		pthread_create(&consumers[i], NULL, consumer, NULL);
	for(int i = 0; i < n_prod; i++)
		pthread_join(producers[i], NULL);
	for(int i = 0; i < n_cons; i++)
		pthread_join(consumers[i], NULL);
	return 0;
}
*/

/* TERMINAL

cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o ProdCons.exe ./ProdCons.c
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./ProdCons.exe
Enter number of Producers: 2
Enter number of Consumers: 4
Enter size of buffer: 4
Producer 1 produced item: 4
Producer 2 produced item: 7
Consumer 1 consumed item: 4
Buffer (count = 1): 	7	-1	-1	-1
Producer 1 produced item: 8
Consumer 2 consumed item: 7
Buffer (count = 1): 	-1	8	-1	-1
Consumer 3 consumed item: 7
Buffer (count = 0): 	-1	-1	-1	-1
Consumer 4 consumed item: 7
Buffer (count = -1): 	-1	-1	-1	-1
Producer 2 produced item: 6
Consumer 1 consumed item: -1
Buffer (count = -1): 	-1	-1	6	-1
Producer 1 produced item: 4
Consumer 2 consumed item: -1
Buffer (count = -1): 	-1	-1	6	4
Consumer 3 consumed item: -1
Buffer (count = -2): 	-1	-1	6	4
Producer 2 produced item: 6
Consumer 4 consumed item: -1
Buffer (count = -2): 	6	-1	-1	4
Consumer 1 consumed item: 6
Buffer (count = -3): 	6	-1	-1	-1
Producer 1 produced item: 7
Consumer 2 consumed item: 6
Buffer (count = -3): 	-1	7	-1	-1
Consumer 3 consumed item: 7
Buffer (count = -4): 	-1	-1	-1	-1
Consumer 1 consumed item: -1
Buffer (count = -5): 	-1	-1	-1	-1
Producer 2 produced item: 3
Consumer 4 consumed item: -1
Buffer (count = -5): 	-1	-1	3	-1
^C

*/

/* Producer Consumer Problem Solved using Semaphore*/
///*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t full, empty, s;

int * buf, count = -1, in = -1, out = -1, buf_size, n_prod, n_cons;
pthread_t *producers, *consumers;

void print_buffer(){
	printf("Buffer (count = %d): ", count);
	for(int i = 0; i < buf_size; i++)
		printf("\t%d", buf[i]);
	printf("\n");
}

int produce(pthread_t self){
	int i = 0;
	int item = 1 + rand() % 10;
	while(!pthread_equal(producers[i], self) && i < n_prod)
		i++;
	printf("Producer %d produced item: %d\n", i + 1, item);
	return item;
}

void consume(int item, pthread_t self){
	int i = 0;
	while(!pthread_equal(consumers[i], self) && i < n_cons)
		i++;
	printf("Consumer %d consumed item: %d\n", i + 1, item);
	buf[out] = -1;
	print_buffer();
}

void * producer(){
	int itemP;
	while(1){
		sem_wait(&empty);
		sem_wait(&s);
		itemP = produce(pthread_self());
		// while(count == buf_size){}
		buf[in] = itemP;
		in = (in + 1) % buf_size;
		count++;
		sem_post(&s);
		sem_post(&full);
		sleep(1);
	}
	return NULL;
}

void * consumer(){
	int itemC;
	while(1){
		// while(count == 0){}
		sem_wait(&full);
		sem_wait(&s);
		itemC = buf[out];
		consume(itemC, pthread_self());
		out = (out + 1) % buf_size;
		sem_post(&s);
		sem_post(&empty);
		count--;
		sleep(1);
	}
	return NULL;
}

int main(){
	printf("Enter number of Producers: ");
	scanf("%d", &n_prod);
	printf("Enter number of Consumers: ");
	scanf("%d", &n_cons);
	printf("Enter size of buffer: ");
	scanf("%d", &buf_size);
	producers = (pthread_t *)malloc(n_prod * sizeof(pthread_t));
	consumers = (pthread_t *)malloc(n_cons * sizeof(pthread_t));
	buf = (int *)malloc(buf_size * sizeof(int));
	for(int i = 0; i < buf_size; i++)
		buf[i] = -1;
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, buf_size);
	sem_init(&s, 0, 1);
	for(int i = 0; i < n_prod; i++)
		pthread_create(&producers[i], NULL, producer, NULL);
	for(int i = 0; i < n_cons; i++)
		pthread_create(&consumers[i], NULL, consumer, NULL);
	for(int i = 0; i < n_prod; i++)
		pthread_join(producers[i], NULL);
	for(int i = 0; i < n_cons; i++)
		pthread_join(consumers[i], NULL);
	sem_destroy(&full);
	sem_destroy(&empty);
	sem_destroy(&s);
	return 0;
}
//*/

/* TERMINAL

cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o ProdCons.exe ./ProdCons.c
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./ProdCons.exe
Enter number of Producers: 2
Enter number of Consumers: 4
Enter size of buffer: 4
Producer 1 produced item: 4
Producer 2 produced item: 7
Consumer 1 consumed item: 4
Buffer (count = 1): 	7	-1	-1	-1
Consumer 2 consumed item: 7
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 8
Producer 2 produced item: 6
Consumer 3 consumed item: 8
Buffer (count = 1): 	-1	-1	6	-1
Consumer 4 consumed item: 6
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 4
Producer 2 produced item: 6
Consumer 1 consumed item: 4
Buffer (count = 1): 	6	-1	-1	-1
Consumer 3 consumed item: 6
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 7
Producer 2 produced item: 3
Consumer 2 consumed item: 7
Buffer (count = 1): 	-1	-1	3	-1
Consumer 1 consumed item: 3
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 10
Producer 2 produced item: 2
Consumer 4 consumed item: 10
Buffer (count = 1): 	2	-1	-1	-1
Consumer 1 consumed item: 2
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 3
Producer 2 produced item: 8
Consumer 2 consumed item: 3
Buffer (count = 1): 	-1	-1	8	-1
Consumer 4 consumed item: 8
Buffer (count = 0): 	-1	-1	-1	-1
Producer 1 produced item: 1
Producer 2 produced item: 10
Consumer 2 consumed item: 1
Buffer (count = 1): 	10	-1	-1	-1
Consumer 3 consumed item: 10
Buffer (count = 0): 	-1	-1	-1	-1
^C

*/
