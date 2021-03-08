   1              		.arch armv6-m
   2              		.eabi_attribute 20, 1
   3              		.eabi_attribute 21, 1
   4              		.eabi_attribute 23, 3
   5              		.eabi_attribute 24, 1
   6              		.eabi_attribute 25, 1
   7              		.eabi_attribute 26, 1
   8              		.eabi_attribute 30, 6
   9              		.eabi_attribute 34, 0
  10              		.eabi_attribute 18, 4
  11              		.file	"general.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.global	device_table
  16              		.data
  17              		.align	2
  20              	device_table:
  21 0000 00000000 		.word	StdIn
  22 0004 00000000 		.word	StdOut
  23 0008 00000000 		.word	StdErr
  24 000c 00000000 		.word	KeyPad
  25 0010 00000000 		.word	AsciiDisplay
  26              		.bss
  27              		.align	2
  28              	heap_end:
  29 0000 00000000 		.space	4
  31              		.text
  32              		.align	1
  33              		.global	_sbrk
  34              		.syntax unified
  35              		.code	16
  36              		.thumb_func
  37              		.fpu softvfp
  39              	_sbrk:
  40              	.LFB3:
  41              		.file 1 "/home/elvina/Dokument/MOP/laborationer/libMD407/general.c"
   1:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** /*
   2:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  * libMD407
   3:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  * general.c
   4:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  * includes: _crt_init, _crt_deinit, _sbrk for malloc-support.
   5:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  * template functions for stdio:
   6:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  */
   7:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  /*
   8:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** #define _REENT_SMALL
   9:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** #define __SINGLE_THREAD
  10:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  11:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** #include <sys/reent.h> 
  12:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****  */
  13:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  14:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** #include "libMD407.h"
  15:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** extern DEV_DRIVER_DESC StdIn,StdOut,StdErr,KeyPad,AsciiDisplay;
  16:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  17:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  18:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** PDEV_DRIVER_DESC device_table[MAX_FILENO+1] =
  19:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** {
  20:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	&StdIn,
  21:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	&StdOut,
  22:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	&StdErr,
  23:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	&KeyPad,
  24:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	&AsciiDisplay,
  25:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** };
  26:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  27:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** static char *heap_end;
  28:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** extern char __heap_low; 	/* Defined by the linker */
  29:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** extern char __heap_top; 	/* Defined by the linker */
  30:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** extern char __bss_start__; 	/* Defined by the linker */
  31:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** extern char __bss_end__; 	/* Defined by the linker */
  32:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  33:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** char * _sbrk(int incr) {
  42              		.loc 1 33 24
  43              		.cfi_startproc
  44              		@ args = 0, pretend = 0, frame = 16
  45              		@ frame_needed = 1, uses_anonymous_args = 0
  46 0000 80B5     		push	{r7, lr}
  47              		.cfi_def_cfa_offset 8
  48              		.cfi_offset 7, -8
  49              		.cfi_offset 14, -4
  50 0002 84B0     		sub	sp, sp, #16
  51              		.cfi_def_cfa_offset 24
  52 0004 00AF     		add	r7, sp, #0
  53              		.cfi_def_cfa_register 7
  54 0006 7860     		str	r0, [r7, #4]
  34:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     char *prev_heap_end;
  35:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     if (heap_end == 0) {
  55              		.loc 1 35 18
  56 0008 114B     		ldr	r3, .L5
  57 000a 1B68     		ldr	r3, [r3]
  58              		.loc 1 35 8
  59 000c 002B     		cmp	r3, #0
  60 000e 02D1     		bne	.L2
  36:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         heap_end = &__heap_low;
  61              		.loc 1 36 18
  62 0010 0F4B     		ldr	r3, .L5
  63 0012 104A     		ldr	r2, .L5+4
  64 0014 1A60     		str	r2, [r3]
  65              	.L2:
  37:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     }
  38:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     prev_heap_end = heap_end;
  66              		.loc 1 38 19
  67 0016 0E4B     		ldr	r3, .L5
  68 0018 1B68     		ldr	r3, [r3]
  69 001a FB60     		str	r3, [r7, #12]
  39:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     
  40:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     if(heap_end + incr > &__heap_top) {
  70              		.loc 1 40 17
  71 001c 0C4B     		ldr	r3, .L5
  72 001e 1A68     		ldr	r2, [r3]
  73 0020 7B68     		ldr	r3, [r7, #4]
  74 0022 D218     		adds	r2, r2, r3
  75              		.loc 1 40 7
  76 0024 0C4B     		ldr	r3, .L5+8
  77 0026 9A42     		cmp	r2, r3
  78 0028 07D9     		bls	.L3
  41:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         /* Kollision mellan heap och stack...*/
  42:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         errno = ENOMEM;
  79              		.loc 1 42 9
  80 002a FFF7FEFF 		bl	__errno
  81 002e 0300     		movs	r3, r0
  82              		.loc 1 42 15
  83 0030 0C22     		movs	r2, #12
  84 0032 1A60     		str	r2, [r3]
  43:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         return (char *)-1;
  85              		.loc 1 43 16
  86 0034 0123     		movs	r3, #1
  87 0036 5B42     		rsbs	r3, r3, #0
  88 0038 06E0     		b	.L4
  89              	.L3:
  44:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     }
  45:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     heap_end += incr;
  90              		.loc 1 45 14
  91 003a 054B     		ldr	r3, .L5
  92 003c 1A68     		ldr	r2, [r3]
  93 003e 7B68     		ldr	r3, [r7, #4]
  94 0040 D218     		adds	r2, r2, r3
  95 0042 034B     		ldr	r3, .L5
  96 0044 1A60     		str	r2, [r3]
  46:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     return (char *) prev_heap_end;
  97              		.loc 1 46 12
  98 0046 FB68     		ldr	r3, [r7, #12]
  99              	.L4:
  47:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** }
 100              		.loc 1 47 1
 101 0048 1800     		movs	r0, r3
 102 004a BD46     		mov	sp, r7
 103 004c 04B0     		add	sp, sp, #16
 104              		@ sp needed
 105 004e 80BD     		pop	{r7, pc}
 106              	.L6:
 107              		.align	2
 108              	.L5:
 109 0050 00000000 		.word	heap_end
 110 0054 00000000 		.word	__heap_low
 111 0058 00000000 		.word	__heap_top
 112              		.cfi_endproc
 113              	.LFE3:
 115              		.align	1
 116              		.global	_crt_init
 117              		.syntax unified
 118              		.code	16
 119              		.thumb_func
 120              		.fpu softvfp
 122              	_crt_init:
 123              	.LFB4:
  48:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  49:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** void _crt_init() {
 124              		.loc 1 49 18
 125              		.cfi_startproc
 126              		@ args = 0, pretend = 0, frame = 16
 127              		@ frame_needed = 1, uses_anonymous_args = 0
 128 005c 80B5     		push	{r7, lr}
 129              		.cfi_def_cfa_offset 8
 130              		.cfi_offset 7, -8
 131              		.cfi_offset 14, -4
 132 005e 84B0     		sub	sp, sp, #16
 133              		.cfi_def_cfa_offset 24
 134 0060 00AF     		add	r7, sp, #0
 135              		.cfi_def_cfa_register 7
  50:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	char *s;
  51:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	PDEV_DRIVER_DESC fd;
  52:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  53:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	heap_end = 0;
 136              		.loc 1 53 11
 137 0062 284B     		ldr	r3, .L15
 138 0064 0022     		movs	r2, #0
 139 0066 1A60     		str	r2, [r3]
  54:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	s = &__bss_start__;
 140              		.loc 1 54 4
 141 0068 274B     		ldr	r3, .L15+4
 142 006a FB60     		str	r3, [r7, #12]
  55:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	while( s < &__bss_end__ )
 143              		.loc 1 55 7
 144 006c 04E0     		b	.L8
 145              	.L9:
  56:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	*s++ = 0;
 146              		.loc 1 56 4
 147 006e FB68     		ldr	r3, [r7, #12]
 148 0070 5A1C     		adds	r2, r3, #1
 149 0072 FA60     		str	r2, [r7, #12]
 150              		.loc 1 56 7
 151 0074 0022     		movs	r2, #0
 152 0076 1A70     		strb	r2, [r3]
 153              	.L8:
  55:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	while( s < &__bss_end__ )
 154              		.loc 1 55 7
 155 0078 FA68     		ldr	r2, [r7, #12]
 156 007a 244B     		ldr	r3, .L15+8
 157 007c 9A42     		cmp	r2, r3
 158 007e F6D3     		bcc	.L9
  57:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	s = &__heap_low;
 159              		.loc 1 57 4
 160 0080 234B     		ldr	r3, .L15+12
 161 0082 FB60     		str	r3, [r7, #12]
  58:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	while( s < &__heap_top )
 162              		.loc 1 58 7
 163 0084 04E0     		b	.L10
 164              	.L11:
  59:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	*s++ = 0;
 165              		.loc 1 59 4
 166 0086 FB68     		ldr	r3, [r7, #12]
 167 0088 5A1C     		adds	r2, r3, #1
 168 008a FA60     		str	r2, [r7, #12]
 169              		.loc 1 59 7
 170 008c 0022     		movs	r2, #0
 171 008e 1A70     		strb	r2, [r3]
 172              	.L10:
  58:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	while( s < &__heap_top )
 173              		.loc 1 58 7
 174 0090 FA68     		ldr	r2, [r7, #12]
 175 0092 204B     		ldr	r3, .L15+16
 176 0094 9A42     		cmp	r2, r3
 177 0096 F6D3     		bcc	.L11
 178              	.LBB2:
  60:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	for( int i = 0; i <= MAX_FILENO; i++ )
 179              		.loc 1 60 11
 180 0098 0023     		movs	r3, #0
 181 009a BB60     		str	r3, [r7, #8]
 182              		.loc 1 60 2
 183 009c 12E0     		b	.L12
 184              	.L14:
  61:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
  62:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 		fd = device_table[i];
 185              		.loc 1 62 6
 186 009e 1E4B     		ldr	r3, .L15+20
 187 00a0 BA68     		ldr	r2, [r7, #8]
 188 00a2 9200     		lsls	r2, r2, #2
 189 00a4 D358     		ldr	r3, [r2, r3]
 190 00a6 7B60     		str	r3, [r7, #4]
  63:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 		if( fd && fd->init != 0)
 191              		.loc 1 63 5
 192 00a8 7B68     		ldr	r3, [r7, #4]
 193 00aa 002B     		cmp	r3, #0
 194 00ac 07D0     		beq	.L13
 195              		.loc 1 63 15 discriminator 1
 196 00ae 7B68     		ldr	r3, [r7, #4]
 197 00b0 1B69     		ldr	r3, [r3, #16]
 198              		.loc 1 63 10 discriminator 1
 199 00b2 002B     		cmp	r3, #0
 200 00b4 03D0     		beq	.L13
  64:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 			(void) fd->init( 0 );
 201              		.loc 1 64 13
 202 00b6 7B68     		ldr	r3, [r7, #4]
 203 00b8 1B69     		ldr	r3, [r3, #16]
 204              		.loc 1 64 11
 205 00ba 0020     		movs	r0, #0
 206 00bc 9847     		blx	r3
 207              	.LVL0:
 208              	.L13:
  60:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
 209              		.loc 1 60 36 discriminator 2
 210 00be BB68     		ldr	r3, [r7, #8]
 211 00c0 0133     		adds	r3, r3, #1
 212 00c2 BB60     		str	r3, [r7, #8]
 213              	.L12:
  60:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
 214              		.loc 1 60 2 discriminator 1
 215 00c4 BB68     		ldr	r3, [r7, #8]
 216 00c6 042B     		cmp	r3, #4
 217 00c8 E9DD     		ble	.L14
 218              	.LBE2:
  65:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	}
  66:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	/* NOTE: No printf buffering */
  67:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	(void)setvbuf(stdin, 0, _IONBF, 0);
 219              		.loc 1 67 16
 220 00ca 144B     		ldr	r3, .L15+24
 221 00cc 1B68     		ldr	r3, [r3]
 222 00ce 5868     		ldr	r0, [r3, #4]
 223              		.loc 1 67 8
 224 00d0 0023     		movs	r3, #0
 225 00d2 0222     		movs	r2, #2
 226 00d4 0021     		movs	r1, #0
 227 00d6 FFF7FEFF 		bl	setvbuf
  68:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	(void)setvbuf(stdout, 0, _IONBF, 0);
 228              		.loc 1 68 16
 229 00da 104B     		ldr	r3, .L15+24
 230 00dc 1B68     		ldr	r3, [r3]
 231 00de 9868     		ldr	r0, [r3, #8]
 232              		.loc 1 68 8
 233 00e0 0023     		movs	r3, #0
 234 00e2 0222     		movs	r2, #2
 235 00e4 0021     		movs	r1, #0
 236 00e6 FFF7FEFF 		bl	setvbuf
  69:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	(void)setvbuf(stderr, 0, _IONBF, 0);
 237              		.loc 1 69 16
 238 00ea 0C4B     		ldr	r3, .L15+24
 239 00ec 1B68     		ldr	r3, [r3]
 240 00ee D868     		ldr	r0, [r3, #12]
 241              		.loc 1 69 8
 242 00f0 0023     		movs	r3, #0
 243 00f2 0222     		movs	r2, #2
 244 00f4 0021     		movs	r1, #0
 245 00f6 FFF7FEFF 		bl	setvbuf
  70:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** }
 246              		.loc 1 70 1
 247 00fa C046     		nop
 248 00fc BD46     		mov	sp, r7
 249 00fe 04B0     		add	sp, sp, #16
 250              		@ sp needed
 251 0100 80BD     		pop	{r7, pc}
 252              	.L16:
 253 0102 C046     		.align	2
 254              	.L15:
 255 0104 00000000 		.word	heap_end
 256 0108 00000000 		.word	__bss_start__
 257 010c 00000000 		.word	__bss_end__
 258 0110 00000000 		.word	__heap_low
 259 0114 00000000 		.word	__heap_top
 260 0118 00000000 		.word	device_table
 261 011c 00000000 		.word	_impure_ptr
 262              		.cfi_endproc
 263              	.LFE4:
 265              		.align	1
 266              		.global	_crt_deinit
 267              		.syntax unified
 268              		.code	16
 269              		.thumb_func
 270              		.fpu softvfp
 272              	_crt_deinit:
 273              	.LFB5:
  71:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  72:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** void _crt_deinit() {
 274              		.loc 1 72 20
 275              		.cfi_startproc
 276              		@ args = 0, pretend = 0, frame = 8
 277              		@ frame_needed = 1, uses_anonymous_args = 0
 278 0120 80B5     		push	{r7, lr}
 279              		.cfi_def_cfa_offset 8
 280              		.cfi_offset 7, -8
 281              		.cfi_offset 14, -4
 282 0122 82B0     		sub	sp, sp, #8
 283              		.cfi_def_cfa_offset 16
 284 0124 00AF     		add	r7, sp, #0
 285              		.cfi_def_cfa_register 7
  73:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	PDEV_DRIVER_DESC fd;
  74:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	fflush(0); /* Will cause terminal flush... */
 286              		.loc 1 74 2
 287 0126 0020     		movs	r0, #0
 288 0128 FFF7FEFF 		bl	fflush
 289              	.LBB3:
  75:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	for( int i = 0; i <= MAX_FILENO; i++ )
 290              		.loc 1 75 11
 291 012c 0023     		movs	r3, #0
 292 012e 7B60     		str	r3, [r7, #4]
 293              		.loc 1 75 2
 294 0130 12E0     		b	.L18
 295              	.L20:
  76:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
  77:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	fd = device_table[i];
 296              		.loc 1 77 5
 297 0132 0D4B     		ldr	r3, .L21
 298 0134 7A68     		ldr	r2, [r7, #4]
 299 0136 9200     		lsls	r2, r2, #2
 300 0138 D358     		ldr	r3, [r2, r3]
 301 013a 3B60     		str	r3, [r7]
  78:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	if( fd && fd->deinit != 0)
 302              		.loc 1 78 4
 303 013c 3B68     		ldr	r3, [r7]
 304 013e 002B     		cmp	r3, #0
 305 0140 07D0     		beq	.L19
 306              		.loc 1 78 14 discriminator 1
 307 0142 3B68     		ldr	r3, [r7]
 308 0144 5B69     		ldr	r3, [r3, #20]
 309              		.loc 1 78 9 discriminator 1
 310 0146 002B     		cmp	r3, #0
 311 0148 03D0     		beq	.L19
  79:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 		fd->deinit( 0 );
 312              		.loc 1 79 5
 313 014a 3B68     		ldr	r3, [r7]
 314 014c 5B69     		ldr	r3, [r3, #20]
 315              		.loc 1 79 3
 316 014e 0020     		movs	r0, #0
 317 0150 9847     		blx	r3
 318              	.LVL1:
 319              	.L19:
  75:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
 320              		.loc 1 75 36 discriminator 2
 321 0152 7B68     		ldr	r3, [r7, #4]
 322 0154 0133     		adds	r3, r3, #1
 323 0156 7B60     		str	r3, [r7, #4]
 324              	.L18:
  75:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
 325              		.loc 1 75 2 discriminator 1
 326 0158 7B68     		ldr	r3, [r7, #4]
 327 015a 042B     		cmp	r3, #4
 328 015c E9DD     		ble	.L20
 329              	.LBE3:
  80:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	}
  81:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** }
 330              		.loc 1 81 1
 331 015e C046     		nop
 332 0160 C046     		nop
 333 0162 BD46     		mov	sp, r7
 334 0164 02B0     		add	sp, sp, #8
 335              		@ sp needed
 336 0166 80BD     		pop	{r7, pc}
 337              	.L22:
 338              		.align	2
 339              	.L21:
 340 0168 00000000 		.word	device_table
 341              		.cfi_endproc
 342              	.LFE5:
 344              		.align	1
 345              		.global	_close
 346              		.syntax unified
 347              		.code	16
 348              		.thumb_func
 349              		.fpu softvfp
 351              	_close:
 352              	.LFB6:
  82:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  83:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** /* Anm. parametrar till respektive device init/deinit är valbar */
  84:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** /* STDIO-common functions */
  85:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _close(int file) { return -1; }
 353              		.loc 1 85 22
 354              		.cfi_startproc
 355              		@ args = 0, pretend = 0, frame = 8
 356              		@ frame_needed = 1, uses_anonymous_args = 0
 357 016c 80B5     		push	{r7, lr}
 358              		.cfi_def_cfa_offset 8
 359              		.cfi_offset 7, -8
 360              		.cfi_offset 14, -4
 361 016e 82B0     		sub	sp, sp, #8
 362              		.cfi_def_cfa_offset 16
 363 0170 00AF     		add	r7, sp, #0
 364              		.cfi_def_cfa_register 7
 365 0172 7860     		str	r0, [r7, #4]
 366              		.loc 1 85 31
 367 0174 0123     		movs	r3, #1
 368 0176 5B42     		rsbs	r3, r3, #0
 369              		.loc 1 85 1
 370 0178 1800     		movs	r0, r3
 371 017a BD46     		mov	sp, r7
 372 017c 02B0     		add	sp, sp, #8
 373              		@ sp needed
 374 017e 80BD     		pop	{r7, pc}
 375              		.cfi_endproc
 376              	.LFE6:
 378              		.align	1
 379              		.global	_open
 380              		.syntax unified
 381              		.code	16
 382              		.thumb_func
 383              		.fpu softvfp
 385              	_open:
 386              	.LFB7:
  86:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _open(const char *name, int flags, int mode) { return -1; }
 387              		.loc 1 86 50
 388              		.cfi_startproc
 389              		@ args = 0, pretend = 0, frame = 16
 390              		@ frame_needed = 1, uses_anonymous_args = 0
 391 0180 80B5     		push	{r7, lr}
 392              		.cfi_def_cfa_offset 8
 393              		.cfi_offset 7, -8
 394              		.cfi_offset 14, -4
 395 0182 84B0     		sub	sp, sp, #16
 396              		.cfi_def_cfa_offset 24
 397 0184 00AF     		add	r7, sp, #0
 398              		.cfi_def_cfa_register 7
 399 0186 F860     		str	r0, [r7, #12]
 400 0188 B960     		str	r1, [r7, #8]
 401 018a 7A60     		str	r2, [r7, #4]
 402              		.loc 1 86 59
 403 018c 0123     		movs	r3, #1
 404 018e 5B42     		rsbs	r3, r3, #0
 405              		.loc 1 86 1
 406 0190 1800     		movs	r0, r3
 407 0192 BD46     		mov	sp, r7
 408 0194 04B0     		add	sp, sp, #16
 409              		@ sp needed
 410 0196 80BD     		pop	{r7, pc}
 411              		.cfi_endproc
 412              	.LFE7:
 414              		.align	1
 415              		.global	_fstat
 416              		.syntax unified
 417              		.code	16
 418              		.thumb_func
 419              		.fpu softvfp
 421              	_fstat:
 422              	.LFB8:
  87:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
 423              		.loc 1 87 39
 424              		.cfi_startproc
 425              		@ args = 0, pretend = 0, frame = 8
 426              		@ frame_needed = 1, uses_anonymous_args = 0
 427 0198 80B5     		push	{r7, lr}
 428              		.cfi_def_cfa_offset 8
 429              		.cfi_offset 7, -8
 430              		.cfi_offset 14, -4
 431 019a 82B0     		sub	sp, sp, #8
 432              		.cfi_def_cfa_offset 16
 433 019c 00AF     		add	r7, sp, #0
 434              		.cfi_def_cfa_register 7
 435 019e 7860     		str	r0, [r7, #4]
 436 01a0 3960     		str	r1, [r7]
 437              		.loc 1 87 53
 438 01a2 3B68     		ldr	r3, [r7]
 439 01a4 8022     		movs	r2, #128
 440 01a6 9201     		lsls	r2, r2, #6
 441 01a8 5A60     		str	r2, [r3, #4]
 442              		.loc 1 87 71
 443 01aa 0023     		movs	r3, #0
 444              		.loc 1 87 29
 445 01ac 1800     		movs	r0, r3
 446 01ae BD46     		mov	sp, r7
 447 01b0 02B0     		add	sp, sp, #8
 448              		@ sp needed
 449 01b2 80BD     		pop	{r7, pc}
 450              		.cfi_endproc
 451              	.LFE8:
 453              		.align	1
 454              		.global	_lseek
 455              		.syntax unified
 456              		.code	16
 457              		.thumb_func
 458              		.fpu softvfp
 460              	_lseek:
 461              	.LFB9:
  88:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _lseek(int file, int ptr, int dir) { return 0;}
 462              		.loc 1 88 40
 463              		.cfi_startproc
 464              		@ args = 0, pretend = 0, frame = 16
 465              		@ frame_needed = 1, uses_anonymous_args = 0
 466 01b4 80B5     		push	{r7, lr}
 467              		.cfi_def_cfa_offset 8
 468              		.cfi_offset 7, -8
 469              		.cfi_offset 14, -4
 470 01b6 84B0     		sub	sp, sp, #16
 471              		.cfi_def_cfa_offset 24
 472 01b8 00AF     		add	r7, sp, #0
 473              		.cfi_def_cfa_register 7
 474 01ba F860     		str	r0, [r7, #12]
 475 01bc B960     		str	r1, [r7, #8]
 476 01be 7A60     		str	r2, [r7, #4]
 477              		.loc 1 88 49
 478 01c0 0023     		movs	r3, #0
 479              		.loc 1 88 1
 480 01c2 1800     		movs	r0, r3
 481 01c4 BD46     		mov	sp, r7
 482 01c6 04B0     		add	sp, sp, #16
 483              		@ sp needed
 484 01c8 80BD     		pop	{r7, pc}
 485              		.cfi_endproc
 486              	.LFE9:
 488              		.align	1
 489              		.global	_isatty
 490              		.syntax unified
 491              		.code	16
 492              		.thumb_func
 493              		.fpu softvfp
 495              	_isatty:
 496              	.LFB10:
  89:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  90:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _isatty(int file) {
 497              		.loc 1 90 23
 498              		.cfi_startproc
 499              		@ args = 0, pretend = 0, frame = 8
 500              		@ frame_needed = 1, uses_anonymous_args = 0
 501 01ca 80B5     		push	{r7, lr}
 502              		.cfi_def_cfa_offset 8
 503              		.cfi_offset 7, -8
 504              		.cfi_offset 14, -4
 505 01cc 82B0     		sub	sp, sp, #8
 506              		.cfi_def_cfa_offset 16
 507 01ce 00AF     		add	r7, sp, #0
 508              		.cfi_def_cfa_register 7
 509 01d0 7860     		str	r0, [r7, #4]
 510 01d2 7B68     		ldr	r3, [r7, #4]
  91:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	switch (file)
 511              		.loc 1 91 2
 512 01d4 022B     		cmp	r3, #2
 513 01d6 01D8     		bhi	.L32
  92:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	{
  93:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 		case STDIN: case STDOUT: case STDERR: return 1;
 514              		.loc 1 93 48
 515 01d8 0123     		movs	r3, #1
 516 01da 00E0     		b	.L33
 517              	.L32:
  94:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 		default: return 0;
 518              		.loc 1 94 19
 519 01dc 0023     		movs	r3, #0
 520              	.L33:
  95:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 	}
  96:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** }
 521              		.loc 1 96 1
 522 01de 1800     		movs	r0, r3
 523 01e0 BD46     		mov	sp, r7
 524 01e2 02B0     		add	sp, sp, #8
 525              		@ sp needed
 526 01e4 80BD     		pop	{r7, pc}
 527              		.cfi_endproc
 528              	.LFE10:
 530              		.align	1
 531              		.global	_write
 532              		.syntax unified
 533              		.code	16
 534              		.thumb_func
 535              		.fpu softvfp
 537              	_write:
 538              	.LFB11:
  97:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
  98:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _write(int file, char *ptr, int len) {
 539              		.loc 1 98 42
 540              		.cfi_startproc
 541              		@ args = 0, pretend = 0, frame = 24
 542              		@ frame_needed = 1, uses_anonymous_args = 0
 543 01e6 80B5     		push	{r7, lr}
 544              		.cfi_def_cfa_offset 8
 545              		.cfi_offset 7, -8
 546              		.cfi_offset 14, -4
 547 01e8 86B0     		sub	sp, sp, #24
 548              		.cfi_def_cfa_offset 32
 549 01ea 00AF     		add	r7, sp, #0
 550              		.cfi_def_cfa_register 7
 551 01ec F860     		str	r0, [r7, #12]
 552 01ee B960     		str	r1, [r7, #8]
 553 01f0 7A60     		str	r2, [r7, #4]
  99:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     PDEV_DRIVER_DESC drvr;
 100:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     drvr = device_table[file];
 554              		.loc 1 100 10
 555 01f2 0A4B     		ldr	r3, .L37
 556 01f4 FA68     		ldr	r2, [r7, #12]
 557 01f6 9200     		lsls	r2, r2, #2
 558 01f8 D358     		ldr	r3, [r2, r3]
 559 01fa 7B61     		str	r3, [r7, #20]
 101:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     if(drvr == 0)
 560              		.loc 1 101 7
 561 01fc 7B69     		ldr	r3, [r7, #20]
 562 01fe 002B     		cmp	r3, #0
 563 0200 01D1     		bne	.L35
 102:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         return 0;
 564              		.loc 1 102 16
 565 0202 0023     		movs	r3, #0
 566 0204 06E0     		b	.L36
 567              	.L35:
 103:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     return drvr->write(ptr,len);
 568              		.loc 1 103 16
 569 0206 7B69     		ldr	r3, [r7, #20]
 570 0208 DB6A     		ldr	r3, [r3, #44]
 571              		.loc 1 103 12
 572 020a 7968     		ldr	r1, [r7, #4]
 573 020c BA68     		ldr	r2, [r7, #8]
 574 020e 1000     		movs	r0, r2
 575 0210 9847     		blx	r3
 576              	.LVL2:
 577 0212 0300     		movs	r3, r0
 578              	.L36:
 104:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** }
 579              		.loc 1 104 1
 580 0214 1800     		movs	r0, r3
 581 0216 BD46     		mov	sp, r7
 582 0218 06B0     		add	sp, sp, #24
 583              		@ sp needed
 584 021a 80BD     		pop	{r7, pc}
 585              	.L38:
 586              		.align	2
 587              	.L37:
 588 021c 00000000 		.word	device_table
 589              		.cfi_endproc
 590              	.LFE11:
 592              		.align	1
 593              		.global	_read
 594              		.syntax unified
 595              		.code	16
 596              		.thumb_func
 597              		.fpu softvfp
 599              	_read:
 600              	.LFB12:
 105:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** 
 106:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** int _read(int file, char *ptr, int len) {
 601              		.loc 1 106 41
 602              		.cfi_startproc
 603              		@ args = 0, pretend = 0, frame = 24
 604              		@ frame_needed = 1, uses_anonymous_args = 0
 605 0220 80B5     		push	{r7, lr}
 606              		.cfi_def_cfa_offset 8
 607              		.cfi_offset 7, -8
 608              		.cfi_offset 14, -4
 609 0222 86B0     		sub	sp, sp, #24
 610              		.cfi_def_cfa_offset 32
 611 0224 00AF     		add	r7, sp, #0
 612              		.cfi_def_cfa_register 7
 613 0226 F860     		str	r0, [r7, #12]
 614 0228 B960     		str	r1, [r7, #8]
 615 022a 7A60     		str	r2, [r7, #4]
 107:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     PDEV_DRIVER_DESC drvr;
 108:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     drvr = device_table[file];
 616              		.loc 1 108 10
 617 022c 0A4B     		ldr	r3, .L42
 618 022e FA68     		ldr	r2, [r7, #12]
 619 0230 9200     		lsls	r2, r2, #2
 620 0232 D358     		ldr	r3, [r2, r3]
 621 0234 7B61     		str	r3, [r7, #20]
 109:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     if(drvr == 0)
 622              		.loc 1 109 7
 623 0236 7B69     		ldr	r3, [r7, #20]
 624 0238 002B     		cmp	r3, #0
 625 023a 01D1     		bne	.L40
 110:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****         return 0;
 626              		.loc 1 110 16
 627 023c 0023     		movs	r3, #0
 628 023e 06E0     		b	.L41
 629              	.L40:
 111:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c ****     return drvr->read(ptr,len);
 630              		.loc 1 111 16
 631 0240 7B69     		ldr	r3, [r7, #20]
 632 0242 1B6B     		ldr	r3, [r3, #48]
 633              		.loc 1 111 12
 634 0244 7968     		ldr	r1, [r7, #4]
 635 0246 BA68     		ldr	r2, [r7, #8]
 636 0248 1000     		movs	r0, r2
 637 024a 9847     		blx	r3
 638              	.LVL3:
 639 024c 0300     		movs	r3, r0
 640              	.L41:
 112:/home/elvina/Dokument/MOP/laborationer/libMD407/general.c **** } ...
 641              		.loc 1 112 1
 642 024e 1800     		movs	r0, r3
 643 0250 BD46     		mov	sp, r7
 644 0252 06B0     		add	sp, sp, #24
 645              		@ sp needed
 646 0254 80BD     		pop	{r7, pc}
 647              	.L43:
 648 0256 C046     		.align	2
 649              	.L42:
 650 0258 00000000 		.word	device_table
 651              		.cfi_endproc
 652              	.LFE12:
 654              	.Letext0:
 655              		.file 2 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/machine/_default_types.h"
 656              		.file 3 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/lock.h"
 657              		.file 4 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/_types.h"
 658              		.file 5 "/usr/share/codelite/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/include/stddef.h"
 659              		.file 6 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/reent.h"
 660              		.file 7 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/types.h"
 661              		.file 8 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/errno.h"
 662              		.file 9 "/usr/share/codelite/tools/gcc-arm/arm-none-eabi/include/sys/stat.h"
 663              		.file 10 "/home/elvina/Dokument/MOP/laborationer/libMD407/libMD407.h"
