Christopher Nelson
Christopher.w.nelso@email.wsu.edu
CS360
Assignment9

Description:
dayserve is a server that logs the hostname of the client to stdout and writes the current date and time to the client via a socket connection. daytime is a client program that takes an argument from the commandline to create a connection to the indicated host. It then writes the information from dayserve to stdout.

How to run:
Type 'make' to compile the c files
Type './dayserve' to run the server.
Type './daytime hostname', where hostname is the hostname of the computer 
that the server is running on, to run the client.
