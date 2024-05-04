#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    string prgname;
    cout << "closh> ";
    getline(cin, prgname); /* read the name of program we want to start */
    if (prgname == "exit") {
        return 0; // Exit the shell if the user inputs "exit"
    }

    int count;
    cout << "count> ";
    cin >> count; // Get the number of copies of the program to run

    char mode;
    cout << "[p]arallel or [s]equential> ";
    cin >> mode; // Get the execution mode: parallel or sequential

    for (int i = 0; i < count; ++i) {
        int cid = fork();
        if (cid == 0) { /* I'm the child process */
            execlp(prgname.c_str(), prgname.c_str(), nullptr); /* Load the program */
            /* If the program named prgname can be started, we never get to this
            line, because the child program is replaced by prgname */
            cerr << "Failed to execute program " << prgname << endl;
            exit(1);
        } else if (cid < 0) { /* fork failed */
            cerr << "Fork failed\n";
            exit(1);
        }

        if (mode == 's') { // If sequential mode, wait for the child process to finish
            waitpid(cid, nullptr, 0); /* Wait for my child to terminate. */
        }
    }

    if (mode == 'p') { // If parallel mode, wait for all child processes to finish
        for (int i = 0; i < count; ++i) {
            wait(nullptr);
        }
    }

    cout << "All processes finished for program " << prgname << endl;

    return 0;
}
