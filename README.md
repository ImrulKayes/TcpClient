# TcpClient

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
