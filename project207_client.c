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
#include <fcntl.h>
#include <mysql/mysql.h>
#include <termios.h>
#include <semaphore.h>
#define BUFSIZE 64

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif
//sem_t mutex;
static char *host = "localhost";//local server name
static char *user = "root"; //username of mysql server
static char *pass =  "Sachinsp14!";
static char *dbname = "test_sachin";
unsigned int port = 3306; 
static char *unix_socket = NULL; // specify the connection type
unsigned int flag = 0; //ODBC connection

extern int errno;

int errexit(const char *format,...);
int connectTCP(const int port,const char *host);
int connectsock(const int port,const char *host,const char *transport);

int main(int argc,char *argv[])
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

  char *host = "127.0.0.1";
  double result;
  int port = 8000;
  int sock,n;

  switch(argc)
  {
    case 1:
    host="localhost";
    break;

    default:printf("Error in reading arguments\n");
    exit(1);
  }

  /* Establishes connectivity with the server by choosing TCP protocol. Returns a positive Integer on connecting. */

  sock=connectTCP(port,host);
  /* On establishing the connection, the integer stored in number is sent to the server who's length is the length of number+1 */
  
  char username[100];
  char password[100];
  char rpassword[100];
  char email[100];
  int  f;
  //ssize_t sent_bytes,rcvd_bytes;
  char type[2000];
  char message[500];
  char flag[10];
  jump:
  do
  { 
    //start:    
    system("clear");
    printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
    printf("a. Login | b. Sign Up\n");
    printf("Enter your option\n");
    char input[10];
    ssize_t sent_bytes;
  
    scanf("%s", input);
    char str[50];
    if(!(strcmp(input,"a")))
    { 
      system("clear");
      printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
      printf("\t\t\t\t\t\t\tLogin\n\n");

      printf("Enter the Username\n");   
      scanf("%s", username);

      printf("Enter the Password\n");
        struct termios term, term_orig;
          tcgetattr(STDIN_FILENO, &term);
          term_orig = term;
          term.c_lflag &= ~ECHO;
          tcsetattr(STDIN_FILENO, TCSANOW, &term);
          scanf("%s", password);
          tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);     
      sprintf(message,"%s %s",username,password);
      //printf("%d",sock);
      //printf("%s",message);
      if((sent_bytes = send(sock,message,20000,0))<0)
      {
        printf("%d",sent_bytes);
          printf("send error\n");
        exit(0);
      }
      sprintf(flag,"done");   
    }
    else if(!(strcmp(input,"b")))
    {     
      system("clear");
      printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
      printf("\t\t\t\t\t\t\tNew User Registration\n\n");

      printf("Enter Username:\n");
      scanf("%s",username);

      sprintf(str,"select * from Login_Details where Username = '%s'",username);
      mysql_query(conn, str); 
      res = mysql_store_result(conn); 

      if(row = mysql_fetch_row(res))
      {
        printf("Username already exists\nTry a different username\n");
        sprintf(flag,"do");
        continue;
      }
      
      printf("Enter Password:\n");            
          struct termios term, term_orig;
          tcgetattr(STDIN_FILENO, &term);
          term_orig = term;
          term.c_lflag &= ~ECHO;
          tcsetattr(STDIN_FILENO, TCSANOW, &term);
          scanf("%s", password);
          tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
      printf("\n");

      printf("Re-enter Password:\n");                   
          tcgetattr(STDIN_FILENO, &term);
          term_orig = term;
          term.c_lflag &= ~ECHO;
          tcsetattr(STDIN_FILENO, TCSANOW, &term);
          scanf("%s", password);
          tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
      printf("\n");

      if(!(strcmp(password,rpassword)))
      {
        printf("Passwords do not match\nPlease try again");
        sprintf(flag,"do");
        continue;
      }
      else
      {
        printf("Enter your email id:\n");
        scanf("%s",email);        
                      
        sprintf(str,"insert into Login_Details values ('%s', AES_ENCRYPT('%s','sanjose123'), '%s', 'Customer')", username, password, email);
        mysql_query(conn, str);
        res = mysql_store_result(conn);           
      }
    }
    else
    {
      printf("Enter a valid operation\n");
      sprintf(flag,"do");
      continue;
    }
  }while(strcmp(flag,"done"));
  ssize_t rcvd_bytes;
  while((rcvd_bytes = recv(sock,type,2000,0))>0)
  { 
    //------------------------------Admin-------------------------------------//
    if(!(strcmp(type,"admin")))
    {
      while(1)
      {
      jump1:
        system("clear");
        printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);

        char flight_num[50];
        char email[50];
        char str[50];
        char input[50];
        char username1[50];
        char password[50];
        printf("\n\nOperations\n\na. Add Airline Representative\nb. Delete Airline Representative  \nc. View Flight Details \nd. View Booking Details \ne. Logout \n\n");
        printf("Enter the operation you want to perform\n");
        scanf("%s",input);
        if(!(strcmp(input,"a")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\tNew Airline Representative Registration\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);

          printf("Enter Username:\n");
          scanf("%s",username1);
          printf("\n");

          sprintf(str,"select * from Login_Details where Username = '%s'",username1);
          mysql_query(conn, str); 
          res = mysql_store_result(conn); 

          if(row = mysql_fetch_row(res))
          {
            printf("Ailine Representative already exists\n");
            continue;
          }

          printf("Enter Password:\n");
          struct termios term, term_orig;         
              tcgetattr(STDIN_FILENO, &term);
              term_orig = term;
              term.c_lflag &= ~ECHO;
              tcsetattr(STDIN_FILENO, TCSANOW, &term);
          scanf("%s",password);
              tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
          printf("\n");

          printf("Enter email id:\n");
          scanf("%s",email);
          printf("\n");

          sprintf(str,"insert into Login_Details values ('%s', AES_ENCRYPT('%s','sanjose123'), '%s', 'Airlines')", username1, password, email);
          mysql_query(conn, str);
          res = mysql_store_result(conn);

          printf("\nAirline Representative Successfully added\n\n");

          /*sprintf(str,"select * from Login_Details where Type = 'Airlines'");
          mysql_query(conn, str);
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tAirline Representative Details\n\n");
          printf("Username\tPassword\tEmail\tType\n\n");
          while(row = mysql_fetch_row(res))
          {
            printf("%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3]);
          }
          mysql_free_result(res);*/

          printf("a. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump1; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"b")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tAirline Representative Termination\n\n");

          sprintf(str,"select * from Login_Details where Type = 'Airlines'");
          mysql_query(conn, str);
          res = mysql_store_result(conn);
          printf("\t\t\t\tAirline Representative Details\n\n");
          printf("Username\tEmail\tType\n\n");
          while(row = mysql_fetch_row(res))
          {
            printf("%s\t%s\t%s\n",row[0],row[2],row[3]);
          }
          mysql_free_result(res);

          printf("Enter the username of the Airline Represenative you want to delete:\n");
          scanf("%s",username1);

          sprintf(str,"delete from Login_Details where Username = '%s'", username1);
          mysql_query(conn, str);
          res = mysql_store_result(conn);

          printf("\n\nAirline Representative Successfully deleted\n\n");
          printf("a. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump1; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"c")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tFlight Details\n\n");

          sprintf(str,"select * from Flight_Details");
          mysql_query(conn, str); 
          res = mysql_store_result(conn);
          
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res); 

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump1; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }       
        }
        else if(!(strcmp(input,"d")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tBooking Details Details\n\n");

          sprintf(str,"select * from Booking_Details");
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("Username  Passenger Name  Flight Number    Date      Departure City  Departure Time  Arrival City  Arrival time  Seats  Total Price  Booking Status\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t  %s\t  %s\t\t %s       %s\t\t%s\t%s\t     %s\t  %s\t  %s\t       %s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[10],row[11]); 
          }
          mysql_free_result(res);

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump1; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"e")))
        {
          printf("Signing out\n");
          break;
        }
        else
        {
          printf("Invalid operation\n");
          continue;
        }
      }
    }
    //------------------------------Airlines-------------------------------------//     
    else if(!(strcmp(type,"Airlines")))
    {   
      printf("Logged in Successfully\n\n");
      while(1)
      { 
      jump2:
        system("clear");
        printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);

        char flight_num[10];
        char flight_name[10];
        char dept_city[10], dept_city1[10], dept_city2[10];
        char dept_time[10];
        char arrival_city[10], arrival_city1[10], arrival_city2[10];
        char arrival_time[10];
        char seats[10];
        char date[10];
        char price[10];
        char input[10];
        char str[500];

        printf("Airline Operations\n\na. View Flight Details\nb. View Booking Details\nc. Add Flight\nd. Reschedule Flight\ne. Cancel Flight\nf.Sign out\n\n");
        
        printf("Enter the operation you want to perform\n");
        scanf("%s",input);
        
        if(!(strcmp(input,"a")))
        { 
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tFlight Details\n\n");
        
          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);
          
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res); 

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump2; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          } 
        }
        else if(!(strcmp(input,"b")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tBooking Details\n\n");
          
          sprintf(str,"select * from Booking_Details where Flight_Name = '%s'",username);

          mysql_query(conn, str); 
          res = mysql_store_result(conn);
          
          printf("Username  Passenger Name  Flight Number    Date      Departure City  Departure Time  Arrival City  Arrival time  Seats  Total Price  Booking Status\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t  %s\t  %s\t\t %s       %s\t\t%s\t%s\t     %s\t  %s\t  %s\t       %s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[10],row[11]); 
          }
          mysql_free_result(res);

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump2; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"c")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tAdd Flight\n\n");

          printf("Enter the details of the flight you want to add\n");
          printf("Flight Number : ");         
          scanf("%s",flight_num);

          printf("Flight Name : ");         
          scanf("%s",flight_name);

          printf("Departure City : ");          
          scanf("%s",dept_city);          

          printf("Departure Time (hh:mm:ss) : ");
          scanf("%s",dept_time);

          printf("Arrival City : ");
          scanf("%s", arrival_city);          

          printf("Arrival Time (hh:mm:ss) : ");
          scanf("%s",arrival_time);

          printf("Date(mm/dd/yyyy) : ");
          scanf("%s",date);

          printf("No of Seats : ");
          scanf("%s",seats);  

          printf("Price (in USD) : ");
          scanf("%s",price);
      
          sprintf(str,"insert into Flight_Details values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", username, flight_num, flight_name, dept_city, dept_time, arrival_city, arrival_time, date, seats, price);        
          mysql_query(conn, str);           
          res = mysql_store_result(conn);

          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res); 

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump2; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }       
        }
        else if(!(strcmp(input,"d")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tReschedule Flight\n\n");

          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res);
    
          printf("Enter the Flight Number you want to reschedule : ");
          scanf("%s",flight_num);

          printf("Departure Time (hh:mm:ss) : ");
          scanf("%s",dept_time);

          printf("Arrival Time (hh:mm:ss) : ");
          scanf("%s",arrival_time);

          printf("Date(mm/dd/yyyy) : ");
          scanf("%s",date);

          printf("No of Seats : ");
          scanf("%s",seats);
  
          printf("Price (in USD) : ");
          scanf("%s",price);
      
          sprintf(str,"update Flight_Details set Departure_Time = '%s', Arrival_Time = '%s', Date = '%s', Seats_Available = '%s', Price_USD = '%s' where Flight_Number = '%s'",dept_time,arrival_time, date, seats, price, flight_num);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res);

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump2; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"e")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\tCancel Flight\n\n");

          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          
          mysql_free_result(res);

          printf("Enter the flight number you want to cancel : ");
          scanf("%s",flight_num); 

          printf("Enter the Date(mm/dd/yyyy) on which you want to cancel");
          scanf("%s",date);
        
          sprintf(str,"delete from Flight_Details where Flight_Number = '%s' and Date = '%s'", flight_num, date);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          sprintf(str,"select * from Flight_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }         
          mysql_free_result(res);

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump2; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }
        }
        else if(!(strcmp(input,"f")))
        {
          printf("Signing out\n");
          break;
        }
        
        else
        {
          printf("Enter a valid operation\n");
          continue;
        }
      } 
    }
    //---------------------------Customer----------------------------------------//
    else if(!(strcmp(type,"Customer")))
    {       
      while(1)
      {
      jump3:
        system("clear");
        printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);

        char flight_num[50];
        char seats[50];
        char str[50];
        char input[50];
        char dept_city[50];
        char arrival_city[50];
        char date[50];
        char name[50];

        printf("Operations\na. Book Tickets \nb. Cancel ticket \nc. View Booking History\nd. Sign out \n\n");
        printf("Enter the operation you want to perform\n");
        scanf("%s",input);
        
        if(!(strcmp(input,"a")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\tBook Flight\n\n");

          int temp=0, temp1=0;
          printf("Enter the Departure City: \n");
          scanf("%s",dept_city);

          printf("Enter the Arrival City: \n");
          scanf("%s",arrival_city);

          printf("Travel Date(mm/dd/yyyy): \n");
          scanf("%s",date);

          sprintf(str,"select * from Flight_Details where Departure_City = '%s' and Arrival_City = '%s' and Date = '%s'", dept_city, arrival_city, date);                   
          mysql_query(conn, str);
          res = mysql_store_result(conn);

          printf("\n\n\t\t\t\t\t\tFlight Details\n\n");
          printf("Flight Number\tFlight Name\tDeparture City\tDeparture Time\tArrival City\tArrival time\tDate\t\tSeats Available\tPrice(USD)\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\n", row[1],row[2],row[3],row[4],row[5], row[6],row[7],row[8],row[9]);  
          }
          mysql_free_result(res);

          printf("Enter the flight details of the flight you want to book\n");
          printf("Enter your name : ");
          scanf("%s",name);
          printf("Flight Number : ");
          scanf("%s",flight_num);
          printf("No of Tickets you want to book on that flight: ");
          scanf("%s",seats);
          
          sprintf(str,"select * from Flight_Details where Flight_Number = '%s'",flight_num);
          mysql_query(conn, str);
          res = mysql_store_result(conn);
          row = mysql_fetch_row(res);
          
          temp =atoi(row[8]);
                  
          int se= atoi(seats);
          temp1 = temp-se;
        
          sprintf(str,"update Flight_Details set Seats_Available = %d where Flight_Number='%s'",temp1, flight_num);         
          mysql_query(conn, str);
          res = mysql_store_result(conn);
          sprintf(str,"select * from Flight_Details where Flight_Number='%s'",flight_num);
          mysql_query(conn, str);
          res = mysql_store_result(conn);               
          row = mysql_fetch_row(res);
                    
          int price = atoi(row[9]);
          int total = price*se;           
          sprintf(str,"insert into Booking_Details values ('%s','%s','%s','%s','%s','%s','%s','%s',%d,%d,%d,'Booked','%s')",username, name, flight_num, row[7],row[3],row[4],row[5],row[6],se, price, total,row[2] );
          mysql_query(conn, str);
          res = mysql_store_result(conn);           
          printf("\nYour Ticket has been booked. ");

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump3; 
          }
          else if(!(strcmp(in,"b")))
          {
            break; //goto start;
          }       
        }
        else if(!(strcmp(input,"b")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\t\tCancel Flight\n\n");

          int temp=0,temp1=0;
          printf("Enter the flight details of the flight you want to Cancel\n");
          printf("Flight Number : ");
          scanf("%s",flight_num);
          printf("Enter your name : ");
          scanf("%s",name);         
                    printf("No of Tickets you want to cancel on that flight: ");
          scanf("%s",seats);
          sprintf(str,"select * from Flight_Details where Flight_Number = '%s'",flight_num);
          mysql_query(conn, str);
          res = mysql_store_result(conn);
          while(row = mysql_fetch_row(res))
          {
            temp =atoi(row[8]);         
          }
          int se= atoi(seats);
          temp1 = temp+se;          
          sprintf(str,"update Flight_Details set Seats_Available = %d where Flight_Number='%s'",temp1, flight_num);
          mysql_query(conn, str);
          res = mysql_store_result(conn);
          printf("\nYour Ticket has been Cancelled.");
        
          sprintf(str,"select * from Flight_Details where Flight_Number='%s'",flight_num);    
          mysql_query(conn, str);
          res = mysql_store_result(conn);               
          row = mysql_fetch_row(res);
                    
          int price = atoi(row[9]);
          int total = price*se;         
          sprintf(str,"insert into Booking_Details values ('%s','%s','%s','%s','%s','%s','%s','%s',%d,%d,%d,'Cancelled','%s')",username, name, flight_num, row[7],row[3],row[4],row[5],row[6],se, price, total, row[2]);
          
          mysql_query(conn, str);
          res = mysql_store_result(conn); 

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump3; 
          }
          else if(!(strcmp(in,"b")))
          {
            break;//goto start;
          } 
        }
        else if(!(strcmp(input,"c")))
        {
          system("clear");
          printf("\t\t\t\t\t\tWelcome to Airline Reservation System\n");
          printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWelcome %s\n\n",username);
          printf("\t\t\t\t\t\t\t\tBooking Details\n\n");

          sprintf(str,"select * from Booking_Details where Username = '%s'",username);
          mysql_query(conn, str); 
          res = mysql_store_result(conn);
          
          printf("Username  Passenger Name  Flight Number    Date      Departure City  Departure Time  Arrival City  Arrival time  Seats  Total Price  Booking Status\n\n");
          while(row = mysql_fetch_row(res))
          {                   
            printf("%s\t  %s\t  %s\t\t %s       %s\t\t%s\t%s\t     %s\t  %s\t  %s\t       %s\n", row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[10],row[11]); 
          }
          mysql_free_result(res);

          printf("\n\na. Home Page | b. Sign out\n");
          printf("Enter your option\n");
          char in[50];
          scanf("%s",in);
          if(!(strcmp(in,"a")))
          {
            goto jump3; 
          }
          else if(!(strcmp(in,"b")))
          {
            break;
            //goto start;
          }           
        }
        else if(!(strcmp(input,"d")))
        {
          printf("Signing out\n");
          break;
        }
        else
        {
          printf("Invalid Operation\n");
          continue;
        }
      }
    } 
    else
    {
      printf("%s\n",type);        
    }
  }
//goto start;
}

/* connectsock - allocate & connect a socket using TCP or UDP */

int connectTCP(const int port,const char *host)
{
  return connectsock(port,host,"tcp");
}

/*
* Arguments:
* host - name of host to which connection is desired
* service - service associated with the desired port
* transport - name of transport protocol to use ("tcp" or "udp")
*/

int connectsock(const int port,const char *host,const char *transport)
{
  struct sockaddr_in6 sin;
  int sock,type;

  memset(&sin,0,sizeof(sin));
  sin.sin6_flowinfo = 0;
  sin.sin6_family = AF_INET6; 
  sin.sin6_port=htons(port);

  inet_pton(AF_INET6,host,&(sin.sin6_addr));

  /* Use protocol to choose a socket type */

  if(strcmp(transport,"udp")==0)
  type=SOCK_DGRAM;
  else
  type=SOCK_STREAM;

  /* Allocate a socket */

  sock=socket(AF_INET6,type,0);

  if(sock<0)
  errexit("Error in creating socket : %s\n",strerror(errno));

  /* Connect the socket */

  if((connect(sock,(struct sockaddr *) &sin,sizeof(sin)))<0)
  errexit("Error in connection %s.%s: %s\n",host,port,strerror(errno));

  return sock;
}

int errexit(const char* format,...)
{
  va_list args;

  va_start(args,format);
  vfprintf(stderr,format,args);
  va_end(args);
  exit(1);
}

