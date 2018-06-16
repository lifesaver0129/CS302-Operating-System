#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "threads/interrupt.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler(struct intr_frame *);

static int get_user(const uint8_t *uaddr);
static bool put_user(uint8_t *udst, uint8_t byte);
static void load_user_data(void *dst_, const void *src_, size_t size);

void syscall_init(void) {
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler(struct intr_frame *f) {
  int syscall_num = NULL;

  load_user_data(&syscall_num, f->esp, sizeof(syscall_num));

  switch (syscall_num) {
    // 0 SYS_HALT,     /* Halt the operating system. */
    case SYS_HALT: {
      syscall_halt();
      break;
    }
    // 1 SYS_EXIT,     /* Terminate this process. */
    case SYS_EXIT: {
      int status;

      load_user_data(&status, f->esp + 4, sizeof(status));

      syscall_exit(status);
      break;
    }
    // 2 SYS_EXEC,     /* Start another process. */
    case SYS_EXEC: {
      const char *cmd_line;

      load_user_data(&cmd_line, f->esp + 4, sizeof(cmd_line));
      if (get_user(cmd_line) == -1) {
        syscall_exit(-1);
      }

      int ret = syscall_exec(cmd_line);
      f->eax = ret;
      break;
    }
    // 3 SYS_WAIT,     /* Wait for a child process to die. */
    case SYS_WAIT: {
      pid_t pid;

      load_user_data(&pid, f->esp + 4, sizeof(pid));

      int ret;
      ret = syscall_wait(pid);
      f->eax = ret;
      break;
    }
    // 4 SYS_CREATE,   /* Create a file. */
    case SYS_CREATE: {
      const char *file_name;
      unsigned initial_size;

      load_user_data(&file_name, f->esp + 4, sizeof(file_name));
      load_user_data(&initial_size, f->esp + 8, sizeof(initial_size));
      if (file_name == NULL || get_user(file_name) == -1) {
        syscall_exit(-1);
      }

      bool ret = syscall_create(file_name, initial_size);
      f->eax = ret;
      break;
    }
    // 5 SYS_REMOVE,   /* Delete a file. */
    case SYS_REMOVE: {
      const char *file_name;

      load_user_data(&file_name, f->esp + 4, sizeof(file_name));

      bool ret = syscall_remove(file_name);
      f->eax = ret;
      break;
    }
    // 6 SYS_OPEN,     /* Open a file. */
    case SYS_OPEN: {
      const char *file_name;
      load_user_data(&file_name, f->esp + 4, sizeof(file_name));

      if (file_name == NULL || get_user(file_name) == -1) {
        syscall_exit(-1);
      }

      int ret = syscall_open(file_name);
      f->eax = ret;
      break;
    }
    // 7 SYS_FILESIZE, /* Obtain a file's size. */
    case SYS_FILESIZE: {
      int fd;

      load_user_data(&fd, f->esp + 4, sizeof(fd));

      int ret = syscall_filesize(fd);
      f->eax = ret;
      break;
    }
    // 8 SYS_READ,     /* Read from a file. */
    case SYS_READ: {
      int fd;
      const void *buffer;
      unsigned size;

      load_user_data(&fd, f->esp + 4, sizeof(fd));
      load_user_data(&buffer, f->esp + 8, sizeof(buffer));
      load_user_data(&size, f->esp + 12, sizeof(size));

      if (get_user(buffer) == -1) {
        syscall_exit(-1);
      }

      int ret = syscall_read(fd, buffer, size);
      f->eax = ret;
      break;
    }
    // 9 SYS_WRITE,    /* Write to a file. */
    case SYS_WRITE: {
      int fd;
      const void *buffer;
      unsigned size;

      load_user_data(&fd, f->esp + 4, sizeof(fd));
      load_user_data(&buffer, f->esp + 8, sizeof(buffer));
      load_user_data(&size, f->esp + 12, sizeof(size));
      if (buffer == NULL || get_user(buffer) == -1) {
        syscall_exit(-1);
      }

      int ret = syscall_write(fd, buffer, size);
      f->eax = ret;
      break;
    }
    // 10 SYS_SEEK,     /* Change position in a file. */
    case SYS_SEEK: {
      int fd_num;
      unsigned position;

      load_user_data(&fd_num, f->esp + 4, sizeof(fd_num));
      load_user_data(&position, f->esp + 8, sizeof(position));

      syscall_seek(fd_num, position);
      break;
    }
    // 11 SYS_TELL,     /* Report current position in a file. */
    case SYS_TELL: {
      int fd_num;

      load_user_data(&fd_num, f->esp + 4, sizeof(fd_num));

      unsigned ret = syscall_tell(fd_num);
      f->eax = ret;
      break;
    }
    // 12 SYS_CLOSE,    /* Close a file. */
    case SYS_CLOSE: {
      int fd_num;

      load_user_data(&fd_num, f->esp + 4, sizeof(fd_num));

      syscall_close(fd_num);
      break;
    }
    default: {
      printf("Wrong system call number %d!\n", syscall_num);
      thread_exit();
      break;
    }
  }
}

void syscall_halt() { shutdown_power_off(); }

void syscall_exit(int status) {
  struct thread *cur = thread_current();
  struct child_thread *child = NULL;
  struct list_elem *e;

  for (e = list_begin(&cur->parent->children);
       e != list_end(&cur->parent->children); e = list_next(e)) {
    struct child_thread *t = list_entry(e, struct child_thread, child_elem);
    if (cur->tid == t->tid) {
      child = t;
      child->exit_status = status;
      child->exited = true;
      if (cur->parent->waiting_for == cur->tid) {
        sema_up(&child->child_exit);
      }
      break;
    }
  }

  cur->exit_status = status;
  printf("%s: exit(%d)\n", cur->name, cur->exit_status);
  thread_exit();
}

pid_t syscall_exec(const char *cmd_line) {
  pid_t ret;
  acquire_filesys_lock();
  ret = process_execute(cmd_line);
  release_filesys_lock();
  return ret;
}

int syscall_wait(pid_t pid) { return process_wait(pid); }

bool syscall_create(const char *file, unsigned initial_size) {
  bool ret;

  acquire_filesys_lock();
  ret = filesys_create(file, initial_size);
  release_filesys_lock();

  return ret;
}

bool syscall_remove(const char *file) {
  bool ret;

  acquire_filesys_lock();
  ret = filesys_remove(file);
  release_filesys_lock();

  return ret;
}

int syscall_open(const char *file) {
  struct thread *cur = thread_current();
  struct file_descriptor *fd = malloc(sizeof(struct file_descriptor));
  if (fd == NULL) {
    return -1;
  }

  acquire_filesys_lock();
  fd->fd_file = filesys_open(file);
  if (fd->fd_file == NULL) {
    release_filesys_lock();
    return -1;
  }
  fd->fd_num = cur->fd_num_to_assign++;
  list_push_back(&cur->file_descriptors, &fd->fd_elem);
  release_filesys_lock();

  return fd->fd_num;
}

int syscall_filesize(int fd_num) {
  int ret = -1;
  struct thread *cur = thread_current();
  struct file_descriptor *fd = malloc(sizeof(struct file_descriptor));
  struct list *file_descriptors = &cur->file_descriptors;
  struct list_elem *e;

  acquire_filesys_lock();
  for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
       e = list_next(file_descriptors)) {
    // get the file_descriptor in file_descriptors
    fd = list_entry(e, struct file_descriptor, fd_elem);

    if (fd_num == fd->fd_num) {
      ret = file_length(fd->fd_file);
      break;
    }
  }
  release_filesys_lock();

  return ret;
}

int syscall_read(int fd_num, void *buffer, unsigned size) {
  struct thread *cur = thread_current();
  struct file_descriptor *fd;
  struct list *file_descriptors = &cur->file_descriptors;
  int ret = -1;

  if (0 == fd_num) {
    ret = input_getc();

  } else {
    struct list_elem *e;
    acquire_filesys_lock();
    for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
         e = list_next(file_descriptors)) {
      // get the file_descriptor in file_descriptors
      fd = list_entry(e, struct file_descriptor, fd_elem);

      if (fd_num == fd->fd_num) {
        ret = file_read(fd->fd_file, buffer, size);
        break;
      }
    }
    release_filesys_lock();
  }
  return ret;
}

int syscall_write(int fd_num, const void *buffer, unsigned size) {
  int ret;

  if (1 == fd_num) {
    putbuf(buffer, size);
    ret = size;
  } else {
    struct file_descriptor *fd = NULL;
    struct thread *cur = thread_current();
    struct list *file_descriptors = &cur->file_descriptors;
    struct list_elem *e;

    for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
         e = list_next(file_descriptors)) {
      // get the file_descriptor in file_descriptors
      fd = list_entry(e, struct file_descriptor, fd_elem);

      if (fd_num == fd->fd_num) {
        break;
      }
    }
    if (fd != NULL) {
      acquire_filesys_lock();
      ret = file_write(fd->fd_file, buffer, size);

      release_filesys_lock();
    }
  }
  return ret;
}

void syscall_seek(int fd_num, unsigned position) {
  struct thread *cur = thread_current();
  struct file_descriptor *fd;
  struct list *file_descriptors = &cur->file_descriptors;
  struct list_elem *e;

  acquire_filesys_lock();
  for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
       e = list_next(file_descriptors)) {
    // get the file_descriptor in file_descriptors
    fd = list_entry(e, struct file_descriptor, fd_elem);

    if (fd_num == fd->fd_num) {
      file_seek(fd->fd_file, position);
      break;
    }
  }
  release_filesys_lock();
}

unsigned syscall_tell(int fd_num) {
  unsigned ret = -1;
  struct thread *cur = thread_current();
  struct file_descriptor *fd;
  struct list *file_descriptors = &cur->file_descriptors;
  struct list_elem *e;

  acquire_filesys_lock();
  for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
       e = list_next(file_descriptors)) {
    // get the file_descriptor in file_descriptors
    fd = list_entry(e, struct file_descriptor, fd_elem);

    if (fd_num == fd->fd_num) {
      ret = file_tell(fd->fd_file);
      break;
    }
  }
  release_filesys_lock();

  return ret;
}

void syscall_close(int fd_num) {
  struct thread *cur = thread_current();

  struct file_descriptor *fd;
  struct list *file_descriptors = &cur->file_descriptors;
  struct list_elem *e;

  acquire_filesys_lock();
  for (e = list_begin(file_descriptors); e != list_end(file_descriptors);
       e = list_next(file_descriptors)) {
    // get the file_descriptor in file_descriptors
    fd = list_entry(e, struct file_descriptor, fd_elem);

    if (fd_num == fd->fd_num) {
      list_remove(&fd->fd_elem);
      file_close(fd->fd_file);
      break;
    }
  }
  release_filesys_lock();
}

/* Reads a byte at user virtual address UADDR.
   UADDR must be below PHYS_BASE.
   Returns the byte value if successful,
   -1 if a segfault occurred. */
static int get_user(const uint8_t *uaddr) {
  if (!is_user_vaddr(uaddr)) {
    return -1;
  }

  int result;
  asm("movl $1f, %0; movzbl %1, %0; 1:" : "=&a"(result) : "m"(*uaddr));
  return result;
}

/* Writes BYTE to user address UDST.
   UDST must be below PHYS_BASE.
   Returns true if successful,
   false if a segfault occurred. */
static bool put_user(uint8_t *udst, uint8_t byte) {
  if (!is_user_vaddr(udst)) {
    return false;
  }
  int error_code;
  asm("movl $1f, %0; movb %b2, %1; 1:"
      : "=&a"(error_code), "=m"(*udst)
      : "q"(byte));
  return error_code != -1;
}

/* Load data from user memory, according to memcpy(). */
static void load_user_data(void *dst_, const void *src_, size_t size) {
  unsigned char *dst = dst_;
  const unsigned char *src = src_;

  ASSERT(dst != NULL || size == 0);
  ASSERT(src != NULL || size == 0);

  // data frame 4 bytes long
  int32_t data;

  while (size-- > 0) {
    data = get_user(src++);
    // if the addr of src is wrong or segfault occurred
    if (data == -1) {
      syscall_exit(-1);
    }
    *dst++ = data;
  }
  return dst_;
}

void close_all_files() {
  struct thread *cur = thread_current();
  struct file_descriptor *fd;
  struct list *file_descriptors = &cur->file_descriptors;
  struct list_elem *e;

  while (!list_empty(file_descriptors)) {
    // get the file_descriptor in file_descriptors
    e = list_pop_front(file_descriptors);
    fd = list_entry(e, struct file_descriptor, fd_elem);

    list_remove(&fd->fd_elem);
    file_close(fd->fd_file);
  }
}