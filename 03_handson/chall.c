/* chall.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long addr;
unsigned long value;

int main(void)
{
  puts("[*] you can read from arbitrary memory address.");
  puts(" [+] let's leak libc addr from 'GOT'.");

  printf("address : 0x");
  scanf("%lx", &addr);
  printf("value : 0x%lx\n\n", *(unsigned long *)addr);

  puts("[*] OK! now, you can calculate 'system' function addr in libc.\n");
  
  puts("[*] you can write to arbitrary memory address.");
  puts(" [+] let's overwrite GOT of 'puts' and exec 'system(\"/bin/sh\\x00\")'");

  printf("address : 0x");
  scanf("%lx", &addr);
  printf("value : 0x");
  scanf("%lx", &value);

  memcpy((void *)addr, (void *)&value, sizeof(unsigned long));

  puts("/bin/sh\x00");
  
  return 0;
}

__attribute__((constructor))
void setup(){
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}