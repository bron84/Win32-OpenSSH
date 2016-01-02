#pragma once

#include <memory.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

//File Descriptor definitions
#define MAX_FDS 128 //a 2^n number

typedef struct w32_fd_set_ {
	unsigned char bitmap[MAX_FDS >> 3];
}w32_fd_set;

#define fd_set w32_fd_set
#define FD_ZERO(set) (memset( (set), 0, sizeof(w32_fd_set)))
#define FD_SET(fd,set) ( (set)->bitmap[(fd) >> 3] |= (0x80 >> ((fd) % 8)))
#define FD_ISSET(fd, set) (( (set)->bitmap[(fd) >> 3] & (0x80 >> ((fd) % 8)))?1:0)
#define FD_CLR(fd, set) ((set)->bitmap[(fd) >> 3] &= (~(0x80 >> ((fd) % 8))))

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

//fcntl commands
#define F_GETFL 0x1
#define F_SETFL 0x2
#define F_GETFL 0x4
#define F_SETFL 0x8

//fd status flags
#define O_NONBLOCK 0x1

//fd flags
#define FD_CLOEXEC 0x1

#define socket w32_socket

/*w32 prototypes of posix functions*/
FILE* w32_fdopen(int fd, const char *mode);
int w32_fstat(int fd, struct stat *buf);
int w32_isatty(int fd);


/*network i/o*/
int w32_socket(int domain, int type, int protocol);

int w32_accept(int fd, struct sockaddr* addr, int* addrlen);
int w32_setsockopt(int fd, int level, int optname, const char* optval, int optlen);
int w32_getsockopt(int fd, int level, int optname, char* optval, int* optlen);
int w32_getsockname(int fd, struct sockaddr* name, int* namelen);
int w32_getpeername(int fd, struct sockaddr* name, int* namelen);
int w32_listen(int fd, int backlog);
int w32_bind(int fd, const struct sockaddr *name, int namelen);
int w32_connect(int fd, const struct sockaddr* name, int namelen);
int w32_shutdown(int fd, int how);

/*non-network i/o*/
int w32_pipe(int *pfds);
int w32_open(const char *pathname, int flags, ...);
int w32_wopen(const wchar_t *pathname, int flags, ...);
int w32_creat(const char *pathname, int mode);
int w32_read(int fd, void *dst, unsigned int max);
int w32_write(int fd, const void *buf, unsigned int max);
int w32_close(int fd);

/*operations on fds*/
int w32_ioctl(int d, int request, ...);
int w32_select(int fds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval *timeout);
int w32_fcntl(int fd, int cmd, ... /* arg */);
int w32_dup(int oldfd);
int w32_dup2(int oldfd, int newfd);


