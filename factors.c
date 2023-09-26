#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FACTORS 25

void *findFactors(void *arg) {
  int n = *(int *)arg;
  int factors[MAX_FACTORS];
  int i = 2, count = 0;
  while (n > 1) {
    if (n % i == 0) {
      factors[count++] = i;
      n /= i;
    } else {
      i++;
    }
  }
  factors[count] = -1;
  int *result = malloc((count + 1) * sizeof(int));
  for (int j = 0; j <= count; j++) {
    result[j] = factors[j];
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("PLEASE ENTER NUMBERS TO FACTOR\n");
  }

  pthread_t threads[argc - 1];
  int numbers[argc - 1];

  for (int i = 1; i < argc; i++) {
    numbers[i - 1] = atoi(argv[i]);
    pthread_create(&threads[i - 1], NULL, findFactors, &numbers[i - 1]);
  }

  for (int i = 0; i < argc - 1; i++) {
    int *factors;
    pthread_join(threads[i], (void **)&factors);
    printf("%d:", numbers[i]);
    for (int j = 0; factors[j] != -1; j++) {
      printf(" %d", factors[j]);
    }
    printf("\n");
    free(factors);
  }

  return 0;
}
