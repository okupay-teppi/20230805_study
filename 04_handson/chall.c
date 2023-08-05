/* chall.c */
#include <stdio.h>

void main(void)
{
  char buf[32];

  puts("[*] Hello!");
  puts("[*] please input your name!");
  gets(buf);

  puts("[*] See you Next time!");
}

__attribute__((constructor))
void setup(){
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}