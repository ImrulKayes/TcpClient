//==================================================== file = tcpClient.c =====
//=  A "client" program thats downloads file from a web- server and shows     =	
//=  download time.
//=============================================================================
//=  Notes:                                                                   =
//=    1) This program is developed using BSD socket. So, it can be run in    =
//=       Linux.					                      =
//=    2) This program can download a file from any Commercial Server         =
//=       and Weblite.				                              =
//=    3) This program hardwires the host name www.web.csee.usf.edu for       =
//=	  commercial web-server(Apache) and www.netcluster.csee.usf.edu for   =
//=       Weblite. #define GET_STRING  hardwires the GET request string into  =
//=       into GET_STRING.                           
//=    4) Use Weblite on the place of Webserver in the statement              =
//=       #define Webserver to download a file from Weblite, given that       =
//=       Weblite should be running before execution this program.            =
//=       For any commercial web server keep the statement as it is.          =
//=---------------------------------------------------------------------------=
//=  Example execution:                                                       =
//=	   Looking for IP address for 'web.csee.usf.edu'...                   =
//=        IP address for 'web.csee.usf.edu' is 131.247.3.9.                  =
//=                                                                           =
//=        Time took   0.003 sec to Resolve IP address.                       =
//=        Time took   0.050 sec to establish connection.                     =
//=        Time took   0.061 sec to get the first byte data.                  =
//=        Time took   2.726 sec to get the full file.                        =
//=        Time took   2.840 sec to the whole download process.               =

//=---------------------------------------------------------------------------=
//=  Build: gcc tcpClient.c -lnsl -o tcpClient                                =
//=---------------------------------------------------------------------------=
//=  Execute: tcpClient                                                       =
//=---------------------------------------------------------------------------=
//=  Author: Imrul Kayes                                                      =
//=          University of South Florida                                      =
//=          Email: imrul@mail.usf.edu                                        =
//=---------------------------------------------------------------------------=
//=  Acknowledgement:  This program uses some code snippets origianlly        =
//=            developed by Ken Christensen,christen@csee.usf.edu             =
//=============================================================================


//----- Include files ---------------------------------------------------------
#include <stdio.h>        // Needed for printf()
#include <string.h>       // Needed for memcpy() and strcpy()  
#include <sys/time.h>     // Needned for time stuff
#include <sys/timeb.h>    // Needned for time stuff
#include <sys/types.h>    // Needed for sockets stuff
#include <netinet/in.h>   // Needed for sockets stuff
#include <sys/socket.h>   // Needed for sockets stuff
#include <arpa/inet.h>    // Needed for sockets stuff
#include <fcntl.h>        // Needed for sockets stuff
#include <netdb.h>        // Needed for sockets stuff

#define Webserver

#ifdef Webserver
#define  PORT_NUM              80     // Web servers are at port 80
#define HOST_NAME "web.csee.usf.edu"  // Host name of web server
#define  GET_STRING "GET /~imrul/500KB.html HTTP/1.0\n\n"  // GET string
#endif

#ifdef Weblite
#define  PORT_NUM              8080     // Weblite at Web at port 80
#define  HOST_NAME "netcluster.csee.usf.edu"  // Host name of web server
#define  GET_STRING "GET /500KB.html HTTP/1.0\n\n"  // GET string
#endif

#define BUF_SIZE 4096   // Buffer size of Client

//===== Main program ==========================================================
void main(void)
{

  int                  client_s;        // Client socket descriptor            
  struct sockaddr_in   server_addr;     // Server Internet address
  char                 out_buf[BUF_SIZE];   // Output buffer for data
  char                 in_buf[BUF_SIZE];    // Input buffer for data
  int                  retcode;         // Return code


  struct hostent *host;            // Structure for gethostbyname()
  struct in_addr  address;         // Structure for Internet address
  char            host_name[256];  // String for host name
  char            host_ip[256];    // Host IP address



  struct timeb start, stop; // Start and stop times structures
  double       elapsed;     // Elapsed time in seconds
  double total_downloadtime=0; // For tracking total download time

  ftime(&start);  // Start timer to to get the DNS resolve time 
  printf("  Looking for IP address for '%s'... \n", HOST_NAME);
  host = gethostbyname(HOST_NAME);

  // Output address if host found
  if (host == NULL)
    printf("  IP address for '%s' could not be found \n", host_name);
  else
  {
    memcpy(&address, host->h_addr, 4);
    strcpy(host_ip, (char *) inet_ntoa(address));
    printf("  IP address for '%s' is %s.\n", HOST_NAME,host_ip);
  }
  ftime(&stop);
  elapsed=((double) stop.time + ((double) stop.millitm * 0.001)) -
          ((double) start.time + ((double) start.millitm * 0.001));
  printf("\n  Time took %7.3f sec to Resolve IP address.",elapsed);
  total_downloadtime=total_downloadtime+elapsed;  // Add resolving time to total download time

  
  // >>> Step #1 <<<
  // Create a client socket
  //   - AF_INET is Address Family Internet and SOCK_STREAM is streams
  client_s = socket(AF_INET, SOCK_STREAM, 0);
 
  if (client_s < 0)
  {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
  }
  
  // >>> Step #2 <<<
  // Fill-in the server's address information and do a connect with the
  // listening server using the client socket - the connect() will block.
  server_addr.sin_family = AF_INET;                 // Address family to use
  server_addr.sin_port = htons(PORT_NUM);           // Port num to use
  server_addr.sin_addr.s_addr = inet_addr(host_ip); // IP address to use
 
  
  ftime(&start);  // Start timer to to get the connection establishment time

  retcode = connect(client_s, (struct sockaddr *)&server_addr,
  sizeof(server_addr));
  if (retcode < 0)
  {
    printf("*** ERROR - connect() failed\n");
    exit(-1);
  }
  ftime(&stop);
  elapsed=((double) stop.time + ((double) stop.millitm * 0.001)) -
          ((double) start.time + ((double) start.millitm * 0.001));
  printf("\n  Time took %7.3f sec to establish connection.",elapsed);
  total_downloadtime=total_downloadtime+elapsed; // Add connection establishment time to total download time

 
  // Send a GET to the Web server
  strcpy(out_buf,GET_STRING);
  ftime(&start); // Start timer to to get the time to get first byte data 
  retcode = send(client_s, out_buf, (strlen(out_buf) + 1), 0);
  if (retcode < 0)
  {
    printf("*** ERROR - send() failed \n");
    exit(-1);
  }

  // >>> Step #3 <<<
  // Receive from the server using the client socket
  // The recv function receives data from a connected socket or a bound connectionless socket.
  
  retcode = recv(client_s, in_buf, BUF_SIZE+1, 0); 
  
  ftime(&stop); 
  elapsed=((double) stop.time + ((double) stop.millitm * 0.001)) -
          ((double) start.time + ((double) start.millitm * 0.001));
  printf("\n  Time took %7.3f sec to get the first byte data.",elapsed);
  total_downloadtime=total_downloadtime+elapsed;

  ftime(&start); // Start timer to get the time of full file download
  while((retcode > 0) || (retcode == -1)){
	retcode = recv(client_s, in_buf, BUF_SIZE+1, 0);
	if(strlen(in_buf)==0){
		break;
	}

	if (retcode < 0)
		{
			printf("*** ERROR - recv() failed \n");
			break;
		}

  }


  ftime(&stop);
  elapsed=((double) stop.time + ((double) stop.millitm * 0.001)) -
          ((double) start.time + ((double) start.millitm * 0.001));
  printf("\n  Time took %7.3f sec to get the full file.",elapsed); 
  total_downloadtime=total_downloadtime+elapsed;
  printf("\n  Time took %7.3f sec to the whole download process.\n",total_downloadtime); 


  // >>> Step #4 <<<
  // Send to the server using the client socket
  strcpy(out_buf, "Message: Closing Connection");
  retcode = send(client_s, out_buf, (strlen(out_buf) + 1), 0);
  if (retcode < 0)
  {
    printf("*** ERROR - send() failed \n");
    exit(-1);
  }

  // >>> Step #5 <<<
  // Close the client socket

  retcode = close(client_s);
  if (retcode < 0)
  {
    printf("*** ERROR - close() failed \n");
    exit(-1);
  }
}
