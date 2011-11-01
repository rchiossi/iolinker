unsigned __linker_init(unsigned **elfdata)
{
  asm volatile ("push %eax\n");
  asm volatile ("push %eax\n");
  asm volatile ("push %eax\n");
  asm volatile ("push %eax\n");
  asm volatile ("pop %eax\n");
  asm volatile ("pop %eax\n");
  asm volatile ("pop %eax\n");
  asm volatile ("pop %eax\n");
}

/* Main stub */
int main(void) {
  return 0;
}
