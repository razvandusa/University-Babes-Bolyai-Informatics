/* Sa se scrie un program C care :
 *  - va citi de la tastatura un numar natural N
 *  - va citi N numere intregi din fisierul binar file.txt si le va stoca intr-o variabila globala
 *  - va crea, apoi, un numar potrivit de thread-uri care vor procesa numerele intregi citite anterior din fisier si care
 *  - vor determina numarul de aparitii a2, a3, a5, ..., a97 ale fiecarui numar intreg PRIM din intervalul (0, 100]
 *  - vor calcula M = media_aritmetica(a2, a3, ..., a97);
 *  - vor determina si afisa toate numerele prime al caror numar de aparitii este cel mai apropiat de media aritmetica M calculata anterior
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int* numbers_array;
int frequency[101];
int mean_value = 0;
int prime_count = 0;
int closest_distance = 1000000;
int closest_primes[101];
pthread_mutex_t mutex;

void* count_frequency(void* arg) {
    int index = *(int*)arg;
    if (numbers_array[index] < 100) {
        pthread_mutex_lock(&mutex);
        frequency[numbers_array[index]]++;
        pthread_mutex_unlock(&mutex);
    }
    free(arg);
    return NULL;
}

void* compute_weighted_mean(void* arg) {
    int prime_number = *(int*)arg;
    if (prime_number < 100) {
        pthread_mutex_lock(&mutex);
        mean_value += frequency[prime_number] * prime_number;
        prime_count++;
        pthread_mutex_unlock(&mutex);
    }
    free(arg);
    return NULL;
}

void* find_closest_to_mean(void* arg) {
    int prime_number = *(int*)arg;
    if (prime_number < 100) {
        pthread_mutex_lock(&mutex);
        int distance = abs(mean_value - frequency[prime_number]);
        if (distance < closest_distance) {
            closest_distance = distance;
            prime_count = 0;
            closest_primes[prime_count] = prime_number;
        } else if (distance == closest_distance) {
            prime_count++;
            closest_primes[prime_count] = prime_number;
        }
        pthread_mutex_unlock(&mutex);
    }
    free(arg);
    return NULL;
}

int is_prime(int n) {
	if (n < 2) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n % 2 == 0) {
		return 0;
	}
	for (int d = 3; d * d <= n; d += 2) {
		if (n % d == 0) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Trebuie sa fie pasat fisierul ca si argument!\n");
		return 0;
	}
	FILE* descriptor = fopen(argv[1],"r");
        if (descriptor == NULL) {
                printf("Fisierul nu s-a putut deschide!\n");
                return 0;
        }

	int N;
	printf("Scrie un numar n : ");
	if (scanf("%d", &N) == 0) {
		printf("Numarul citit de la tastatura trebuie sa fie format doar din cifre!\n");
		return 0;
	}
	if (N < 0) {
		printf("Numarul citit de la tastatura trebuie sa fie pozitiv!\n");
		return 0;
	}

	numbers_array = (int *)malloc(sizeof(int) * N);
	if (numbers_array == NULL) {
		printf("Alocarea de memorie a esuat!\n");
		return 0;
	}

	for (int i = 0; i < N; i++) {
		if (fscanf(descriptor,"%d",&numbers_array[i]) == 0) {
			printf("Nu se poate citi a %d-a valoarea din fisier!", i);
			fclose(descriptor);
			return 0;
		}
	}
	fclose(descriptor);

	pthread_mutex_init(&mutex, NULL);
	pthread_t t[N];
	for (int i = 0; i < N; i++) {
		int* p = (int *)malloc(sizeof(int));
		*p = i;
		pthread_create(&t[i], NULL, count_frequency, p);
	}

	for (int i = 0; i < N; i++) {
		pthread_join(t[i], NULL);
	}

	for (int i = 0; i < N; i++) {
		if (is_prime(i)) {
			int* p = (int *)malloc(sizeof(int));
			*p = i;
			pthread_create(&t[i], NULL, compute_weighted_mean, p);
		}
	}

	for (int i = 0; i < N; i++) {
		if (is_prime(i)) {
			pthread_join(t[i], NULL);
		}
	}

	for (int i = 0; i < N; i++) {
		if (is_prime(i)) {
			printf("Numarul de aparitii a numarului %d este %d\n", i, frequency[i]);
		}
	}

	printf("Media aritmetica este : %d\n", mean_value/prime_count);

	prime_count = 0;
	for (int i = 0; i < N; i++) {
		if (is_prime(i)) {
			int* p = malloc(sizeof(int));
			*p = i;
			pthread_create(&t[i], NULL, find_closest_to_mean, p);
		}
	}

	for (int i = 0; i < N; i++) {
		if (is_prime(i)) {
			pthread_join(t[i], NULL);
		}
	}

	for (int i = 0; i <= prime_count; i++) {
		printf("Cel mai apropiat numar de media aritmetica este %d\n", closest_primes[i]);
	}
	pthread_mutex_destroy(&mutex);
	free(numbers_array);
	return 0;
}