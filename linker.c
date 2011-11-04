#include <linux/auxvec.h>
#include "linker.h"

static struct soinfo si;

static void init_info(const char *name)
{
  unsigned* ptr = (unsigned*)  &si;
  int i;

  for (i=0; i<sizeof(struct soinfo)/4;i++) *ptr = 0;

  for (i=0; i<SOINFO_NAME_LEN && name[i] != '\0'; i++)
    si.name[i] = name[i];

  si.name[i] = 0;
}

unsigned __linker_init(unsigned **elfdata)
{
  int argc = (int) *elfdata;
  char** argv = (char**) (elfdata + 1); 
  unsigned* envp = (unsigned*) (argv + argc + 1);
  unsigned* vecs;

  init_info(argv[0]);

  vecs = (unsigned*) envp;
  while (vecs[0] != 0) 
    vecs++;
  vecs++;

  while (vecs[0] != 0) {
    switch (vecs[0]) {
    case AT_PHDR:
      si.phdr = (Elf32_Phdr*) vecs[1];
      break;
    case AT_PHNUM:
      si.phnum = (int) vecs[1];
      break;
    case AT_ENTRY:
      si.entry = vecs[1];
      break;
    }
    vecs += 2;
  }  

  return &si.entry;
}

/* Main stub */
int main(void) {
  return 0;
}
