#ifndef SOCKET2_H
#define SOCKET2_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>


#define PORT 8080
#define BUF_SIZE 8192
#define CRLF "\r\n"
#define SP " \t"
#define BACKLOG 8

#define RESPONSE_200_NOCRLF "HTTP/1.1 200 OK"
#define RESPONSE_200 (RESPONSE_200_NOCRLF CRLF CRLF)
#define RESPONSE_201 "HTTP/1.1 201 Created"
#define RESPONSE_204 "HTTP/1.1 204 No Content\r\n\r\n"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define RESPONSE_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define RESPONSE_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_LENGTH "Content-Length"
#define URL_ENCODED "application/x-www-form-urlencoded"
#define JSON_TYPE "application/json"

#define PATH_TODOS "/todos"
#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_DELETE "DELETE"

#define KEY_ID "id"
#define KEY_TITLE "title"
#define KEY_DESCRIPTION "description"



/**
 * struct Todo - Structure for a task in a to-do list
 *
 * this structure holds the details of a to-do item and links
 * to the next item in the list, forming a singly linked list
 * of to-dos
 *
 * @id: the unique identifier for the current to-do item
 * @title: the title or summary of the current to-do item
 * @description: a detailed description of the current to-do item
 * @next: a pointer to the next to-do item in the linked list,
 *        or NULL if there is no next item
 */

typedef struct Todo
{
    int id;
    char *title;
    char *description;
    struct Todo *next;
} todo_t;



/* functions needed for task 4 to task 11 */

/* from server.c */
int start_server(void);
int accept_messages(int sd);
int send_response(int client_sd, char *response);
int parse_request(int client_sd, char *buf);

/* from trim.c */
char *trim(char *str);



#endif /* SOCKET2_H */
