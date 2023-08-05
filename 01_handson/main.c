#include <stdio.h>

int main(void)
{
  FILE * fd;
  char flag_buf[256];

  puts("[*] Hello! present for you!");
  
  fd = fopen("flag_2", "r");
  if (fd == NULL) {
    fprintf(stderr, "[!] You couldn't open file\n");
    exit(-1);
  }
  
  fgets(flag_buf, 256, fd);
  puts(flag_buf);

  puts("[*] Let's submit flag and move on to the next challenge 'Baby_PWN #3'\n");

  char buf[8];

  puts("[*] please input '0xdeadbeef' in buf");
  fgets(buf, 5, stdin);
  
  printf("buf = 0x%x\n", *(int *)buf);

  if (*(unsigned int *)buf == 0xdeadbeef) {
    puts("[*] OK! you got shell!");
    system("/bin/sh\x00");
  }

  return 0;
}