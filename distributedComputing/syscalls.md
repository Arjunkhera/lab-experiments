[File I/O](https://www.learncpp.com/cpp-tutorial/186-basic-file-io/)

### Semaphores

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg)
```

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semop(int semid, struct sembuf *semops, size_t nsemops)

struct sembuf {
   unsigned short sem_num; /* Semaphore set num */
   short sem_op; /* Semaphore operation */
   short sem_flg; /* Operation flags, IPC_NOWAIT, SEM_UNDO */
};

```

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semctl(int semid, int semnum, int cmd, …)

union semun {
   int val; /* val for SETVAL */
   struct semid_ds *buf; /* Buffer for IPC_STAT and IPC_SET */
   unsigned short *array; /* Buffer for GETALL and SETALL */
   struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
};

struct semid_ds {
   struct ipc_perm sem_perm; /* Permissions */
   time_t sem_otime; /* Last semop time */
   time_t sem_ctime; /* Last change time */
   unsigned long sem_nsems; /* Number of semaphores in the set */
};
```

```

### Shared Memory

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg)
```

```c
#include <sys/types.h>
#include <sys/shm.h>

void * shmat(int shmid, const void *shmaddr, int shmflg)
```

The second argument, shmaddr, is to specify the attaching address. If shmaddr is NULL, the system by default chooses the suitable address to attach the segment.   

```c
#include <sys/types.h>
#include <sys/shm.h>

int shmdt(const void *shmaddr)
```

```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmctl(int shmid, int cmd, struct shmid_ds *buf)
```

To remove a shared memory segment, use the following code:

```c
shmctl (shm_id, IPC_RMID, NULL)
```
