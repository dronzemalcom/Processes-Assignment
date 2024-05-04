#include <iostream>
#include <sys/wait.h>
//#include <windows.h>
#include <unistd.h>
using namespace std;

int main() {
    cout << "my pid: " << getpid() << ", my parent pid: " << getppid() << endl;
    int cid = fork();
    if (cid == 0) {
        // child process
        cout << "my pid: " << getpid() << ", my parent pid: " << getppid() << endl;
    }
    else {
        // parent process
        sleep(2);
        cout << "my pid: " << getpid() << ", my parent pid: " << getppid() << endl;
    }
    return 0;
}