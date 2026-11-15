#include <pthread.h>
#include <stdio.h>

void* foo() {
    printf("Created a new thread");
    return NULL;
}
int main() {
    pthread_t thread1;
    
    // Creating a new thread
    pthread_create(&thread1, NULL, foo, NULL);
    
    // pthread_join(thread1, NULL);
    return 0;
}