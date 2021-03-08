/*
 * 	libNAME.c
 *	custom static library
 */
 
 /* Include standard headers */
#include	<stdio.h>
#include 	<sys/stat.h>

/* Declare your functions in 'libNANE.h' */
#include	"libmd407io.h"


/* Define your functions here */
/* STDIO-templates */
int _close(int file) { return -1; }
int _open(const char *name, int flags, int mode) { return -1; }
int _isatty(int file) { return 1; }//"är detta en tele type writer?"="är detta en terminal som kommer skicka/ta emot text"
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _lseek(int file, int ptr, int dir) { return 0;}
int _read(int file, char *ptr, int len) { return 0; }
int _write(int file, char *ptr, int len) { return 0; }

