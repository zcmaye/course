#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>

#include "socket_wrap.h"
#include "cjson/cJSON.h"

#define SERVER_NAME "Server:hdy-maye/1.0\r\n"
#define ROOT_DIR "./www"

void unimplemented(int client);
void handle_get_request(int client,const char* path,const char* params);
void handle_post_request(int client,const char* path,const char* params);
void not_found(int client);

int createServer(uint16_t port)
{
	int fd = hdy_socket(AF_INET,SOCK_STREAM,0);

	int optval = 1;
	setsockopt(fd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	hdy_bind(fd,(struct sockaddr*)&addr,sizeof(addr));

	hdy_listen(fd,5);

	return fd;
}

/*
* 处理客户端请求
*/
void handle_request(int client) {
	char buf[1024]={0};
	char method[16]={0};
	char url[128]={0};
	char path[128]={0};
	char params[128]={0};
	int nread = 0;

	//请求行 GET /user/edit?is_active=true&is_delete=false HTTP/1.1
	//解析请求行，拿出方法和URL
	nread = hdy_read_line(client,buf,sizeof(buf));
	if(sscanf(buf,"%s %s",method,url) !=2) {
		
	}
	printf("method:[%s],url:[%s]\n",method,url);

	//如果不是GET或POST方法，告诉客户端未实现
	if(strcmp(method,"GET") !=0 && strcmp(method,"POST")!=0) {
		unimplemented(client);
		return;	
	}

	//解析URL（PATH,PARAMS）
	// /user/edit?is_active=true&is_delete=false
	sscanf(url,"%[^?]?%s",path,params);
	printf("path:[%s],params:[%s]\n",path,params);

	if(strcmp(method,"GET") == 0) {

		//读取剩下的数据，并丢弃
		while((nread = hdy_read_line(client,buf,sizeof(buf)))>0 && buf[0] != '\r' && buf[1] != '\n') {
			printf("line data : %.*s\n",nread,buf);	
		}

		handle_get_request(client,path,params);
	}
	else if(strcmp(method,"POST") == 0) {
		handle_post_request(client,path,params);
	}

	printf("handle request finished!\n");
	sleep(1);
	close(client);
}

/*告诉客户端请求方法未实现*/
void unimplemented(int client)
{
	const char* html = "<h2>服务器不支持请求的功能，无法完成请求<h2>";

	char buf[1024];
	sprintf(buf,"HTTP/1.1 501 服务器不支持请求的功能，无法完成请求\r\n");	
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,SERVER_NAME);
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Type:text/html\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Length:%d\r\n",strlen(html));
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"%s\r\n",html);
	hdy_write(client,buf,strlen(buf));

}

void not_found(int client)
{
	const char* html = "<h2>Not Found!<h2>";

	char buf[1024];
	sprintf(buf,"HTTP/1.1 404 Not Found!\r\n");	
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,SERVER_NAME);
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Type:text/html\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Length:%d\r\n",strlen(html));
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"%s\r\n",html);
	hdy_write(client,buf,strlen(buf));
}

void not_mapping_method(int client,const char* method,const char* path)
{
	char html[512]={0};
	sprintf(html,"No mapping for HTTP-Method:'%s',URL '%s'",method,path);

	char buf[1024];
	sprintf(buf,"HTTP/1.1 404 Not Found!\r\n");	
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,SERVER_NAME);
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Type:text/html\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Length:%d\r\n",strlen(html));
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"%s\r\n",html);
	hdy_write(client,buf,strlen(buf));
}

void response_json(int client,const char* data,int status)
{
	char buf[1024];
	sprintf(buf,"HTTP/1.1 %d Hdy!\r\n",status);	
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,SERVER_NAME);
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Type:application/json\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"Content-Length:%d\r\n",strlen(data));
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"\r\n");
	hdy_write(client,buf,strlen(buf));
	sprintf(buf,"%s\r\n",data);
	hdy_write(client,buf,strlen(buf));
}

void send_file(int client,const char* filename)
{
	FILE* resource = fopen(filename,"rb");
	if(!resource) {
		not_found(client);
	}
	else{
		//获取文件长度
		fseek(resource,0,SEEK_END);
		int length = ftell(resource);
		fseek(resource,0,SEEK_SET);

		char buf[1024];
		//写入消息头
		sprintf(buf,"HTTP/1.1 200 OK\r\n");	
		hdy_write(client,buf,strlen(buf));
		sprintf(buf,SERVER_NAME);
		hdy_write(client,buf,strlen(buf));
		sprintf(buf,"Content-Type:text/html\r\n");
		hdy_write(client,buf,strlen(buf));
		sprintf(buf,"Content-Length:%d\r\n",length);
		hdy_write(client,buf,strlen(buf));
		sprintf(buf,"\r\n");
		hdy_write(client,buf,strlen(buf));

		//写入消息体
		while(!feof(resource)) {
			int nread = fread(buf,1,1024,resource);
			hdy_write(client,buf,nread);
		}
	}
	fclose(resource);
}

void handle_get_request(int client,const char* path,const char* params)
{
	char filename[128];
	struct stat st;

	//如果path只有一个/,也就是访问默认资源
	if(strcmp(path,"/") == 0) {
		sprintf(filename,"%s/index.html",ROOT_DIR);
	}
	else{
		sprintf(filename,"%s%s",ROOT_DIR,path);
	}
	printf("filename is : [%s]\n",filename);


	//查看文件是否存在
	if(stat(filename,&st) == -1) {
		sprintf(filename,"%s/notFound404.html",ROOT_DIR);
		if(stat(filename,&st) == -1) {
			not_found(client);
		}
	}
	send_file(client,filename);
}

void handle_post_request(int client,const char* path,const char* params)
{
	printf("handle post request : %s\n",path);
	char buf[1024];
	char header[128];
	char value[128];
	int nread;

	int contentLength= 0;			//数据大小
	char contentType[64];			//数据类型
	char contentDisposition[64];	//数据位置(可能有文件名)
	char* data = NULL;				//数据缓冲区指针

	//读取所有头，并获取数据长度
	while((nread = hdy_read_line(client,buf,sizeof(buf)))>0 && buf[0] != '\r' && buf[1] != '\n') {
		//printf("%.*s\n",nread,buf);
		if(sscanf(buf,"%[^:]: %[^\r]",header,value) !=2) {
			printf("header parse error:%s\n",header);
		}
		else{
			//printf("header:%s, value:%s\n",header,value);
			if(strcmp(header,"Content-Length") == 0) {
				contentLength = atoi(value);
			}
			//如果需要获取文件类型和拓展名，请求时必须加上如下两个头：
			//Content-Type: image/gif
			//Content-Disposition: attachment;filename="example.gif"
			else if(strcmp(header,"Content-Type") == 0) {
				strncpy(contentType,value,nread);
			}
			else if(strcmp(header,"Content-Disposition") == 0) {
				strncpy(contentDisposition,value,nread);
			}
			printf("header:%s, value:%s\n",header,value);
		}
	}

	printf("data length : %d\n",contentLength);

	//读取body
	if(contentLength > 0) {
		//动态分配内存
		data = malloc(sizeof(char) * contentLength);
		if(!data) {
			response_json(client,"{\"code\":500,\"message\":\"error,malloc!\",\"data\":null}",500);
			return;
		}
		printf("reading body!\n");
		nread = hdy_read_len(client,data,contentLength);
		//printf("read body success,data is : %.*s\n",nread,buf);
	}

	printf("path is : %s\n",path);
	if(strcmp(path,"/login") == 0) {
		//解析Json
		cJSON * json = cJSON_ParseWithLength(buf,contentLength);
		if(!json) {
			response_json(client,"{\"code\":500,\"message\":\"error,json parse error\",\"data\":null}",200);
			free(data);
			return;
		}

		cJSON* usernameItem = cJSON_GetObjectItem(json,"username");
		cJSON* passwordItem = cJSON_GetObjectItem(json,"password");

		if(strcmp(usernameItem->valuestring,"maye") != 0 || strcmp(passwordItem->valuestring,"123456") != 0) {
			response_json(client,"{\"code\":500,\"message\":\"账号或密码错误\",\"data\":null}",200);
			free(data);
			return;
		}

		response_json(client,"{\"code\":200,\"message\":\"success\",\"data\":null}",200);
	}
	else if(strcmp(path,"/upload") == 0) {
		//获取文件名和拓展名
		char filename [128];
		sscanf(contentDisposition,"attachment;filename=\"%[^\"]",filename);
		printf("filename is : %s\n",filename);

		FILE* fp = fopen(filename,"wb");	
		if(!fp) {
			response_json(client,"{\"code\":500,\"message\":\"文件保存失败\",\"data\":null}",200);
			free(data);
			return;
		}
		if(fwrite(data,1,contentLength,fp) != contentLength) {
			response_json(client,"{\"code\":500,\"message\":\"保存文件时失败，写入数据不正确\",\"data\":null}",200);
			free(data);
			fclose(fp);
			return;
		}
		fflush(fp);
		fclose(fp);
		response_json(client,"{\"code\":200,\"message\":\"success\",\"data\":null}",200);
	}
	else{
		printf("path is : %s\n",path);
		not_mapping_method(client,"POST",path);		
	}
	free(data);
}


int main()
{
	int fd = createServer(8080);

	int counter = 0;
	while(1) {
		int client = hdy_accept(fd,NULL,NULL);
		if(client<0) {
			counter++;
			if(counter > 3)
				break;
			continue;
		}
		handle_request(client);
	}

	close(fd);
	return 0;
}

