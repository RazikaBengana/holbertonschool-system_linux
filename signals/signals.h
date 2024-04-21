#ifndef SIGNALS_H
#define SIGNALS_H


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


typedef void (*sighandler_t)(int);


/* task 0 */
void sigint_handler(int signum);
int handle_signal(void);

/* task 1 */
void (*current_handler_signal(void))(int);

/* task 2 */
void sigint_handler2(int signum);
int handle_sigaction(void);

/* task 3 */
void (*current_handler_sigaction(void))(int);

/* task 4 */
void sigquit_handler(int signum, siginfo_t *si, void *ucontext);
int trace_signal_sender(void);

/* task 6 */
void sigint_handler3(int signum);

/* task 10 */
int pid_exist(pid_t pid);



/* advanced tasks */

/* task 100 */
void all_signal_handler(int signum, siginfo_t *si, void *ucontext);
void all_in_one(void);

/* task 101 */
int sigset_init(sigset_t *set, int *signals);

/* task 102 */
int sigset_init2(sigset_t *set, int *signals);
int signals_block(int *signals);

/* task 103 */
int sigset_init3(sigset_t *set, int *signals);
int signals_unblock(int *signals);

/* task 104 */
int handle_pending(void (*handler)(int));



#endif /* SIGNALS_H */
