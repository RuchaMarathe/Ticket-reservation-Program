#include <stdio.h>
#define _USE_BSD 1
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <mysql/mysql.h>
#define  WIN                // WIN for Winsock and BSD for BSD sockets

//----- Include files -------------------------------------------------------
#include <stdio.h>          // Needed for printf()
#include <stdlib.h>         // Needed for memcpy()
#ifdef WIN32
  #include <winsock.h>      // Needed for all Windows stuff
#endif
#ifdef BSD
  #include <sys/types.h>    // Needed for system defined identifiers.
  #include <netinet/in.h>   // Needed for internet address structure.
  #include <sys/socket.h>   // Needed for socket(), bind(), etc...
  #include <arpa/inet.h>    // Needed for inet_ntoa()
  #include <fcntl.h>
  #include <netdb.h>
#endif
static char *host = "localhost";//local server name
static char *user = "root"; //username of mysql server
static char *pass =  "Sachinsp14!";
static char *dbname = "test_sachin";

unsigned int port = 3306; 
static char *unix_socket = NULL; // specify the connection type
unsigned int flag = 0; //ODBC connection
int errexit(const char* format,...);
int connectTCP(const char *service);
int connectsock(const char *service,const char *transport);

int main(char argc,char *argv[])
{
	#ifdef WIN32
	//int err;
  	WORD wVersionRequested = MAKEWORD(1,1); // Stuff for WSA functions
  	WSADATA wsaData;                        // Stuff for WSA functions
	#endif
	
	#ifdef WIN32
	int err;
  	err = WSAStartup(wVersionRequested, &wsaData);
	if (err !=0)
	{
		fprintf(stderr,"Could't initialize winsock");
		exit(1);
	}	
	#endif

	char message[100];
	char *service="echo";	
	int acceptsock,sock;
	struct sockaddr_in6 sin;

	fd_set afds;
	fd_set rfds;
	int fd,nfds;
	sock=connectTCP(service);	
	nfds=getdtablesize();
	FD_ZERO(&afds);
	FD_SET(sock,&afds);

	while(1)
	{
		memcpy(&rfds,&afds,sizeof(rfds));

		if(select(nfds,&rfds,(fd_set *)0,(fd_set *)0,(struct timeval *)0)<0)
			errexit("*select: %s\n", strerror(errno));

		if(FD_ISSET(sock,&rfds))
		{	
			MYSQL *conn;
			MYSQL_RES *res;
			MYSQL_ROW row;
			conn = mysql_init(NULL); // prepare connectivity to the database
			if(!(mysql_real_connect(conn,host,user,pass,dbname,port,unix_socket,flag))) //return 0 on success
			{
				fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
				exit(1);
			}	
		
			acceptsock=accept(sock,(struct sockaddr*)NULL,NULL);

			if(acceptsock<0)
			{
				printf("error in accepting\n");
				exit(0);
			}
			FD_SET(acceptsock,&afds);		

			read(acceptsock,message,100);		
			char str[1000];	
			char *username = strtok(message," ");		
			char *password = strtok(NULL,"\n");	
			sprintf(str,"select * from Login_Details where username = '%s' and password = AES_ENCRYPT('%s','sanjose123')",username,password);
			mysql_query(conn, str); 
			res = mysql_store_result(conn);	
	
			if(row = mysql_fetch_row(res))
			{
				printf("Logged in Successfully\n");
				char *msg=row[3];
				ssize_t sent_bytes;
				if((sent_bytes = send(acceptsock,msg,20000,0))<0)
		   			printf("send error\n");	
			}
			else
			{
				printf("Log in Failed\nVerify your Username and Password\n");		
				char *msg="Log in Failed";
				ssize_t sent_bytes;
				if((sent_bytes = send(acceptsock,msg,20000,0))<0)
		   			printf("send error\n");				
			}
		}
		for (fd=0; fd<nfds; ++fd)
		{
			if (fd != sock && FD_ISSET(fd, &rfds))
			{
				close(fd);
				FD_CLR(fd, &afds);
			}
		}		
	}		
}


int connectsock(const char *service,const char *transport)
{
	struct sockaddr_in6 server;

	int serversock,type,acceptsock,number;

	memset(&server,0,sizeof(server));

	server.sin6_flowinfo = 0;
	server.sin6_family = AF_INET6;
	server.sin6_addr = in6addr_any;
	server.sin6_port = htons(8000);

	/* Use protocol to choose a socket type */

	if(strcmp(transport,"udp")==0)
	{
		type=SOCK_DGRAM;
	}
	else
	{
		type=SOCK_STREAM;
	}

	/* Allocate a socket */

	serversock=socket(AF_INET6,type,0);

	if(serversock<0)
	{
		printf("Cant create socket\n");
		exit(0);
	}

	number=1;

	if(setsockopt(serversock,SOL_SOCKET,SO_REUSEPORT,(const char*)&number,sizeof(number))<0)
	{
		printf("setsockopt(SO_REUSEPORT) failed\n");
		exit(0);
	}

	/* Bind Call : Adds details from serversock to socket descriptor */

	int b;
	b=bind(serversock,(struct sockaddr*)&server,sizeof(server));

	if(b<0)
	{
		printf("Binding error\n");
		exit(0);
	}

	/* Listen Call : Allows 10 connections at the socket to wait in queue  */

	int listeningsock;
	listeningsock=listen(serversock,10);
	if(listeningsock<0)
	{
		printf("Error in listening\n");
		exit(0);
	}

	return serversock;
}


int connectTCP(const char *service)
{
	return connectsock(service,"tcp");
}

int errexit(const char* format,...)
{
	va_list args;

	va_start(args,format);
	vfprintf(stderr,format,args);
	va_end(args);
	exit(1);
}
