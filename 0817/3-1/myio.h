#ifndef __MYIO_H_
#define __MYIO_H_

void myopen (const char *path, int flags, int *fd);
void myread (int fd, void *buf, size_t count, int *out);

#endif 