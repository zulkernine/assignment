#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <time.h>
#include <sys/wait.h>

#define SEMOBJ_NAME "/mutex"
#define MAX_SLEEP_SECS 3
#define BUFFER_SIZE 50

/* defining the structure for buffer */
typedef struct {
   int in, out;
   int items[BUFFER_SIZE];       // shared circular queue
   int total;
} BUFFER;

/* initialize the buffer */
void init_buffer (BUFFER *buf) {
   buf->in = 0;
   buf->out = 0;
   buf->total = 0;
   for (int i = 0; i < BUFFER_SIZE; i++)
      buf->items[i] = 0;
}

int main () {
   int p, c;
   printf ("Number of producers: ");
   scanf ("%d", &p);
   printf ("Number of consumers: ");
   scanf ("%d", &c);
   if (p & c == 0) {
      perror("No of consumers or producers cannot be zero");
      exit(1);
   }

   /* getting a new semaphore for the shared segment */
   sem_t *bufmutex = sem_open(SEMOBJ_NAME, O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, 1);
   if (bufmutex == SEM_FAILED) {
      perror("In sem_open()");
      exit(1);
   }
   /* requesting the semaphore not to be held when completely unreferenced */
   sem_unlink(SEMOBJ_NAME);

   /* requesting the shared segment */    
   BUFFER* buf = (BUFFER*)mmap(NULL, sizeof(BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
   if (buf == MAP_FAILED) {
      perror("In mmap()");
      exit(1);
   }
   fprintf(stderr, "Shared memory segment allocated correctly (%d bytes) at %p.\n", (int)sizeof(BUFFER), buf);
   
   /* initialize the buffer */
   init_buffer(buf);
   
   /* seeding the random number generator */
   // srand (time(NULL));

   /* create the producer manager process */
   int producer_manager = fork();

   if (producer_manager < 0) {
      perror("In producer manager process");
      exit(1);
   }

   else if (producer_manager == 0) {
      for (int i = 0; i < p; i++) {
         sleep(1);
         srand(time(NULL));

         // create a new producer
         int producer = fork();
         if (producer < 0) {
            perror("In producer process");
            exit(1);
         }
         else if (producer == 0) {
            // wait for the semaphore for mutual exclusive access to the buffer
            sem_wait (bufmutex);

            // wait if the buffer is full
            while ((buf->in + 1) % BUFFER_SIZE == buf->out) {
               sem_post (bufmutex);
               sleep(rand() % (MAX_SLEEP_SECS+1));
               sem_wait (bufmutex);
            }

            // produce item
            int produce = random() % 100 + 1;
            buf->items[buf->in] = produce;
            printf ("Producer %d produced %d at %d\n", getpid(), produce, buf->in);
            
            buf->in = (buf->in + 1) % BUFFER_SIZE;
            
            // release the semaphore
            sem_post (bufmutex);
            exit (0);
         }
         else {
            wait(NULL);
         }
      }
      exit(0);
   }

   /* create the consumer manager process */
   int consumer_manager = fork();

   if (consumer_manager < 0) {
      perror("In consumer manager process");
      exit(1);
   }
   else if (consumer_manager == 0) {
      for (int i = 0; i < c; i++) {
         // create a new consumer
         int consumer = fork();

         // wait for the semaphore for mutual exclusive access to the buffer
         if (consumer < 0) {
            perror("In consumer process");
            exit(1);
         }

         // wait if the buffer is empty
         else if (consumer == 0) {
            sem_wait (bufmutex);
            while (buf->in == buf->out) {
               sem_post (bufmutex);
               sleep(1);
               sem_wait (bufmutex);
            }

            // consume item
            int consume = buf->items[buf->out];
            buf -> total += consume;
            printf ("Consumer %d consumed %d at %d\n", getpid(), consume, buf->out);

            buf->out = (buf->out + 1) % BUFFER_SIZE;

            // release the semaphore
            sem_post (bufmutex);
            exit (0);
         }
         else {
            wait(NULL);
         }
      }
      exit (0);
   }
   wait (NULL);

   /* freeing the reference to the semaphore */
   sem_close(bufmutex);
   printf ("total -> %d", buf->total);

   /* release the shared memory space */
   munmap(buf, sizeof(BUFFER));
}
