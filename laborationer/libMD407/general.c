/*
 * libMD407
 * general.c
 * includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
 * template functions for stdio:
 */
#include "libMD407.h"
extern DEV_DRIVER_DESC StdIn,StdOut,StdErr,KeyPad,AsciiDisplay;
PDEV_DRIVER_DESC device_table[MAX_FILENO+1] =
{
	&StdIn,
	&StdOut,
	&StdErr,
	&KeyPad,
	&AsciiDisplay,
};

static char *heap_end;
extern char __heap_low; 	/* Defined by the linker */
extern char __heap_top; 	/* Defined by the linker */
extern char __bss_start__; 	/* Defined by the linker */
extern char __bss_end__; 	/* Defined by the linker */

char * _sbrk(int incr) { ... }

void _crt_init() {
	char *s;
	PDEV_DRIVER_DESC fd;

	heap_end = 0;
	s = &__bss_start__;
	while( s < &__bss_end__ )
	*s++ = 0;
	s = &__heap_low;
	while( s < &__heap_top )
	*s++ = 0;
	for( int i = 0; i <= MAX_FILENO; i++ )
	{
		fd = device_table[i];
		if( fd && fd->init != 0)
			(void) fd->init( 0 );
	}
	/* NOTE: No printf buffering */
	(void)setvbuf(stdin, 0, _IONBF, 0);
	(void)setvbuf(stdout, 0, _IONBF, 0);
	(void)setvbuf(stderr, 0, _IONBF, 0);
}

void _crt_deinit() {
	PDEV_DRIVER_DESC fd;
	fflush(0); /* Will cause terminal flush... */
	for( int i = 0; i <= MAX_FILENO; i++ )
	{
	fd = device_table[i];
	if( fd && fd->deinit != 0)
		fd->deinit( 0 );
	}
}

/* Anm. parametrar till respektive device init/deinit är valbar */
/* STDIO-common functions */
int _close(int file) { return -1; }
int _open(const char *name, int flags, int mode) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _lseek(int file, int ptr, int dir) { return 0;}

int _isatty(int file) {
	switch (file)
	{
		case STDIN: case STDOUT: case STDERR: return 1;
		default: return 0;
	}
}

int _write(int file, char *ptr, int len) { ... }
int _read(int file, char *ptr, int len) { ... } 