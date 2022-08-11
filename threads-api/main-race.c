#include <stdio.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    Pthread_mutex_lock(&mlock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&mlock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_mutex_lock(&mlock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&mlock);
    Pthread_join(p, NULL);
    return 0;
}
