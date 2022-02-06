/*
 * 	startup-crt.c
 *  includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
 *  template functions for stdio: 
 */

#include	<errno.h>
#include 	<sys/stat.h>
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<unistd.h>


/* länka h-filen */
#include    <libmd407.h>

__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=__stack_top\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL _crt_init\n");			/* init C-runtime library */
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(" BL _crt_deinit\n");			/* deinit C-runtime library */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}


/* Main program */

void main(void)
{
    setvbuf(stdout, 0, _IONBF, 0);
    printf("Library test");
    char buffer[10];
    while(1){
        if(read(KEYPAD, buffer, 1)){
            char c = buffer[0] + '0';
            write(ASCIIDISPLAY, &c, 1);
        }
    }
}
