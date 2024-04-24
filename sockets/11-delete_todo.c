#include "socket2.h"


static int ids;
static todo_t *todo_root;


int post_request(int client_sd, char *body, short content_length);
int get_request(int client_sd, short todo_id);
int delete_request(int client_sd, short todo_id);
void parse_path_and_todo_id(char **path, short *todo_id);


/**
 * main - the entry point that starts the server to handle incoming requests
 *
 * this program calls the start_server function and ignores the command line
 * arguments
 *
 * @ac: argument count
 * @av: argument values
 *
 * Return: the return value from start_server()
 */

int main(int ac, char **av)
{
	return (start_server());
	(void)ac;
	(void)av;
}



/**
 * parse_request - program that parses an HTTP request, identifies
 * the HTTP method, and routes the request to the appropriate function
 *
 * this function extracts the method, path, and body from the request
 * buffer, then depending on the method type it calls the respective
 * function to handle POST, GET, or DELETE requests
 *
 * @client_sd: the client socket descriptor
 * @buf: the buffer containing the received HTTP request
 *
 * Return: the integer status code of the operation
 */

int parse_request(int client_sd, char *buf)
{
	char *start_line, *method, *path, *header, *body, *key, *value,
		*save_ptr1, *save_ptr2;
	short content_length = 0, todo_id = -1;

	body = strstr(buf, CRLF CRLF);

	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start_line = strtok_r(buf, CRLF, &save_ptr1);
	method = strtok(start_line, SP);
	path = strtok(NULL, SP);
	parse_path_and_todo_id(&path, &todo_id);
	printf("Path: [%s] Todo:[%d] Method:[%s]\n", path, todo_id, method);

	if (strcasecmp(path, PATH_TODOS) || (strcasecmp(method, METHOD_POST) &&
					     strcasecmp(method, METHOD_GET) && strcasecmp(method, METHOD_DELETE)))
		return (send_response(client_sd, RESPONSE_404));

	header = strtok_r(NULL, CRLF, &save_ptr1);

	while (header)
	{
		key = trim(strtok_r(header, ":", &save_ptr2));
		value = trim(strtok_r(NULL, CRLF, &save_ptr2));

		if (!strcasecmp(key, CONTENT_LENGTH))
			content_length = atoi(value);
		header = strtok_r(NULL, CRLF, &save_ptr1);
	}
	if (!strcasecmp(method, METHOD_POST))
	{
		if (!content_length)
			return (send_response(client_sd, RESPONSE_411));
		post_request(client_sd, body, content_length);
	}
	else if (!strcasecmp(method, METHOD_GET))
		get_request(client_sd, todo_id);

	else if (!strcasecmp(method, METHOD_DELETE))
		delete_request(client_sd, todo_id);

	return (0);
}



/**
 * post_request - program that handles POST requests by creating
 * a new TODO item from the request body and adds it to the todo list
 *
 * @client_sd: the client socket descriptor
 * @body: the request body containing todo item details
 * @content_length: the length of the request body
 *
 * Return: 1 on failure, or the response code on success
 */

int post_request(int client_sd, char *body, short content_length)
{
	char *query, *key, *value, *save_ptr1, *save_ptr2,
		*title = NULL, *description = NULL;
	char buf1[1024] = {0}, buf2[1024] = {0};
	todo_t *todo, *node;

	body[content_length] = 0;
	query = strtok_r(body, "&", &save_ptr1);

	while (query)
	{
		key = strtok_r(query, "=", &save_ptr2);
		value = strtok_r(NULL, "=", &save_ptr2);
		printf("Body param: \"%s\" -> \"%s\"\n", key, value);

		if (!strcasecmp(key, KEY_TITLE))
			title = value;
		else if (!strcasecmp(key, KEY_DESCRIPTION))
			description = value;
		query = strtok_r(NULL, "&", &save_ptr1);
	}
	if (!title || !description)
		return (send_response(client_sd, RESPONSE_422));

	todo = calloc(1, sizeof(*todo));

	if (!todo)
		return (1);

	todo->id = ids++;
	todo->title = strdup(title);
	todo->description = strdup(description);

	if (!todo_root)
		todo_root = todo;
	else
	{
		node = todo_root;
		while (node->next)
			node = node->next;
		node->next = todo;
	}
	sprintf(buf2, "{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
	KEY_DESCRIPTION "\":\"%s\"}", ids - 1, title, description);
	sprintf(buf1, RESPONSE_201 CRLF CONTENT_LENGTH ": %lu" CRLF
	CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s", strlen(buf2), buf2);

	return (send_response(client_sd, buf1));
}



/**
 * get_request - program that handles GET requests to retrieve
 * a specific todo item or all items if no ID is specified
 *
 * @client_sd: the client socket descriptor
 * @todo_id: the ID of the todo item to retrieve;
 *           -1 to retrieve all
 *
 * Return: the response code from sending the todo data
 */

int get_request(int client_sd, short todo_id)
{
	char buf1[BUF_SIZE + 1] = {0}, buf2[BUF_SIZE + 1] = {0};
	todo_t *todo = NULL;

	if (todo_id != -1)
	{
		for (todo = todo_root; todo; todo = todo->next)
			if (todo->id == todo_id)
				break;
		if (!todo)
			return (send_response(client_sd, RESPONSE_404));

		sprintf(buf2 + strlen(buf2),
			"{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
		KEY_DESCRIPTION "\":\"%s\"}", todo->id, todo->title,
			todo->description);
	}
	else
	{
		buf2[0] = '[';

		for (todo = todo_root; todo; todo = todo->next)
			sprintf(buf2 + strlen(buf2),
				"{\"" KEY_ID "\":%d,\"" KEY_TITLE "\":\"%s\",\""
		KEY_DESCRIPTION "\":\"%s\"}%s", todo->id, todo->title,
			todo->description, todo->next ? "," : "");
		*(buf2 + strlen(buf2)) = ']';
	}
	sprintf(buf1, RESPONSE_200_NOCRLF CRLF CONTENT_LENGTH ": %lu" CRLF
	CONTENT_TYPE ": " JSON_TYPE CRLF CRLF "%s", strlen(buf2), buf2);

	return (send_response(client_sd, buf1));
}



/**
 * delete_request - program that handles DELETE requests to remove
 * a specific todo item identified by todo_id from the list
 *
 * @client_sd: the client socket descriptor
 * @todo_id: the ID of the todo item to delete
 *
 * Return: the response code after attempting to delete the item
 */

int delete_request(int client_sd, short todo_id)
{
	todo_t *todo = NULL, *prev = NULL;

	if (todo_id == -1)
		return (send_response(client_sd, RESPONSE_422));

	for (todo = todo_root; todo; prev = todo, todo = todo->next)
		if (todo->id == todo_id)
			break;

	if (!todo)
		return (send_response(client_sd, RESPONSE_404));

	if (prev)
		prev->next = todo->next;
	else
		todo_root = todo->next;

	free(todo);

	return (send_response(client_sd, RESPONSE_204));
}



/**
 * parse_path_and_todo_id - program that parses the request URL
 * to extract the path and TODO ID
 *
 * @path: the URL path, modified in-place to strip query parameters
 * @todo_id: a pointer to store the extracted todo ID;
 *           set to -1 if none found
 *
 * Return: nothing (void)
 */

void parse_path_and_todo_id(char **path, short *todo_id)
{
	char *todo_str;

	*path = strtok(*path, "?");
	todo_str = strtok(NULL, SP);

	if (todo_str)
	{
		if (!strcasecmp(strtok(todo_str, "="), KEY_ID))
			*todo_id = atoi(strtok(NULL, "="));
	}
}