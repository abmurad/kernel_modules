  #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>

//       int inet_aton(const char *cp, struct in_addr *inp);
int main  ( void )
{

	struct in_addr inp ;
	
	inet_aton ( "172.16.9.21" , &inp) ;

	printf("%u\n" , (inp . s_addr));

}

