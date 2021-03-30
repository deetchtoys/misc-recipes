#include "TestRunner.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>

using std::cout;
using std::endl;
using std::string;

void print_exit(int status)
{
    if (WIFEXITED(status))
        cout << "normal termination, exit status:" << WEXITSTATUS(status) << endl;
    else if (WIFSIGNALED(status))
    {
        cout << "abnormal termination, signal number:" << WTERMSIG(status);
#ifdef WCOREDUMP
        cout << (WCOREDUMP(status) ? "(core file generated)" : "") << endl;
#endif
    }
    else if (WIFSTOPPED(status))
    {
        cout << "child stopped, signal number = %d" << WSTOPSIG(status) << endl;
    }

}

int globvar = 6;
char buf[] = "a write to stdout\n";

int forkTest(int argc, char **argv, TestRunner *self)
{
    int var = 88;
    pid_t pid;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        self->printErrMsg(ERROR_PREFIX);

    if ((pid = fork()) < 0)
        self->printErrMsg(ERROR_PREFIX);
    else if(pid == 0)
    {
        globvar++;
        var++;
    }
    else
    {
        sleep(5);
    }

    cout << "pid :" << getpid() << "; glob:" << globvar << "; var:" << var << endl;

    return 0;
}

int waitTest(int argc, char **argv, TestRunner *self)
{
    pid_t pid;
    int status;
    //exit(7)
    if ( (pid = fork()) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }
    else if (pid == 0)
    {
        exit(7);
    }

    if (wait(&status) != pid)
    {
        self->printErrMsg(ERROR_PREFIX);
    }

    print_exit(status);


    //abort
    if ( (pid = fork()) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }
    else if (pid == 0)
    {
        abort();
    }

    if (wait(&status) != pid)
    {
        self->printErrMsg(ERROR_PREFIX);
    }

    print_exit(status);

    //SIGFPE
    if ( (pid = fork()) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }
    else if (pid == 0)
    {
        status /= 0;
    }

    if (wait(&status) != pid)
    {
        self->printErrMsg(ERROR_PREFIX);
    }

    print_exit(status);

    return 0;
}

int avoidZombie(int argc, char **argv, TestRunner *self)
{
    pid_t pid;
    if ((pid = fork()) < 0)
        self->printErrMsg(ERROR_PREFIX);
    else if (pid == 0)
    {
        if ((pid = fork()) < 0)
        {
            self->printErrMsg(ERROR_PREFIX);
        }
        else if (pid > 0)
        {
            //child
            cout << "child pid = " << getpid() << endl;
            exit(0);
        }

        //child child
        sleep(2);
        cout << "child child, parent pid = " << getppid() << endl;
        exit(0);
    }

    //father
    sleep(5);
    cout << wait(NULL) << endl;
    exit(0);
    return 0;
}

int execTest(int argc, char **argv, TestRunner *self)
{
    char * env_init[] = {"USER=unknown", "PATH=/tmp", NULL};
    cout << "father pid " << getpid() << endl;
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }
    else if (pid == 0)
    {
        cout << "================= start execle first time =========================" << endl;
        if (execle("/home/aidu37/script/bin/showAll.sh", "hahahaha", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
        {
            self->printErrMsg(ERROR_PREFIX);
            cout << "================= endl execle first time =========================" << endl;
            exit(-1);
        }

        cout << "================= endl execle first time =========================" << endl;
        exit(0);
    }

    cout << "first child pid " << pid << endl;
    
    if (waitpid(pid, NULL, 0) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }

    if ((pid = fork()) < 0)
    {
        self->printErrMsg(ERROR_PREFIX);
    }
    else if (pid == 0)
    {
        cout << "================= start execlp second time =========================" << endl;
        if (execlp("showAll.sh", "peipeipei", "only 1 arg", (char *)0) < 0)
        {
            self->printErrMsg(ERROR_PREFIX);
            cout << "================= endl execlp second time =========================" << endl;
            exit(-1);
        }
        cout << "================= endl execlp second time =========================" << endl;
        exit(0);
    }
    else
    {
        wait(0);
    }

    cout << "second child pid " << pid << endl;
    
    return 0;
}

int niceTest(int argc, char **argv, TestRunner *self)
{
    cout << getpriority(PRIO_PROCESS, getpid()) << endl;
    int niceValue = nice(14);
    cout << niceValue << endl;
    if (niceValue == -1)
    {
        self->printErrMsg(ERROR_PREFIX);
    }

    cout << getpriority(PRIO_PROCESS, getpid()) << endl;

    return 0;
}

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        cout << "SIGUSR1" << endl;
    else if (signo == SIGUSR2)
        cout << "SIGUSR2" << endl;
    else
        cout << "received signal " << signo << endl;
}

int signalTest(int argc, char **argv, TestRunner *self)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        cout << "can't catch SIGUSR1" << endl;

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        cout << "can't catch SIGUSR2" << endl;

    for( ; ; )
         pause();
    
    return 0;
}



int TestRunner::run(int argc, char **argv)
{
    return signalTest(argc, argv, this);
}

