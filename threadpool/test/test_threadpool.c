#define THREAD 32
#define QUEUE  256

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "blogger.h"

#include "threadpool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;

void dummy_task(void *arg __attribute__((unused))) {
    usleep(10000);
    pthread_mutex_lock(&lock);
    done++;
    pthread_mutex_unlock(&lock);
}

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_INFO, argv[0]);
    threadpool_t *pool;

    pthread_mutex_init(&lock, NULL);

    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    BLOG(LOG_ERR, "Pool started with %d threads and "
            "queue size of %d", THREAD, QUEUE);

    while(threadpool_add(pool, &dummy_task, NULL, 0) == 0) {
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
    }

    BLOG(LOG_ERR, "Added %d tasks", tasks);

    while((tasks / 2) > done) {
        usleep(10000);
    }
    assert(threadpool_destroy(pool, 0) == 0);
    BLOG(LOG_INFO, "Did %d tasks", done);

    return 0;
}