#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

void childSleep() {
    unsigned char n;
    int file = open("/dev/urandom", O_RDONLY, 0);
    read(file, &n, 1);
    close(file);
    n = (n & 0b11) + 1;
    printf("%d %dsec\n", getpid(), n);
    sleep(n);
    printf("%d finished after %dsec\n", getpid(), n);
    exit(n);
}

int main(int argc, char const *argv[]) {
  printf("%d about to create 2 child processes\n", getpid());
  pid_t p;
  p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    childSleep();
  } else {
    p = fork();
    if (p < 0) {
      perror("fork fail");
      exit(1);
    } else if (p == 0) {
      childSleep();
    } else {
      int status = 0;
      pid_t child = waitpid(-1, &status, 0);
      printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), child, WEXITSTATUS(status));
    }
  }
  return 0;
}
