#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

static int time = 0;

int main(int argc, char const *argv[]) {
  printf("%d about to create 2 child processing\n", getpid());
  pid_t p;
  p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    unsigned int n;
    int file = open("/dev/urandom", O_RDONLY, 0);
    read(file, &n, 4);
    close(file);
    n %= 5;
    printf("%d %dsec\n", getpid(), n);
    sleep(n);
    printf("%d finished after %dsec\n", getpid(), n);
  } else {
    printf("parent\n");
    p = fork();
    if (p < 0) {
      perror("fork fail");
      exit(1);
    } else if (p == 0) {
      unsigned int n;
      int file = open("/dev/urandom", O_RDONLY, 0);
      read(file, &n, 4);
      close(file);
      n %= 5;
      printf("%d %dsec\n", getpid(), n);
      sleep(n);
      printf("%d finished after %dsec\n", getpid(), n);
    } else {
      printf("parent still\n");
    }
  }
  return 0;
}
