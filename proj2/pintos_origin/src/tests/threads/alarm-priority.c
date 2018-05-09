/* Checks that when the alarm clock wakes up threads, the
 higher-priority threads run first. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func alarm_priority_thread;
static struct semaphore wait_sema;

void
test_alarm_priority (void)
{
    /* This test does not work with the MLFQS. */
    ASSERT (!thread_mlfqs);
    
    sema_init (&wait_sema, 0);
    
    for (int i = 0; i < 10; i++)
    {
        int priority = PRI_DEFAULT - (i + 5) % 10 - 1;
        char name[16];
        snprintf (name, sizeof name, "priority %d", priority);
        thread_create (name, priority, alarm_priority_thread, NULL);
    }
    
    printf ("\nbegin\n");
    for (int i = 0; i < 10; i++)
        sema_up (&wait_sema);
    
    timer_sleep(2000);
    printf ("\nend\n");
}

static void
alarm_priority_thread (void *aux UNUSED)
{
    /* Now we know we're at the very beginning of a timer tick, so
     we can call timer_sleep() without worrying about races
     between checking the time and a timer interrupt. */
    
    sema_down (&wait_sema);
    /* Print a message on wake-up. */
    int64_t t = timer_ticks ();
    for (int i = 0; i < 30; )
        if (timer_ticks () != t)
            i++, t = timer_ticks ();
}
