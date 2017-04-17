#include <stdio.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SA struct sockaddr

int main(int argc, const char *argv[])
{

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("fail to socket");
		exit(1);
	
	
	}

	struct sockaddr_in my_addr,peer_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(50000);
	my_addr.sin_addr.s_addr=inet_addr("0.0.0.0");

	int ret_bind=bind(sockfd,(SA *)&my_addr,sizeof(my_addr));
	if(ret_bind<0)
	{
		perror("fail to bind");
		exit(1);
	
	
	
	}

	char buf[128];

	socklen_t len=sizeof(peer_addr);

	listen(sockfd,5);



	int ret_recv;

	while(1)
	{
		int confd=accept(sockfd,(SA*)&peer_addr,&len);
		if(confd<0)
		{
			perror("fail to accept");
			exit(1);

		}
		

		printf("ip:%s,port:%d is connected\n",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));

		while(1)
		{
			bzero(buf,sizeof(buf));

	
			ret_recv=recv(confd,buf,sizeof(buf),0);
			if(ret_recv<0)
			{
				perror("fail to recv");
				exit(1);


			}
			else if (ret_recv==0)
			{
				printf("peer is shutdown\n");
				close(confd);
				break;


			}
			else
			{

				printf("%s\n",buf);
				//send
				send(confd,buf,strlen(buf),0);
				//
				//close
			}
		}
	}

	return 0;
}
