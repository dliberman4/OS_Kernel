#include <stdint.h>
#include "../../PageAllocator/pageAllocator.h"

void * syscall_sbrk()
{
  return 0;//(void *)assignAllocatedPage(currentProc(), allocatePage());
}
