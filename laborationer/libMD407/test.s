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
  11              		.file	"usart_driver.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.global	StdIn
  16              		.data
  17              		.align	2
  20              	StdIn:
  21 0000 73746469 		.ascii	"stdin\000"
  21      6E00
  22 0006 00000000 		.space	10
  22      00000000 
  22      0000
  23 0010 00000000 		.word	usart_init
  24 0014 00000000 		.word	usart_deinit
  25 0018 00000000 		.word	0
  26 001c 00000000 		.word	_isatty
  27 0020 00000000 		.word	0
  28 0024 00000000 		.word	0
  29 0028 00000000 		.word	0
  30 002c 00000000 		.word	0
  31 0030 00000000 		.word	usart_read
  32              		.global	StdOut
  33              		.align	2
  36              	StdOut:
  37 0034 7374646F 		.ascii	"stdout\000"
  37      757400
  38 003b 00000000 		.space	9
  38      00000000 
  38      00
  39 0044 00000000 		.word	usart_init
  40 0048 00000000 		.word	usart_deinit
  41 004c 00000000 		.word	0
  42 0050 00000000 		.word	_isatty
  43 0054 00000000 		.word	0
  44 0058 00000000 		.word	0
  45 005c 00000000 		.word	0
  46 0060 00000000 		.word	usart_write
  47 0064 00000000 		.word	0
  48              		.global	StdErr
  49              		.align	2
  52              	StdErr:
  53 0068 73746465 		.ascii	"stderr\000"
  53      727200
  54 006f 00000000 		.space	9
  54      00000000 
  54      00
  55 0078 00000000 		.word	usart_init
  56 007c 00000000 		.word	usart_deinit
  57 0080 00000000 		.word	0
  58 0084 00000000 		.word	_isatty
  59 0088 00000000 		.word	0
  60 008c 00000000 		.word	0
  61 0090 00000000 		.word	0
  62 0094 00000000 		.word	usart_write
  63 0098 00000000 		.word	0
  64              		.text
  65              		.align	1
  66              		.syntax unified
  67              		.code	16
  68              		.thumb_func
  69              		.fpu softvfp
  71              	usart_init:
  72              	.LFB3:
  73              		.file 1 "D:/mop/laborationer/libMD407/usart_driver.c"
   1:D:/mop/laborationer/libMD407\usart_driver.c **** /*
   2:D:/mop/laborationer/libMD407\usart_driver.c ****  * libMD407
   3:D:/mop/laborationer/libMD407\usart_driver.c ****  * usart_driver.c
   4:D:/mop/laborationer/libMD407\usart_driver.c ****  * USART driver
   5:D:/mop/laborationer/libMD407\usart_driver.c ****  * Drivers for STDIN, STDOUT and STDERR
   6:D:/mop/laborationer/libMD407\usart_driver.c ****  */
   7:D:/mop/laborationer/libMD407\usart_driver.c ****  
   8:D:/mop/laborationer/libMD407\usart_driver.c **** #include "libMD407.h"
   9:D:/mop/laborationer/libMD407\usart_driver.c **** 
  10:D:/mop/laborationer/libMD407\usart_driver.c **** /* Define functions here */
  11:D:/mop/laborationer/libMD407\usart_driver.c **** 
  12:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_init( int initval );
  13:D:/mop/laborationer/libMD407\usart_driver.c **** static void usart_deinit( int deinitval);
  14:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_write(char *ptr, int len);
  15:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_read(char *ptr, int len);
  16:D:/mop/laborationer/libMD407\usart_driver.c **** 
  17:D:/mop/laborationer/libMD407\usart_driver.c **** DEV_DRIVER_DESC StdIn =
  18:D:/mop/laborationer/libMD407\usart_driver.c **** {
  19:D:/mop/laborationer/libMD407\usart_driver.c **** 	{"stdin"},
  20:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_init,
  21:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_deinit,
  22:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  23:D:/mop/laborationer/libMD407\usart_driver.c **** 	_isatty,
  24:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  25:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  26:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  27:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  28:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_read
  29:D:/mop/laborationer/libMD407\usart_driver.c **** };
  30:D:/mop/laborationer/libMD407\usart_driver.c **** 
  31:D:/mop/laborationer/libMD407\usart_driver.c **** DEV_DRIVER_DESC StdOut =
  32:D:/mop/laborationer/libMD407\usart_driver.c **** {
  33:D:/mop/laborationer/libMD407\usart_driver.c **** 	{"stdout"},
  34:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_init,
  35:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_deinit,
  36:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  37:D:/mop/laborationer/libMD407\usart_driver.c **** 	_isatty,
  38:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  39:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  40:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  41:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_write,
  42:D:/mop/laborationer/libMD407\usart_driver.c **** 	0
  43:D:/mop/laborationer/libMD407\usart_driver.c **** };
  44:D:/mop/laborationer/libMD407\usart_driver.c **** 
  45:D:/mop/laborationer/libMD407\usart_driver.c **** DEV_DRIVER_DESC StdErr =
  46:D:/mop/laborationer/libMD407\usart_driver.c **** {
  47:D:/mop/laborationer/libMD407\usart_driver.c **** 	{"stderr"},
  48:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_init,
  49:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_deinit,
  50:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  51:D:/mop/laborationer/libMD407\usart_driver.c **** 	_isatty,
  52:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  53:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  54:D:/mop/laborationer/libMD407\usart_driver.c **** 	0,
  55:D:/mop/laborationer/libMD407\usart_driver.c **** 	usart_write,
  56:D:/mop/laborationer/libMD407\usart_driver.c **** 	0
  57:D:/mop/laborationer/libMD407\usart_driver.c **** };
  58:D:/mop/laborationer/libMD407\usart_driver.c **** 
  59:D:/mop/laborationer/libMD407\usart_driver.c **** /* USART types and constants definitions */
  60:D:/mop/laborationer/libMD407\usart_driver.c **** #define BIT_UE		(1<<13)
  61:D:/mop/laborationer/libMD407\usart_driver.c **** #define BIT_TE		(1<<3)
  62:D:/mop/laborationer/libMD407\usart_driver.c **** #define	BIT_RE		(1<<2)
  63:D:/mop/laborationer/libMD407\usart_driver.c **** 
  64:D:/mop/laborationer/libMD407\usart_driver.c **** // till _tstchar
  65:D:/mop/laborationer/libMD407\usart_driver.c **** #define BIT_RXNE	(1<<5)
  66:D:/mop/laborationer/libMD407\usart_driver.c **** #define	BIT_TXE		(1<<7)
  67:D:/mop/laborationer/libMD407\usart_driver.c **** 
  68:D:/mop/laborationer/libMD407\usart_driver.c **** // Usart registers
  69:D:/mop/laborationer/libMD407\usart_driver.c **** typedef struct
  70:D:/mop/laborationer/libMD407\usart_driver.c **** {
  71:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short sr;
  72:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused0;
  73:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short dr;
  74:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused1;
  75:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short brr;
  76:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused2;
  77:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short cr1;
  78:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused3;
  79:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short cr2;
  80:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused4;
  81:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short cr3;
  82:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short Unused5;
  83:D:/mop/laborationer/libMD407\usart_driver.c **** 	volatile unsigned short gtpr;
  84:D:/mop/laborationer/libMD407\usart_driver.c **** } USART;
  85:D:/mop/laborationer/libMD407\usart_driver.c **** 
  86:D:/mop/laborationer/libMD407\usart_driver.c **** #define USART1 ((USART*)0x40011000)
  87:D:/mop/laborationer/libMD407\usart_driver.c **** 
  88:D:/mop/laborationer/libMD407\usart_driver.c **** /* USART implementation */
  89:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_init( int initval ) { 
  74              		.loc 1 89 38
  75              		.cfi_startproc
  76              		@ args = 0, pretend = 0, frame = 8
  77              		@ frame_needed = 1, uses_anonymous_args = 0
  78 0000 80B5     		push	{r7, lr}
  79              		.cfi_def_cfa_offset 8
  80              		.cfi_offset 7, -8
  81              		.cfi_offset 14, -4
  82 0002 82B0     		sub	sp, sp, #8
  83              		.cfi_def_cfa_offset 16
  84 0004 00AF     		add	r7, sp, #0
  85              		.cfi_def_cfa_register 7
  86 0006 7860     		str	r0, [r7, #4]
  90:D:/mop/laborationer/libMD407\usart_driver.c ****     // Baudraten bestäms som vi tidigare sett i BRR
  91:D:/mop/laborationer/libMD407\usart_driver.c **** 	USART1->brr = 0x2D9;
  87              		.loc 1 91 8
  88 0008 064B     		ldr	r3, .L3
  89              		.loc 1 91 14
  90 000a 074A     		ldr	r2, .L3+4
  91 000c 1A81     		strh	r2, [r3, #8]
  92:D:/mop/laborationer/libMD407\usart_driver.c **** 	// Antalet stoppbitar bestäms i CR2
  93:D:/mop/laborationer/libMD407\usart_driver.c **** 	USART1->cr2 = 0;
  92              		.loc 1 93 8
  93 000e 054B     		ldr	r3, .L3
  94              		.loc 1 93 14
  95 0010 0022     		movs	r2, #0
  96 0012 1A82     		strh	r2, [r3, #16]
  94:D:/mop/laborationer/libMD407\usart_driver.c **** 	/*
  95:D:/mop/laborationer/libMD407\usart_driver.c **** 	* Kretsen aktiveras genom CR1, 
  96:D:/mop/laborationer/libMD407\usart_driver.c **** 	* här bestäms också ramens längd och antal bitar
  97:D:/mop/laborationer/libMD407\usart_driver.c **** 	*/
  98:D:/mop/laborationer/libMD407\usart_driver.c **** 	USART1->cr1 = BIT_UE | BIT_TE | BIT_RE;
  97              		.loc 1 98 8
  98 0014 034B     		ldr	r3, .L3
  99              		.loc 1 98 14
 100 0016 054A     		ldr	r2, .L3+8
 101 0018 9A81     		strh	r2, [r3, #12]
  99:D:/mop/laborationer/libMD407\usart_driver.c ****     
 100:D:/mop/laborationer/libMD407\usart_driver.c ****     return 1;
 102              		.loc 1 100 12
 103 001a 0123     		movs	r3, #1
 101:D:/mop/laborationer/libMD407\usart_driver.c **** }
 104              		.loc 1 101 1
 105 001c 1800     		movs	r0, r3
 106 001e BD46     		mov	sp, r7
 107 0020 02B0     		add	sp, sp, #8
 108              		@ sp needed
 109 0022 80BD     		pop	{r7, pc}
 110              	.L4:
 111              		.align	2
 112              	.L3:
 113 0024 00100140 		.word	1073811456
 114 0028 D9020000 		.word	729
 115 002c 0C200000 		.word	8204
 116              		.cfi_endproc
 117              	.LFE3:
 119              		.align	1
 120              		.syntax unified
 121              		.code	16
 122              		.thumb_func
 123              		.fpu softvfp
 125              	usart_deinit:
 126              	.LFB4:
 102:D:/mop/laborationer/libMD407\usart_driver.c **** 
 103:D:/mop/laborationer/libMD407\usart_driver.c **** static void usart_deinit( int deinitval){/* funktion för när vi är färdiga med usart */
 127              		.loc 1 103 41
 128              		.cfi_startproc
 129              		@ args = 0, pretend = 0, frame = 8
 130              		@ frame_needed = 1, uses_anonymous_args = 0
 131 0030 80B5     		push	{r7, lr}
 132              		.cfi_def_cfa_offset 8
 133              		.cfi_offset 7, -8
 134              		.cfi_offset 14, -4
 135 0032 82B0     		sub	sp, sp, #8
 136              		.cfi_def_cfa_offset 16
 137 0034 00AF     		add	r7, sp, #0
 138              		.cfi_def_cfa_register 7
 139 0036 7860     		str	r0, [r7, #4]
 104:D:/mop/laborationer/libMD407\usart_driver.c ****     /* stäng av interrupt */
 105:D:/mop/laborationer/libMD407\usart_driver.c ****     USART1->cr1 = 0;
 140              		.loc 1 105 11
 141 0038 034B     		ldr	r3, .L6
 142              		.loc 1 105 17
 143 003a 0022     		movs	r2, #0
 144 003c 9A81     		strh	r2, [r3, #12]
 106:D:/mop/laborationer/libMD407\usart_driver.c **** }
 145              		.loc 1 106 1
 146 003e C046     		nop
 147 0040 BD46     		mov	sp, r7
 148 0042 02B0     		add	sp, sp, #8
 149              		@ sp needed
 150 0044 80BD     		pop	{r7, pc}
 151              	.L7:
 152 0046 C046     		.align	2
 153              	.L6:
 154 0048 00100140 		.word	1073811456
 155              		.cfi_endproc
 156              	.LFE4:
 158              		.align	1
 159              		.global	_tstchar
 160              		.syntax unified
 161              		.code	16
 162              		.thumb_func
 163              		.fpu softvfp
 165              	_tstchar:
 166              	.LFB5:
 107:D:/mop/laborationer/libMD407\usart_driver.c **** 
 108:D:/mop/laborationer/libMD407\usart_driver.c **** /* funktioner från usart_polling */
 109:D:/mop/laborationer/libMD407\usart_driver.c **** char _tstchar( void )
 110:D:/mop/laborationer/libMD407\usart_driver.c **** {
 167              		.loc 1 110 1
 168              		.cfi_startproc
 169              		@ args = 0, pretend = 0, frame = 0
 170              		@ frame_needed = 1, uses_anonymous_args = 0
 171 004c 80B5     		push	{r7, lr}
 172              		.cfi_def_cfa_offset 8
 173              		.cfi_offset 7, -8
 174              		.cfi_offset 14, -4
 175 004e 00AF     		add	r7, sp, #0
 176              		.cfi_def_cfa_register 7
 111:D:/mop/laborationer/libMD407\usart_driver.c **** 	if( (USART1->sr & BIT_RXNE ) == BIT_RXNE)
 177              		.loc 1 111 13
 178 0050 084B     		ldr	r3, .L11
 179 0052 1B88     		ldrh	r3, [r3]
 180 0054 9BB2     		uxth	r3, r3
 181              		.loc 1 111 18
 182 0056 1A00     		movs	r2, r3
 183 0058 2023     		movs	r3, #32
 184 005a 1340     		ands	r3, r2
 185              		.loc 1 111 4
 186 005c 202B     		cmp	r3, #32
 187 005e 04D1     		bne	.L9
 112:D:/mop/laborationer/libMD407\usart_driver.c **** 		return (char) USART1->dr;
 188              		.loc 1 112 23
 189 0060 044B     		ldr	r3, .L11
 190 0062 9B88     		ldrh	r3, [r3, #4]
 191 0064 9BB2     		uxth	r3, r3
 192              		.loc 1 112 10
 193 0066 DBB2     		uxtb	r3, r3
 194 0068 00E0     		b	.L10
 195              	.L9:
 113:D:/mop/laborationer/libMD407\usart_driver.c **** 	return 0;
 196              		.loc 1 113 9
 197 006a 0023     		movs	r3, #0
 198              	.L10:
 114:D:/mop/laborationer/libMD407\usart_driver.c **** }
 199              		.loc 1 114 1
 200 006c 1800     		movs	r0, r3
 201 006e BD46     		mov	sp, r7
 202              		@ sp needed
 203 0070 80BD     		pop	{r7, pc}
 204              	.L12:
 205 0072 C046     		.align	2
 206              	.L11:
 207 0074 00100140 		.word	1073811456
 208              		.cfi_endproc
 209              	.LFE5:
 211              		.align	1
 212              		.global	_outchar
 213              		.syntax unified
 214              		.code	16
 215              		.thumb_func
 216              		.fpu softvfp
 218              	_outchar:
 219              	.LFB6:
 115:D:/mop/laborationer/libMD407\usart_driver.c **** 
 116:D:/mop/laborationer/libMD407\usart_driver.c **** void _outchar( char c )
 117:D:/mop/laborationer/libMD407\usart_driver.c **** {
 220              		.loc 1 117 1
 221              		.cfi_startproc
 222              		@ args = 0, pretend = 0, frame = 8
 223              		@ frame_needed = 1, uses_anonymous_args = 0
 224 0078 80B5     		push	{r7, lr}
 225              		.cfi_def_cfa_offset 8
 226              		.cfi_offset 7, -8
 227              		.cfi_offset 14, -4
 228 007a 82B0     		sub	sp, sp, #8
 229              		.cfi_def_cfa_offset 16
 230 007c 00AF     		add	r7, sp, #0
 231              		.cfi_def_cfa_register 7
 232 007e 0200     		movs	r2, r0
 233 0080 FB1D     		adds	r3, r7, #7
 234 0082 1A70     		strb	r2, [r3]
 118:D:/mop/laborationer/libMD407\usart_driver.c **** 	while (( USART1->sr & BIT_TXE ) == 0 );
 235              		.loc 1 118 8
 236 0084 C046     		nop
 237              	.L14:
 238              		.loc 1 118 17 discriminator 1
 239 0086 0B4B     		ldr	r3, .L17
 240 0088 1B88     		ldrh	r3, [r3]
 241 008a 9BB2     		uxth	r3, r3
 242              		.loc 1 118 22 discriminator 1
 243 008c 1A00     		movs	r2, r3
 244 008e 8023     		movs	r3, #128
 245 0090 1340     		ands	r3, r2
 246              		.loc 1 118 8 discriminator 1
 247 0092 F8D0     		beq	.L14
 119:D:/mop/laborationer/libMD407\usart_driver.c **** 	USART1->dr = (unsigned short) c;
 248              		.loc 1 119 8
 249 0094 074A     		ldr	r2, .L17
 250              		.loc 1 119 15
 251 0096 FB1D     		adds	r3, r7, #7
 252 0098 1B78     		ldrb	r3, [r3]
 253 009a 9BB2     		uxth	r3, r3
 254              		.loc 1 119 13
 255 009c 9380     		strh	r3, [r2, #4]
 120:D:/mop/laborationer/libMD407\usart_driver.c ****     if( c == '\n') _outchar('\r'); 
 256              		.loc 1 120 7
 257 009e FB1D     		adds	r3, r7, #7
 258 00a0 1B78     		ldrb	r3, [r3]
 259 00a2 0A2B     		cmp	r3, #10
 260 00a4 02D1     		bne	.L16
 261              		.loc 1 120 20 discriminator 1
 262 00a6 0D20     		movs	r0, #13
 263 00a8 FFF7FEFF 		bl	_outchar
 264              	.L16:
 121:D:/mop/laborationer/libMD407\usart_driver.c **** }	
 265              		.loc 1 121 1
 266 00ac C046     		nop
 267 00ae BD46     		mov	sp, r7
 268 00b0 02B0     		add	sp, sp, #8
 269              		@ sp needed
 270 00b2 80BD     		pop	{r7, pc}
 271              	.L18:
 272              		.align	2
 273              	.L17:
 274 00b4 00100140 		.word	1073811456
 275              		.cfi_endproc
 276              	.LFE6:
 278              		.align	1
 279              		.syntax unified
 280              		.code	16
 281              		.thumb_func
 282              		.fpu softvfp
 284              	usart_write:
 285              	.LFB7:
 122:D:/mop/laborationer/libMD407\usart_driver.c **** 
 123:D:/mop/laborationer/libMD407\usart_driver.c **** 
 124:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_write(char *ptr, int len){ 
 286              		.loc 1 124 43
 287              		.cfi_startproc
 288              		@ args = 0, pretend = 0, frame = 16
 289              		@ frame_needed = 1, uses_anonymous_args = 0
 290 00b8 80B5     		push	{r7, lr}
 291              		.cfi_def_cfa_offset 8
 292              		.cfi_offset 7, -8
 293              		.cfi_offset 14, -4
 294 00ba 84B0     		sub	sp, sp, #16
 295              		.cfi_def_cfa_offset 24
 296 00bc 00AF     		add	r7, sp, #0
 297              		.cfi_def_cfa_register 7
 298 00be 7860     		str	r0, [r7, #4]
 299 00c0 3960     		str	r1, [r7]
 125:D:/mop/laborationer/libMD407\usart_driver.c ****     
 126:D:/mop/laborationer/libMD407\usart_driver.c ****     int len0 = len;
 300              		.loc 1 126 9
 301 00c2 3B68     		ldr	r3, [r7]
 302 00c4 FB60     		str	r3, [r7, #12]
 127:D:/mop/laborationer/libMD407\usart_driver.c ****     
 128:D:/mop/laborationer/libMD407\usart_driver.c ****     while(len--)
 303              		.loc 1 128 10
 304 00c6 06E0     		b	.L20
 305              	.L21:
 129:D:/mop/laborationer/libMD407\usart_driver.c ****         _outchar(*ptr++);
 306              		.loc 1 129 22
 307 00c8 7B68     		ldr	r3, [r7, #4]
 308 00ca 5A1C     		adds	r2, r3, #1
 309 00cc 7A60     		str	r2, [r7, #4]
 310              		.loc 1 129 9
 311 00ce 1B78     		ldrb	r3, [r3]
 312 00d0 1800     		movs	r0, r3
 313 00d2 FFF7FEFF 		bl	_outchar
 314              	.L20:
 128:D:/mop/laborationer/libMD407\usart_driver.c ****         _outchar(*ptr++);
 315              		.loc 1 128 14
 316 00d6 3B68     		ldr	r3, [r7]
 317 00d8 5A1E     		subs	r2, r3, #1
 318 00da 3A60     		str	r2, [r7]
 128:D:/mop/laborationer/libMD407\usart_driver.c ****         _outchar(*ptr++);
 319              		.loc 1 128 10
 320 00dc 002B     		cmp	r3, #0
 321 00de F3D1     		bne	.L21
 130:D:/mop/laborationer/libMD407\usart_driver.c ****     
 131:D:/mop/laborationer/libMD407\usart_driver.c ****     return len0;
 322              		.loc 1 131 12
 323 00e0 FB68     		ldr	r3, [r7, #12]
 132:D:/mop/laborationer/libMD407\usart_driver.c ****     	
 133:D:/mop/laborationer/libMD407\usart_driver.c **** 	
 134:D:/mop/laborationer/libMD407\usart_driver.c **** }
 324              		.loc 1 134 1
 325 00e2 1800     		movs	r0, r3
 326 00e4 BD46     		mov	sp, r7
 327 00e6 04B0     		add	sp, sp, #16
 328              		@ sp needed
 329 00e8 80BD     		pop	{r7, pc}
 330              		.cfi_endproc
 331              	.LFE7:
 333              		.align	1
 334              		.syntax unified
 335              		.code	16
 336              		.thumb_func
 337              		.fpu softvfp
 339              	usart_read:
 340              	.LFB8:
 135:D:/mop/laborationer/libMD407\usart_driver.c **** 
 136:D:/mop/laborationer/libMD407\usart_driver.c **** static int usart_read(char *ptr, int len){
 341              		.loc 1 136 42
 342              		.cfi_startproc
 343              		@ args = 0, pretend = 0, frame = 16
 344              		@ frame_needed = 1, uses_anonymous_args = 0
 345 00ea 90B5     		push	{r4, r7, lr}
 346              		.cfi_def_cfa_offset 12
 347              		.cfi_offset 4, -12
 348              		.cfi_offset 7, -8
 349              		.cfi_offset 14, -4
 350 00ec 85B0     		sub	sp, sp, #20
 351              		.cfi_def_cfa_offset 32
 352 00ee 00AF     		add	r7, sp, #0
 353              		.cfi_def_cfa_register 7
 354 00f0 7860     		str	r0, [r7, #4]
 355 00f2 3960     		str	r1, [r7]
 137:D:/mop/laborationer/libMD407\usart_driver.c ****     int len0 = len;
 356              		.loc 1 137 9
 357 00f4 3B68     		ldr	r3, [r7]
 358 00f6 FB60     		str	r3, [r7, #12]
 138:D:/mop/laborationer/libMD407\usart_driver.c ****     
 139:D:/mop/laborationer/libMD407\usart_driver.c ****     while(len--)
 359              		.loc 1 139 10
 360 00f8 06E0     		b	.L24
 361              	.L25:
 140:D:/mop/laborationer/libMD407\usart_driver.c ****         *ptr++ = _tstchar();
 362              		.loc 1 140 13
 363 00fa 7C68     		ldr	r4, [r7, #4]
 364 00fc 631C     		adds	r3, r4, #1
 365 00fe 7B60     		str	r3, [r7, #4]
 366              		.loc 1 140 18
 367 0100 FFF7FEFF 		bl	_tstchar
 368 0104 0300     		movs	r3, r0
 369              		.loc 1 140 16
 370 0106 2370     		strb	r3, [r4]
 371              	.L24:
 139:D:/mop/laborationer/libMD407\usart_driver.c ****         *ptr++ = _tstchar();
 372              		.loc 1 139 14
 373 0108 3B68     		ldr	r3, [r7]
 374 010a 5A1E     		subs	r2, r3, #1
 375 010c 3A60     		str	r2, [r7]
 139:D:/mop/laborationer/libMD407\usart_driver.c ****         *ptr++ = _tstchar();
 376              		.loc 1 139 10
 377 010e 002B     		cmp	r3, #0
 378 0110 F3D1     		bne	.L25
 141:D:/mop/laborationer/libMD407\usart_driver.c ****     
 142:D:/mop/laborationer/libMD407\usart_driver.c ****     return len0;
 379              		.loc 1 142 12
 380 0112 FB68     		ldr	r3, [r7, #12]
 143:D:/mop/laborationer/libMD407\usart_driver.c **** 
 144:D:/mop/laborationer/libMD407\usart_driver.c **** } ...
 381              		.loc 1 144 1
 382 0114 1800     		movs	r0, r3
 383 0116 BD46     		mov	sp, r7
 384 0118 05B0     		add	sp, sp, #20
 385              		@ sp needed
 386 011a 90BD     		pop	{r4, r7, pc}
 387              		.cfi_endproc
 388              	.LFE8:
 390              	.Letext0:
 391              		.file 2 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\machine\\_default_ty
 392              		.file 3 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\lock.h"
 393              		.file 4 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\_types.h"
 394              		.file 5 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\lib\\gcc\\arm-none-eabi\\9.2.1\\include\\std
 395              		.file 6 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\reent.h"
 396              		.file 7 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\types.h"
 397              		.file 8 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\errno.h"
 398              		.file 9 "d:\\nedladdningar\\codelite\\tools\\gcc-arm\\arm-none-eabi\\include\\sys\\stat.h"
 399              		.file 10 "D:/mop/laborationer/libMD407/libMD407.h"
