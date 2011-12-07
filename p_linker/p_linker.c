#include <linux/auxvec.h>

typedef struct _file_info {
  unsigned entry_point;
  unsigned headers_addr;
  unsigned headers_num;
} file_info;

#define DEBUG 0

#if DEBUG
#include <stdio.h>
#include <stdlib.h>

void check_parameters(int argc, char* argv[], char* envp[], unsigned* auxv);
void print_file_info(file_info info);
#endif

/*
int c_end __attribute__ ((section(".ctors")));
int c_end = 0xffffffff;
*/

void _ld_start() {
  asm(
      "sub $0x10,%esp \n"

      /* get argc */
      "lea 0x4(%ebp),%eax \n"  
      "mov (%eax),%eax \n"
      "mov %eax,%ebx \n"
      "mov %eax,(%esp) \n"

      /* get argv */
      "lea 0x8(%ebp),%eax \n"  
      "mov %eax,0x4(%esp) \n"

      /* get envp */
      "lea 0xc(%ebp,%ebx,4),%eax \n"  
      "mov %eax,0x8(%esp) \n"

      /* get auxv */
      "_l_auxv: \n"
      "add $0x4,%eax \n"
      "mov (%eax),%ebx \n"
      "test %ebx,%ebx \n"
      "jnz _l_auxv \n"
      "add $0x4,%eax \n"
      "mov %eax,0xc(%esp) \n" 

      /* locked and loaded! */
      "call __init_linker \n"
      
      /* transfer control to the program */
      "push %eax \n"
      "ret \n"

      //TEST ONLY: exit(15)
      //"mov $0x1,%eax \n"
      //"mov $0xF,%ebx \n"
      //"int $0x80 \n"
      );
}


file_info get_file_info(unsigned* auxv) {
  file_info info;
  int i;
  
  info.entry_point = 0xffffffff;
  info.headers_addr = 0xffffffff;
  info.headers_num = 0xffffffff;

  i=0;
  while (auxv[i] != 0) {
    switch (auxv[i]) {
    case AT_PHNUM:
      info.headers_num = auxv[++i];
      break;
    case AT_PHDR:
      info.headers_addr = auxv[++i];
      break;
    case AT_ENTRY:
      info.entry_point = auxv[++i];
      break;
    default:
      i++;
      break;
    }
    i++;
  }

  return info;
}

unsigned __init_linker(int argc, char* argv[], char* envp[], unsigned* auxv)
{
  file_info info;

#if DEBUG
  //check_parameters(argc,argv,envp,auxv);
#endif

  info = get_file_info(auxv);

#if DEBUG
  print_file_info(info);
#endif

  return info.entry_point;
}

/* Main Stub */
int main(void)
{
  return 0;
}

#if DEBUG

void check_parameters(int argc, char* argv[], char* envp[], unsigned* auxv)
{
  int i;
  char** p = envp;

  printf("argc = %d\n",argc);

  for (i=0; i<argc; i++) {
    printf("argv[%d] = %s\n",i,argv[i]);
  }
  /*
  i=0;
  while(*p) {
    printf("envp[%d] = %s\n",i,*p);
    i++;
    p++;
  }
  */

  printf("auxv = %p\n",auxv);

  i=0;
  while (auxv[i] != 0) {
    printf("auxv[i] = 0x%08x ",auxv[i++]);
    printf("0x%08x\n",auxv[i++]);
  }
}

void print_file_info(file_info info)
{
  printf("entry_point = 0x%08x headers_addr = 0x%08x headers_num = 0x%08x\n",info.entry_point,info.headers_addr,info.headers_num);
}

#endif
