#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int parentID = getpid(); /* ID of this process */
    string prgname;
    getline(cin, prgname); /* read the name of program we want to start */
    int cid = fork();
    if (cid == 0) { /* I'm the child process */
        execlp(prgname.c_str(), prgname.c_str(), nullptr); /* Load the program */
        /* If the program named prgname can be started, we never get to this
        line, because the child program is replaced by prgname */
        cout << "I didn't find program " << prgname << endl;
    } else if (cid > 0) { /* I'm the parent process */
        sleep(1); /* Give my child time to start. */
        waitpid(cid, nullptr, 0); /* Wait for my child to terminate. */
        cout << "Program " << prgname << " finished\n";
    } else { /* fork failed */
        cerr << "Fork failed\n";
        return 1;
    }
    return 0;
}