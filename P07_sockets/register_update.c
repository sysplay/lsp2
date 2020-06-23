#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#include "sem.h"
#include "em_registers.h"

#define KEY 0x12345 // Would retrieve the same if not detached

#define max(a, b) (a > b)? a: b
#define MAX_VOLTAGE 440
#define MIN_VOLTAGE 420
#define MIN_CURRENT 50
#define MAX_CURRENT 70
#define MAX_KW      100
#define MIN_KW      80
#define VOLT_TH     445
#define MAX_FREQ    62
#define MIN_FREQ    45

#define MAX_SIZE    4

static pthread_mutex_t mutex;
static pthread_mutex_t mutex_max;
static pthread_cond_t count_threshold_cv;
static sem_t sem;
static int count = 0, i_avg[MAX_SIZE], v_avg[MAX_SIZE];

void *calc_avg_max(void *arg)
{
    int sumi = 0, sumv = 0, i;
    struct em_registers *reg;

    if (arg == NULL)
    {
        printf("Invalid arg\n");
        return NULL;
    }
    reg = arg;

    while (1)
    {
        // TODO 17: Take the appropriate lock to safely read max registers
        // TODO 18: Wait for the conditional signal for calc_max thread
        for (i = 0; i < MAX_SIZE; i++)
        {
            sumi += i_avg[i];
            sumv += v_avg[i];
        }
        count = 0;

        // TODO 19: Take the appropriate lock to update the avg_max registers
        reg->i_avg_max = sumi / MAX_SIZE;
        reg->vavg_max = sumv / MAX_SIZE;
        printf("I Avg Max = %d, V Avg Max = %d\n", reg->i_avg_max, reg->vavg_max);
        sumi = sumv = 0;
    }
    return NULL;
}
 
void *calc_max(void *arg)
{
    struct em_registers *reg;

    if (arg == NULL)
    {
        printf("Argument is null\n");
        return NULL;
    }
    reg = arg;

    while (1)
    {
        // TODO 14: Wait for the registers to be updated
        // TODO 15: Get the appropriate mutex to safely read the registers
        reg->ia_max = max(reg->ia_max, reg->ia);
        reg->ib_max = max(reg->ib_max, reg->ib);
        reg->ic_max = max(reg->ic_max, reg->ic);
        reg->va_max = max(reg->va_max, reg->va);
        reg->vb_max = max(reg->vb_max, reg->vb);
        reg->vc_max = max(reg->vc_max, reg->vc);
        printf("Max so far is\n");
        printf("Va Max = %u, Vb Max = %u, Vc Max = %u\n", reg->va_max, reg->vb_max, reg->vc_max);
        printf("Ia Max = %u, Ib Max = %u, Ic Max = %u\n", reg->ia_max, reg->ib_max, reg->ic_max);
        i_avg[count] = reg->ia_max;
        v_avg[count] = reg->va_max;
        count++;
        // TODO 16: Notify the calc_avg_max thread when count reaches 4
    }
    return NULL;
}

// TODO 7: Update the signature as thread requirement
void update_registers(struct em_registers *regs)
{
    struct em_registers *reg;
    if (regs == NULL)
    {
        printf("Invalid argument\n");
        return;
    }
    reg = regs;

    while (1)
    {
        srand(time(0));
        // TODO 12: Use appropriate mechanism to synchronize the access to registers
        reg->va = (rand() % (MAX_VOLTAGE - MIN_VOLTAGE + 1)) + MIN_VOLTAGE;
        reg->vb = (rand() % (MAX_VOLTAGE - MIN_VOLTAGE + 1)) + MIN_VOLTAGE;
        reg->vc = (rand() % (MAX_VOLTAGE - MIN_VOLTAGE + 1)) + MIN_VOLTAGE;
        reg->freq = (rand() % (MAX_FREQ - MAX_FREQ + 1)) + MIN_FREQ;
        reg->ia = (rand() % (MAX_CURRENT - MIN_CURRENT + 1)) + MIN_CURRENT;
        reg->ib = (rand() % (MAX_CURRENT - MIN_CURRENT + 1)) + MIN_CURRENT;
        reg->ic = (rand() % (MAX_CURRENT - MIN_CURRENT + 1)) + MIN_CURRENT;
        reg->kw_a = (rand() % (MAX_KW - MIN_KW + 1)) + MIN_KW;
        reg->kw_b = (rand() % (MAX_KW - MIN_KW + 1)) + MIN_KW;
        reg->kw_c = (rand() % (MAX_KW - MIN_KW + 1)) + MIN_KW;
        reg->va_th = VOLT_TH;
        reg->vb_th = VOLT_TH;
        reg->vc_th = VOLT_TH;
        // TODO 13: Notify calc_max thread of this update
        sleep(5);
    }
}

void update_shm(struct em_registers *reg, int sem_id, char *shm_addr)
{
    while (1) 
    {
        // TODO 8: Remove from here and convert into thread
        update_registers(reg);
        // TODO 5: Synchronize the access to shared memory using semaphore
        // TODO 20: Synchronize the access to local registers
        memcpy(shm_addr, reg, sizeof(struct em_registers));
        printf("Updated...\n");
        sleep(5);
    }
}

void *shm_allocate(key_t key, size_t shm_size,
        int flags, int *shm_id, void *addr)
{
    // TODO 2: Get and attach the shared memory
    printf("The segment id: %d (0x%X)\n", *shm_id, *shm_id);

    /*Attach the shared memory segment.*/
    return shmat(*shm_id, addr, 0);
}

int main()
{
    int shm_id;
    char *shm_addr = NULL;
    struct em_registers reg = {0};
    const int shm_size = sizeof(struct em_registers);
    int sem_id;
    pthread_t update_thid, calc_max_thid;

    // TODO 1: Allocate the shared memory segment
    printf("Shared memory attached at address %p\n", shm_addr);

    // TODO 3: Allocate the binary semaphore
    printf("Semaphore created with id: %d\n", sem_id);

    // TODO 4: Initialize the binary semaphore

    // TODO 6: Create the threads for update_registers & calc_max

    // TODO 11: Create the thread for calc_avg_max

    update_shm(&reg, sem_id, shm_addr);

    // TODO 7: Join the threads

    // TODO 9: Detach the shared memory segment
    printf("Shared memory detached\n");
    // TODO 10: Deallocate the shared memory segment

    return 0;
}
