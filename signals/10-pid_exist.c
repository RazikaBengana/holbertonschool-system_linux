#include <signal.h>

/**
 * pid_exist - program that checks if a process with a specified PID exists
 *
 * this function uses the kill system call to check process existence;
 * passing 0 as the signal number does not send any signal but performs
 * error checking, which can be used to check for the existence of a process
 *
 * @pid: the process ID to check
 *
 * Return: 1 if the process exists,
 *         0 if the process does not exist or an error occurs
 */

int pid_exist(pid_t pid)
{
	return (kill(pid, 0) + 1);
}
