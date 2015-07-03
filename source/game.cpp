#include "poker.h"
#include "socket.h"

string b_reg;
int process=IDEL;

string msg_reg;
int cnt;
gamer g;
int    sockfd ;
int ac_time;

void reg_init(const char* name,char* id)
{
	char reg_buff[50]={'\0'};
	sprintf(reg_buff,"reg: %s %s \n",id,name);
	if( write(sockfd, reg_buff, strlen(reg_buff)) < 0)
    	{
    		cout<<"send reg error"<<endl;
    		exit(0);
   	 }
}

int main(int argc,char **argv)
{
	struct sockaddr_in    servaddr;
	struct sockaddr_in    clientaddr;
	char    buff;
	int n;
	b_reg.resize(5);
	cnt=0;
	ac_time=2;
	
	//freopen("test.txt","r",stdin);

	if( argc != 6)
	{
		cout<<endl<<"usage: ./client <s.ip><s.port><w.ip><w.port><id>"<<endl;
		exit(0);
	}
	/******************socket creat********************************/ 
	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout<<"create socket error"<<endl;
		exit(0);
	}
	/********************struct sockaddr_in  servaddr ***********************************************/
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port=htons(atoi(argv[2]));

	if(inet_aton(argv[1],&servaddr.sin_addr)==0)
	{
		cout<<"invalid server ip address"<<endl;
		exit(0);
	}
	
	/***********************struct sockaddr_in clientaddr************************************************************/
	memset(&clientaddr,0,sizeof(struct sockaddr_in));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(atoi(argv[4]));
   
	if(inet_aton(argv[3],&clientaddr.sin_addr) ==0)
	{
		cout<<"invalid client ipaddress"<<endl;
		exit(0);
	}
	/*****************************bind clientaddr and socket*************************************************************/
	if( bind(sockfd, (struct sockaddr*)&clientaddr, sizeof(struct sockaddr_in)) <0)
	{
		cout<<"bind socket error"<<endl;
		exit(0);
	}
	cout<<"bind ok"<<endl;
	/********************connect server*****************************************************/
	while(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr))<0);
	cout<<"connect ok "<<endl;
	/****************************creat  and send reg_msg*****************************************/
	reg_init("sky",*(argv+5));	
	/**********************************************************************************/
	
	while(1)
	{
		n = recv(sockfd,&buff, 1, 0);
		if(n > 0)
		{
			if(get_info(buff)==GAMEOVER)
				break;
		}

	}
	close(sockfd);
	return 0;
}
