/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/string.h"
#include "stdlib/stdio.h"

extern uint64_t systemCall(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

char parse_command(char * input);
uint64_t execve(int id);
void wait(uint64_t pid);

int main()
{
	void * heap;
	uint64_t * num;
	int i=0;

	init_printf(0, putc);
	printf("Soy sample! Voy a pedir todas las paginas que pueda...\n");
	do {
		heap = (void *)systemCall(0x2d, 0, 0, 0, 0, 0);
		if(!heap)
			break;
		printf("Tengo una pagina en %x (voy %d paginas obtenidas), voy a intentar escribir 0xC0FFEE...\n", heap, ++i);
		num = (uint64_t *)heap;
		*num = 0xC0FFEE;
		printf("Leo heap: %x\n", *num);
	} while(heap);

	return 0;
}