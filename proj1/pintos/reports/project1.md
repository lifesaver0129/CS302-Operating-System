# Project 1: Thread Report

#### 11510109 Tiankai Jiang
#### 11510225 Yuxing Hu

---

## Preliminary

### Introduction

The thread project require us to finish some specific targets and add some 
features into the thread system which is implemented on Pintos, an educational 
operating system. Pintos operating system allow us to manage kernel threads, 
loading and running user programs, and a file system, but it implements all 
of these in a very simple way. For this project, we focused on thread organization,
including reimplementing scheduler, using round-robin type scheduler to control,
and write the priority scheduler.

### Software dependency

The whole project is deployed and tested under the Ubanto 14.04 version Linux OS. 
The majority of codes are written within vim, whereas the others are used sublime
text to type in. For debugging, we choose gdb as the testing instrument.

---

## Task 1: Scheduler based on time slice

**Data structures and Functions**

- In timer.c, we add the global variable:
  
  extern struct list blocked_list;

  This list is meant to obtain a sleeping threads and keep tracking them.
  
- In thread.h, we add a member variable：
  
  int64_t ticks_blocked;
  
  This integer is meant to record how long (how many ticks) has the thread been
  forced to slept.
  
**Algorithm and Methods**

The problem with original solution of the timer_sleep function is that the 
thread is keep crossing between the running queue and ready queue which takes
lots of CPU resources and we need to reimplement the wake up strategy.

To achieve the timer_sleep() without causing any busy-waiting, we try to block
the thread at the time we call timer_sleep() function. Because we've already add
a member variable into the thread construction, so we just need to use the OS's
time interrupt and add the detection of thread itself. Each time ticks_blocked
will minus 1, and when it comes to 0, this thread will be woke up.

In timer_sleep function, before we start, we need to check for valid ticks
argument, which means the ticks should bigger than 0. Then we calculate the
tick value for the thread as described above. This is calculated by adding
the global ticks (ticks since the OS booted) to the ticks argument.
And then we add the current thread to the sleep list. And finally we will
block the thread.

Need to mention that we used insr_disable to make current thread can not be
interrupted.
  
---

## Task 2: Round-Robin scheduler

**Data structures and Functions**

- In thread.h, we add a member variable：
  
  int TIME_SLICE;
  
  This int is meant to set the time slice.

  
**Algorithm and Methods**

So task 2 asked us to implement the round robin scheduler and set this as the
default scheduler algorithm, however, we found that the system already set 
the changing type to round robin.

There's also other requirement we needs to follow, that is the time_slice of 
the thread should be set as original priority %7 +2, which is the reason we 
define a new int value called TIME_SLICE and record the new set time slice. 

---
  
## Task 3: Priority scheduler based on time slice

**Data structures and Functions**

- In thread.h, we add the following member variables：

  - int init_pri;
  
    This remains the initial priority of the thread.
    
  - struct list locks;
  
    This is used for lock the thread that is holding.
    
  - struct lock *lw;
  
    The lock the thread is currently waiting on, and the value of this lock 
    will set to NULL if there's no lock.
   
  - static inline bool pri_comp (const struct list_elem *a, const struct list_elem *b, 
  void *aux UNUSED);
  
    This is a boolean value and it will compare two list_elem value and return
    whether former one is way higher than the latter one.

  - max(a,b)({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

    This macro return the max between two integers.
 
  - In synch.h, we add the following member variables：

  - struct list_elem elem;
  
    This list_elem is inside of lock, and is a list element for priority donation.
    
  - int max_priority;
  
    This integer is also inside the lock, and is used to indicate the maximum 
    priority of a thread.
    
  - static inline bool lc (const struct list_elem *a, const struct list_elem *b, void *aux);

  - static inline bool sc (const struct list_elem *a, const struct list_elem *b, void *aux);
  
    Both of these two boolean return value is used to determine the order of 
    list_elem.
    
**Algorithm and Methods**

To begin with, we need to set the priority dispatch algorithm. The updated priority
is set to max(formal_priority-3, 0). And we implement this method in the 
thread_tick() method.

By analyse the property of thread we can find out that it already has a priority
value and all we need to do is containing a priority queue, which means we need to
make the list priority ordered when we add thread into the queue, including:

  - unlocking the thread
  
  - initialize the thread
  
  - yield the thread
  
We can know that currently the way of adding the thread into the list is pushing
the list to the back, which is not the right choice of setting in. However, in
list.c, we found there's a method called list_insert_ordered, which is exactly
what we need to implement the thread. This method require us to input the compare
method, which we have wrote by ourselves: pri_comp(). We should also change the
insert method inside the thread_yield() and thread_init().

Next test require us to implement the preemptive dispatch scheduler, which means
when we create a new thread, if the priority of it is higher than the current one,
we should run that first, and the current thread(which has a lower priority) needs
to be blocked.

In order to achieve this requirement, we need to call thread_yield() when we 
change the priority of the thread. Another circumstance is that when the new
created thread which has a higher thread than current one.

There are several priority relation tests in this task, so we decide to analyze them
first and try to know what do they acquire us to do. So the logistic of testing
can be summarized as:

  1. When a thread acquire a lock, if the lock's priority is lower than the thread itself,
  increase it; if this lock is also locking by other lock, the priority of lock will be
  donated, and when that lock is gone, resume the previous priority.
  
  2. If a thread is donated by several threads, maintain the highest priority.
  
  3. When we setting the priority, if the thread is under donation, we should set the 
  original_prioirty, and if the current setting priority is greater than current
  priority, change the current priority, otherwise resume the original_priority when the
  donation is over.
  
  4. At the releasing lock process, and the priority is changing, we should consider the
  donate priority and current priority.
  
  5. Change the signal waiting queue to priority queue.

  6. Change the waiter queue inside the condition situation to priority queue.
  
  7. If the priority is changing when releasing the lock, preemption could happen.
  
So the first thing we've done is that add some new member variables into the thread 
and lock. We change the lock acquire function so that the priority donation could 
happen before the POST action. And the thread that has been woken up become the 
owner of the lock. The way of achieving the priority is to change the lock's highest
priority.

Every time we insert the thread, or a donate action is happen, we will check the 
priority, insert orderly and yield the thread. We also need to change the arrange 
function of lock list. We noticed that when we release a lock, current priority 
could also change. So we rewrite the thread_update_priority function. If the thread
has a lock, we require the maximum priority which could be donated by higher thread.
And if this priority is higher than base_priority we should update the donated priority.

Last but not least, we need to change the condition queue into priority queue. To do that,
we add list_sort function inside the cond_signal function and add two compare function 
to make things more clear. The semaphore's waiting queue should also be initialized as
priority queue by revising the sema_up and sema_down function.

A potential race condition would be while the thread priority variable is being updated
to the new priority, the interrupt handler is writing to the priority variable. Thus,
these conflicting writes could mangle the priority variable, therefore being a race
condition.

---

## Additions

### Differences

The current version is way different comparing the origin version we thought it would 
like to be. We use lots of prioirty queue, however the origin thought of implement this
is to use another list to maintain the queueing status. However, after we deep reading
the program kernel, we found that there is a more easy way to implement it which is
called insert_ordered_list. So we choose to use that function instead of our origin
plan.

Another major difference is that we decide to maintion the priority queue by checking the
status every time we insert it rather than to change the list itself. We know that by
adding few function to the list.c file can be another way to achieve the list, however, 
we choose to call the function every time we invoke it so the process can be read more
easily.

### Reflection

**Tiankai Jiang**

Making the prograssing plan, reading the document, disscussing within the group, 
implementing task 1, 2 and 3.

**Yuxing Hu**

Making the prograssing plan, reading the document, disscussing within the group, 
implementing task 3, writing the report.

### Futher thinking

We've been doing this project almost for a month, and sometimes it really become a 
nightmare for us. The project is made by Stanford(or Berkeley?) University, however
our TA have done several localizate changes, which is great because that makes us
comprehensive more easily. The problem is to achieve the right target we need to
get through the test, but lots of the tests are no longer useful becuase some basic
rules of project has been change, so debugging become a serious work for us and caused
us a lot of time. 

We would like to thank all the TAs for their tremendous job and replies on BB which
really helped us a lot. It has been a great experience for us when we revise what
we've done for this project.
