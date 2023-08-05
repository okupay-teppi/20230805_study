/* test_chall.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * filename = NULL;

void print_flag(char * flag_name);
void print_stack(void * buf_addr);
void check_buf(void * buf);
void cheat();
void vuln_func();
void open_flag(char * fname);

void win_1();
void win_2(unsigned long param_1, unsigned long param_2);
void win_3();

int main(void)
{
  vuln_func();
  return 0;
}

void print_stack(void * buf_addr) {
  unsigned long stack_addr;

  stack_addr = (unsigned long)buf_addr;

  puts("[*] print stack frame ... ");
  puts("address            : value            ");
  for (int i = 0; i < 0x10; i++) {
    printf("0x%016lx : 0x%016lx", stack_addr + 0x8 * i, *(unsigned long *)(stack_addr + 0x8 * i));
    if (i == 0) {
      printf("  <=== buf1\n");
    } else if (i == 3) {
      printf("  <=== secret\n");
    } else if (i == 5) {
      printf("  <=== ret addr\n");
    } else {
      printf("\n");
    }
  }
  puts("[*] Done ...");
}

void print_flag(char * flag_name) {
  FILE * fd;
  char buffer[256];

  fd = fopen(flag_name, "r");
  if (fd == NULL) {
    fprintf(stderr, "[!] You couldn't open file\n");
    exit(-1);
  }
  
  fgets(buffer, 256, fd);
  puts(buffer);
}

void check_buf(void * buf) {
  for (int i; i < 0x70; i+=8) {
    if ((unsigned long)print_flag <= *(unsigned long *)(buf + i) && *(unsigned long *)(buf + i) < (unsigned long)cheat)  {
      puts("[!] sorry, you can't exec 'print_flag' by ROP in this question ...");
      exit(0);
    }
  }
}

void cheat() {
  puts("[*] This is cheat func!");
  char buf[0x100];
  gets(buf);
  system("/bin/ls\n");
}

void vuln_func()
{
  char buf1[0x18];
  unsigned long secret = 0x1337;
  
  filename = "flag_1";

  print_stack(buf1);
  
  puts("[*] Please input data in 'buf1' ...");
  fgets(buf1, 0x70, stdin);
  check_buf(buf1);

  if (secret == 0xdeadbeef) {
    puts("[*] Congratulations! I will give you flag_1.");
    print_flag(filename);
    puts("[*] Let's submit flag and move on to the next challenge 'hands-on 2-2'\n");
    print_stack(buf1);
  } else {
    puts("[*] check the stack frame! and overwirte 'secret' variable");
    print_stack(buf1);
  }
}

void win_1() {
  puts("[*] win_1 function.");
  puts("[*] Congratulations! I will give you flag_2!");
  print_flag("flag_2");

  puts("\n[*] Let's submit flag and move on to the next challenge 'hands-on 2-3'");

  exit(0);
}

void win_2(unsigned long param_1, unsigned long param_2) {
  puts("[*] win_2 function.");
  filename = "flag_3";

  if ((param_1 == 0xdeadbeef) && (param_2 == 0xcafebabe)) {
    puts("[*] Congratulations! I will give you flag_3!!");
    print_flag(filename);
  
    puts("[*] Let's submit flag and move on to the next challenge 'hands-on 2-4'\n");
  } else {
    puts("[*] ok, Let's check value of 'rdi' and 'rsi' register.");
  }

  exit(0);
}

void win_3() {
  unsigned long bss_writable = 0x404200;

  puts("[*] win_3 function.");
  printf(" [+] bss writable : %s\n", (char *)bss_writable);
  filename = "flag_4";

  if (strcmp((char *)bss_writable, "katagaitai") == 0) {
    puts("[*] Congratulations! I will give you flag_4!!!");
    puts("[*] ok, you can execute 'system' function. Let's get shell!");
    print_flag(filename);
  } else {
    puts("[*] ok, Let's check value of 'rdi'.");
    puts("[*] you must set pointer of string in 'rdi' register, and you can write data to 'bss' by 'gets'");
  }

  exit(0);
}

__attribute__((constructor))
void setup(){
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}