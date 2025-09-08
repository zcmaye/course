//udp客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

int main()
{
	//创建socket
	int cfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(cfd<0)
	{
		perror("socket error");
		return -1;
	}

	int n;
	char buf[1024];
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);
	inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr.s_addr);

	while(1)
	{
		//读标准输入数据
		memset(buf, 0x00, sizeof(buf));
		n = read(STDIN_FILENO, buf, sizeof(buf));

		//发送数据
		sendto(cfd, buf, n, 0, (struct sockaddr *)&serv, sizeof(serv));

		//读取数据
		memset(buf, 0x00, sizeof(buf));
		n = recvfrom(cfd, buf, sizeof(buf), 0, NULL, NULL);
		printf("n==[%d], buf==[%s]\n", n, buf);
	}

	//关闭套接字
	close(cfd);

	return 0;
}
