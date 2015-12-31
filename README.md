# TcpClient

A Tcp "client" program thats downloads file from a web- server and shows  download time.

Notes:                                                                   
1) This program is developed using BSD socket. So, it can be run in Linux.					                      
2) This program can download a file from any Commercial Server and Weblite.				 

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
