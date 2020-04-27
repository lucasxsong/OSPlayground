#include <iostream>
#include <pthread.h>
#define MAX 600000 
#define MAX_THREAD 6 

using namespace std;

long a[MAX];
int sum[] = {0};
int counter = 0;

void* sum_array(void* arg) {
    int thread_part = counter++;

    for (int i = thread_part * (MAX/MAX_THREAD); i < (thread_part + 1) * MAX/MAX_THREAD; ++i) {
        sum[thread_part] += a[i];
    }
}

int main() {
    pthread_t threads[2];

    for (int i = 0; i < MAX; ++i) {
        a[i] = i * i;
    }
    for(int i = 0; i < MAX_THREAD; ++i) {
      pthread_create(&threads[i], NULL, sum_array, (void*) NULL);
    }

     for(int i = 0; i < MAX_THREAD; ++i) {
      pthread_join(threads[i], NULL);
    }
    
    int sigma = 0;
    for(int i = 0; i < MAX_THREAD; ++i) {
      sigma+= sum[i];
    }
    
    cout << "sum is " << sigma << endl;

    return 0;

  }
