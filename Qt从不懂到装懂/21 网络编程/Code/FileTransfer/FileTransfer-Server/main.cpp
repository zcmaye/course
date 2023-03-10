#include<QCoreApplication>
#include"Server.h"

int main(int argc,char* argv[])
{
	QCoreApplication a(argc, argv);

	Server server;
	server.startListen(5678);
	
	return a.exec();
}