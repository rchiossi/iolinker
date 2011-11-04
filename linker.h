#include <linux/elf.h>

#define SOINFO_NAME_LEN 128

typedef struct soinfo soinfo;

struct soinfo
{
  char name[SOINFO_NAME_LEN];
  Elf32_Phdr *phdr;
  int phnum;
  unsigned entry;
  unsigned base;
  unsigned size;

  unsigned *dynamic;

  unsigned wrprotect_start;
  unsigned wrprotect_end;

  soinfo *next;
  unsigned flags;

  const char *strtab;
  Elf32_Sym *symtab;

  unsigned nbucket;
  unsigned nchain;
  unsigned *bucket;
  unsigned *chain;

  unsigned *plt_got;

  Elf32_Rel *plt_rel;
  unsigned plt_rel_count;

  Elf32_Rel *rel;
  unsigned rel_count;

  unsigned *preinit_array;
  unsigned preinit_array_count;

  unsigned *init_array;
  unsigned init_array_count;
  unsigned *fini_array;
  unsigned fini_array_count;

  void (*init_func)(void);
  void (*fini_func)(void);

  unsigned refcount;
  //struct link_map linkmap;
};
