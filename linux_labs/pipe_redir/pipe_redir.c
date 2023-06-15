#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd[2], fd_in, fd_out;
  pid_t pid1, pid2;

  printf("Starting program...\n");
  // create pipe
  if (pipe(fd) < 0) {
    perror("pipe");
    return 1;
  }

  printf("Pipe created...\n");

  // create first child process
  pid1 = fork();
  if (pid1 < 0) {
    perror("fork");
    return 1;
  } else if (pid1 == 0) { // child process 1
    printf("Child 1 executing...\n");

    fd_in = open("/etc/passwd", O_RDONLY);
    dup2(fd_in, STDIN_FILENO); // replace standard input with file
    close(fd_in);

    dup2(fd[1],
         STDOUT_FILENO); // replace standard output with output part of pipe

    close(fd[0]);
    close(fd[1]);

    char *argv1[] = {"grep", "-v", "usr", NULL};
    execvp(argv1[0], argv1);

    _exit(1);
  }

  // create second child process
  pid2 = fork();
  if (pid2 < 0) {
    perror("fork");
    return 1;
  } else if (pid2 == 0) {
    printf("Child 2 executing...\n");
    // child process 2
    fd_out = open("r.txt", O_WRONLY | O_CREAT, 0666);
    dup2(fd_out, STDOUT_FILENO); // replace standard output with file
    close(fd_out);

    dup2(fd[0], STDIN_FILENO); // replace standard input with input part of pipe
                               //
    close(fd[0]);
    close(fd[1]);

    char *argv2[] = {"wc", "-l", NULL};
    execvp(argv2[0], argv2);

    _exit(1);
  }

  close(fd[0]);
  close(fd[1]);

  printf("Waiting for children to finish...\n");

  // wait for child processes to finish
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

  // print content of r.txt
  pid_t pid3 = fork();
  if (pid3 < 0) {
    perror("fork");
    return 1;
  } else if (pid3 == 0) {
    printf("Printint the content of r.txt...\n");

    char *argv3[] = {"cat", "r.txt", NULL};
    execvp(argv3[0], argv3);
    _exit(1);
  }

  waitpid(pid3, NULL, 0);

  printf("Program finished.\n");

  return EXIT_SUCCESS;
}
