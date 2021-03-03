/*
* libMD407.h
* Typer och konstanter som används i hela programbiblioteket
*/
#include 	<stdio.h>
#include 	<errno.h>
#include 	<sys/stat.h>
/* Type definitions */
#include 	<sys/stat.h>
typedef struct
{
	char name[16];
	int (*init) (int);
	void (*deinit) (int);
	int (*fstat)(struct stat *st);
	int (*isatty)(void);
	int (*open)(const char name,int flags,int mode);
	int (*close)(void);
	int (*lseek)(int ptr, int dir);
	int (*write)(char *ptr, int len);
	int (*read)(char *ptr, int len);
} DEV_DRIVER_DESC, *PDEV_DRIVER_DESC;

/* File handle constants */
enum {STDIN=0,STDOUT,STDERR,KEYPAD,ASCIIDISPLAY};
#define MAX_FILENO ASCIIDISPLAY
/* Library defined functions */
int _isatty(int file); 