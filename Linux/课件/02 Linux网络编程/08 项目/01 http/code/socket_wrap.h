#pragma once

#include <sys/socket.h>
#include <stdio.h>

void hdy_exit(const char *s);
int hdy_accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
int hdy_bind(int fd, const struct sockaddr *sa, socklen_t salen);
int hdy_connect(int fd, const struct sockaddr *sa, socklen_t salen);
int hdy_listen(int fd, int backlog);
int hdy_socket(int family, int type, int protocol);
ssize_t hdy_read(int fd, void *ptr, size_t nbytes);
ssize_t hdy_write(int fd, const void *ptr, size_t nbytes);
int hdy_close(int fd);
ssize_t hdy_read_len(int fd, void *vptr, size_t n);
ssize_t hdy_write_len(int fd, const void *vptr, size_t n);
ssize_t hdy_read_line(int fd, char*buffer, size_t maxlen);
