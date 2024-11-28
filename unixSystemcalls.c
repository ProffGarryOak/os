fork, getpid, and wait
This program demonstrates process creation using fork, retrieving process IDs using getpid, and waiting for child processes using wait.

c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        exit(0);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: PID = %d\n", getpid());
    }

    return 0;
}
exec
This program demonstrates replacing the current process image with a new process image using the exec family of functions.

c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};

    printf("Executing ls command...\n");
    execvp(args[0], args);
    
    perror("execvp"); // execvp only returns on failure
    exit(EXIT_FAILURE);
}
close
This program demonstrates closing a file descriptor using close.

c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read from the file
    char buffer[100];
    read(fd, buffer, sizeof(buffer) - 1);
    
    close(fd); // Close the file descriptor
    printf("File closed successfully.\n");

    return 0;
}
stat
This program demonstrates retrieving file status using stat.

c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    struct stat sb;

    if (stat("example.txt", &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File size: %lld bytes\n", (long long) sb.st_size);

    return 0;
}
opendir and readdir
This program demonstrates opening a directory and reading its contents using opendir and readdir.

c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
    if (d == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}