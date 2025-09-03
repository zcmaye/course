#include "socket_wrap.h"
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define HDY_ERROR(fmt,...)\
	printf("[ERROR] %s:%d  : ",__FILE__,__LINE__);\
	printf(fmt,##__VA_ARGS__);\
	printf(" (%s)",strerror(errno));\
	printf("\n");

int hdy_accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;
again:
	if ((n = accept(fd, sa, salenptr)) < 0) {
		if ((errno == ECONNABORTED) || (errno == EINTR))
			goto again;
		else {
			HDY_ERROR("accept error");
			exit(-1);
		}
	}
	return n;
}

int hdy_bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	int n;
	if ((n = bind(fd, sa, salen)) < 0) {
		HDY_ERROR("bind error");
		exit(-1);
	}

	return n;
}

int hdy_connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	int n;
	n = connect(fd, sa, salen);
	if (n < 0) {
		HDY_ERROR("connect error");
		exit(-1);
	}

	return n;
}

int hdy_listen(int fd, int backlog)
{
	int n;
	if ((n = listen(fd, backlog)) < 0) {
		HDY_ERROR("listen error");
		exit(-1);
	}

	return n;
}

int hdy_socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0) {
		HDY_ERROR("socket error");
		exit(-1);
	}

	return n;
}

ssize_t hdy_read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
again:
	if ( (n = read(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}

	return n;
}

ssize_t hdy_write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;
again:
	if ((n = write(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}

int hdy_close(int fd)
{
	int n;
	if ((n = close(fd)) == -1) {
		HDY_ERROR("close error");
	}

	return n;
}
ssize_t hdy_read_len(int fd, void *vptr, size_t n)
{
	size_t  nleft = n;              //usigned int 剩余未读取的字节数
	ssize_t nread = 0;              //int 实际读到的字节数
	char   *ptr = vptr;

	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		} else if (nread == 0)
			break;

		nleft -= nread;   //nleft = nleft - nread 
		ptr += nread;
	}
	return n - nleft;
}

ssize_t hdy_write_len(int fd, const void *vptr, size_t n){
	size_t nleft = n;
	ssize_t nwritten = 0;
	const char *ptr = vptr;

	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}

ssize_t hdy_read_line(int sockfd, char*buffer, size_t size) {
	if (buffer == NULL || size < 3) { // 至少需要容纳一个字符 + \r\n
		errno = EINVAL;
		return -1;
	}

	ssize_t total_read = 0;
	ssize_t bytes_read;
	char ch;
	int found_cr = 0; // 标记是否已经找到 \r

	while (total_read < (ssize_t)(size - 1)) { // 保留位置给null终止符
											   // 一次读取一个字符
		bytes_read = recv(sockfd, &ch, 1, 0);

		if (bytes_read < 0) {
			if (errno == EINTR) { // 被信号中断，继续读取
				continue;
			}
			HDY_ERROR("recv failed in read_line");
			return -1;
		}

		if (bytes_read == 0) { // 对端关闭连接
			if (total_read == 0) {
				return 0; // 没有数据可读
			} else {
				break; // 有部分数据，但没有\r\n
			}
		}

		// 将字符存入缓冲区
		buffer[total_read++] = ch;

		// 检查行结束符
		if (ch == '\n') {
			if (found_cr) {
				// 找到了完整的 \r\n
				buffer[total_read] = '\0'; // 添加null终止符
				return total_read;
			}
			// 只有 \n 没有 \r，继续读取（有些系统可能只使用 \n）
		} else if (ch == '\r') {
			found_cr = 1;
		} else {
			found_cr = 0; // 重置标记
		}
	}

	// 缓冲区已满但未找到 \r\n
	errno = EMSGSIZE;
	return -1;
}
