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
  11              		.file	"delay.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.section	.start_section,"ax",%progbits
  16              		.align	1
  17              		.global	startup
  18              		.syntax unified
  19              		.code	16
  20              		.thumb_func
  21              		.fpu softvfp
  23              	startup:
  24              	.LFB0:
  25              		.file 1 "D:/mop/laborationer/5-3/delay.c"
   1:D:/mop/laborationer/5-3\delay.c **** /*
   2:D:/mop/laborationer/5-3\delay.c ****  * 	startup.c
   3:D:/mop/laborationer/5-3\delay.c ****  *
   4:D:/mop/laborationer/5-3\delay.c ****  */
   5:D:/mop/laborationer/5-3\delay.c **** __attribute__((naked)) __attribute__((section (".start_section")) )
   6:D:/mop/laborationer/5-3\delay.c **** void startup ( void )
   7:D:/mop/laborationer/5-3\delay.c **** {
  26              		.loc 1 7 1
  27              		.cfi_startproc
  28              		@ Naked Function: prologue and epilogue provided by programmer.
  29              		@ args = 0, pretend = 0, frame = 0
  30              		@ frame_needed = 1, uses_anonymous_args = 0
   8:D:/mop/laborationer/5-3\delay.c **** __asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
  31              		.loc 1 8 1
  32              		.syntax divided
  33              	@ 8 "D:/mop/laborationer/5-3/delay.c" 1
  34 0000 0248     		 LDR R0,=0x2001C000
  35              	
  36              	@ 0 "" 2
   9:D:/mop/laborationer/5-3\delay.c **** __asm__ volatile(" MOV SP,R0\n");
  37              		.loc 1 9 1
  38              	@ 9 "D:/mop/laborationer/5-3/delay.c" 1
  39 0002 8546     		 MOV SP,R0
  40              	
  41              	@ 0 "" 2
  10:D:/mop/laborationer/5-3\delay.c **** __asm__ volatile(" BL main\n");					/* call main */
  42              		.loc 1 10 1
  43              	@ 10 "D:/mop/laborationer/5-3/delay.c" 1
  44 0004 FFF7FEFF 		 BL main
  45              	
  46              	@ 0 "" 2
  11:D:/mop/laborationer/5-3\delay.c **** __asm__ volatile(".L1: B .L1\n");				/* never return */
  47              		.loc 1 11 1
  48              	@ 11 "D:/mop/laborationer/5-3/delay.c" 1
  49 0008 FEE7     		.L1: B .L1
  50              	
  51              	@ 0 "" 2
  12:D:/mop/laborationer/5-3\delay.c **** }
  52              		.loc 1 12 1
  53              		.thumb
  54              		.syntax unified
  55 000a C046     		nop
  56              		.cfi_endproc
  57              	.LFE0:
  59              		.text
  60              		.align	1
  61              		.global	init_app
  62              		.syntax unified
  63              		.code	16
  64              		.thumb_func
  65              		.fpu softvfp
  67              	init_app:
  68              	.LFB1:
  13:D:/mop/laborationer/5-3\delay.c **** 
  14:D:/mop/laborationer/5-3\delay.c **** #define STK_CTRL ((volatile unsigned int *)(0xE000E010))
  15:D:/mop/laborationer/5-3\delay.c **** #define STK_LOAD ((volatile unsigned int *)(0xE000E014))
  16:D:/mop/laborationer/5-3\delay.c **** #define STK_VAL ((volatile unsigned int *)(0xE000E018))
  17:D:/mop/laborationer/5-3\delay.c **** #define SIMULATOR 
  18:D:/mop/laborationer/5-3\delay.c **** #define GPIO_MODER ((volatile unsigned int *) 0x40021000)
  19:D:/mop/laborationer/5-3\delay.c **** #define Bargraph ((volatile unsigned char *) 0x40021014)
  20:D:/mop/laborationer/5-3\delay.c **** 
  21:D:/mop/laborationer/5-3\delay.c **** void init_app(void)
  22:D:/mop/laborationer/5-3\delay.c **** {
  69              		.loc 1 22 1
  70              		.cfi_startproc
  71              		@ args = 0, pretend = 0, frame = 0
  72              		@ frame_needed = 1, uses_anonymous_args = 0
  73 0000 80B5     		push	{r7, lr}
  74              		.cfi_def_cfa_offset 8
  75              		.cfi_offset 7, -8
  76              		.cfi_offset 14, -4
  77 0002 00AF     		add	r7, sp, #0
  78              		.cfi_def_cfa_register 7
  23:D:/mop/laborationer/5-3\delay.c ****     * ( (unsigned long *) 0x40021000) = 0x00005555;  // GPIO_MODER initieras
  79              		.loc 1 23 5
  80 0004 044B     		ldr	r3, .L3
  81              		.loc 1 23 39
  82 0006 054A     		ldr	r2, .L3+4
  83 0008 1A60     		str	r2, [r3]
  24:D:/mop/laborationer/5-3\delay.c ****     * ( (unsigned char *) 0x40021014) = 0x0;
  84              		.loc 1 24 5
  85 000a 054B     		ldr	r3, .L3+8
  86              		.loc 1 24 39
  87 000c 0022     		movs	r2, #0
  88 000e 1A70     		strb	r2, [r3]
  25:D:/mop/laborationer/5-3\delay.c **** 
  26:D:/mop/laborationer/5-3\delay.c **** }
  89              		.loc 1 26 1
  90 0010 C046     		nop
  91 0012 BD46     		mov	sp, r7
  92              		@ sp needed
  93 0014 80BD     		pop	{r7, pc}
  94              	.L4:
  95 0016 C046     		.align	2
  96              	.L3:
  97 0018 00100240 		.word	1073876992
  98 001c 55550000 		.word	21845
  99 0020 14100240 		.word	1073877012
 100              		.cfi_endproc
 101              	.LFE1:
 103              		.align	1
 104              		.global	delay_250ns
 105              		.syntax unified
 106              		.code	16
 107              		.thumb_func
 108              		.fpu softvfp
 110              	delay_250ns:
 111              	.LFB2:
  27:D:/mop/laborationer/5-3\delay.c **** 
  28:D:/mop/laborationer/5-3\delay.c **** 
  29:D:/mop/laborationer/5-3\delay.c **** void delay_250ns( void )
  30:D:/mop/laborationer/5-3\delay.c **** {
 112              		.loc 1 30 1
 113              		.cfi_startproc
 114              		@ args = 0, pretend = 0, frame = 0
 115              		@ frame_needed = 1, uses_anonymous_args = 0
 116 0024 80B5     		push	{r7, lr}
 117              		.cfi_def_cfa_offset 8
 118              		.cfi_offset 7, -8
 119              		.cfi_offset 14, -4
 120 0026 00AF     		add	r7, sp, #0
 121              		.cfi_def_cfa_register 7
  31:D:/mop/laborationer/5-3\delay.c ****     /* SystemCoreClock = 168000000 */
  32:D:/mop/laborationer/5-3\delay.c ****     *STK_CTRL = 0;
 122              		.loc 1 32 5
 123 0028 0C4B     		ldr	r3, .L7
 124              		.loc 1 32 15
 125 002a 0022     		movs	r2, #0
 126 002c 1A60     		str	r2, [r3]
  33:D:/mop/laborationer/5-3\delay.c ****     *STK_LOAD = ( (168/4) -1 );
 127              		.loc 1 33 5
 128 002e 0C4B     		ldr	r3, .L7+4
 129              		.loc 1 33 15
 130 0030 2922     		movs	r2, #41
 131 0032 1A60     		str	r2, [r3]
  34:D:/mop/laborationer/5-3\delay.c ****     *STK_VAL = 0;
 132              		.loc 1 34 5
 133 0034 0B4B     		ldr	r3, .L7+8
 134              		.loc 1 34 14
 135 0036 0022     		movs	r2, #0
 136 0038 1A60     		str	r2, [r3]
  35:D:/mop/laborationer/5-3\delay.c ****     *STK_CTRL = 5;  //sätter enable och clksource
 137              		.loc 1 35 5
 138 003a 084B     		ldr	r3, .L7
 139              		.loc 1 35 15
 140 003c 0522     		movs	r2, #5
 141 003e 1A60     		str	r2, [r3]
  36:D:/mop/laborationer/5-3\delay.c ****     // börjar räkna
  37:D:/mop/laborationer/5-3\delay.c ****     while( (*STK_CTRL & 0x10000 )== 0 );    //vänta till countflag=1
 142              		.loc 1 37 10
 143 0040 C046     		nop
 144              	.L6:
 145              		.loc 1 37 13 discriminator 1
 146 0042 064B     		ldr	r3, .L7
 147 0044 1A68     		ldr	r2, [r3]
 148              		.loc 1 37 23 discriminator 1
 149 0046 8023     		movs	r3, #128
 150 0048 5B02     		lsls	r3, r3, #9
 151 004a 1340     		ands	r3, r2
 152              		.loc 1 37 10 discriminator 1
 153 004c F9D0     		beq	.L6
  38:D:/mop/laborationer/5-3\delay.c ****     *STK_CTRL = 0;
 154              		.loc 1 38 5
 155 004e 034B     		ldr	r3, .L7
 156              		.loc 1 38 15
 157 0050 0022     		movs	r2, #0
 158 0052 1A60     		str	r2, [r3]
  39:D:/mop/laborationer/5-3\delay.c **** }
 159              		.loc 1 39 1
 160 0054 C046     		nop
 161 0056 BD46     		mov	sp, r7
 162              		@ sp needed
 163 0058 80BD     		pop	{r7, pc}
 164              	.L8:
 165 005a C046     		.align	2
 166              	.L7:
 167 005c 10E000E0 		.word	-536813552
 168 0060 14E000E0 		.word	-536813548
 169 0064 18E000E0 		.word	-536813544
 170              		.cfi_endproc
 171              	.LFE2:
 173              		.global	__aeabi_uidiv
 174              		.align	1
 175              		.global	delay_micro
 176              		.syntax unified
 177              		.code	16
 178              		.thumb_func
 179              		.fpu softvfp
 181              	delay_micro:
 182              	.LFB3:
  40:D:/mop/laborationer/5-3\delay.c **** 
  41:D:/mop/laborationer/5-3\delay.c **** void delay_micro(unsigned int us)
  42:D:/mop/laborationer/5-3\delay.c **** {
 183              		.loc 1 42 1
 184              		.cfi_startproc
 185              		@ args = 0, pretend = 0, frame = 8
 186              		@ frame_needed = 1, uses_anonymous_args = 0
 187 0068 80B5     		push	{r7, lr}
 188              		.cfi_def_cfa_offset 8
 189              		.cfi_offset 7, -8
 190              		.cfi_offset 14, -4
 191 006a 82B0     		sub	sp, sp, #8
 192              		.cfi_def_cfa_offset 16
 193 006c 00AF     		add	r7, sp, #0
 194              		.cfi_def_cfa_register 7
 195 006e 7860     		str	r0, [r7, #4]
  43:D:/mop/laborationer/5-3\delay.c **** #ifdef SIMULATOR
  44:D:/mop/laborationer/5-3\delay.c ****     us = us / 1000;
 196              		.loc 1 44 8
 197 0070 7B68     		ldr	r3, [r7, #4]
 198 0072 FA22     		movs	r2, #250
 199 0074 9100     		lsls	r1, r2, #2
 200 0076 1800     		movs	r0, r3
 201 0078 FFF7FEFF 		bl	__aeabi_uidiv
 202              	.LVL0:
 203 007c 0300     		movs	r3, r0
 204 007e 7B60     		str	r3, [r7, #4]
  45:D:/mop/laborationer/5-3\delay.c ****     us++;
 205              		.loc 1 45 7
 206 0080 7B68     		ldr	r3, [r7, #4]
 207 0082 0133     		adds	r3, r3, #1
 208 0084 7B60     		str	r3, [r7, #4]
  46:D:/mop/laborationer/5-3\delay.c **** #endif
  47:D:/mop/laborationer/5-3\delay.c ****     while( us > 0 )
 209              		.loc 1 47 10
 210 0086 0AE0     		b	.L10
 211              	.L11:
  48:D:/mop/laborationer/5-3\delay.c ****     {
  49:D:/mop/laborationer/5-3\delay.c ****         delay_250ns();
 212              		.loc 1 49 9
 213 0088 FFF7FEFF 		bl	delay_250ns
  50:D:/mop/laborationer/5-3\delay.c ****         delay_250ns();
 214              		.loc 1 50 9
 215 008c FFF7FEFF 		bl	delay_250ns
  51:D:/mop/laborationer/5-3\delay.c ****         delay_250ns();
 216              		.loc 1 51 9
 217 0090 FFF7FEFF 		bl	delay_250ns
  52:D:/mop/laborationer/5-3\delay.c ****         delay_250ns();
 218              		.loc 1 52 9
 219 0094 FFF7FEFF 		bl	delay_250ns
  53:D:/mop/laborationer/5-3\delay.c ****         us--;
 220              		.loc 1 53 11
 221 0098 7B68     		ldr	r3, [r7, #4]
 222 009a 013B     		subs	r3, r3, #1
 223 009c 7B60     		str	r3, [r7, #4]
 224              	.L10:
  47:D:/mop/laborationer/5-3\delay.c ****     {
 225              		.loc 1 47 10
 226 009e 7B68     		ldr	r3, [r7, #4]
 227 00a0 002B     		cmp	r3, #0
 228 00a2 F1D1     		bne	.L11
  54:D:/mop/laborationer/5-3\delay.c ****     }
  55:D:/mop/laborationer/5-3\delay.c **** }
 229              		.loc 1 55 1
 230 00a4 C046     		nop
 231 00a6 C046     		nop
 232 00a8 BD46     		mov	sp, r7
 233 00aa 02B0     		add	sp, sp, #8
 234              		@ sp needed
 235 00ac 80BD     		pop	{r7, pc}
 236              		.cfi_endproc
 237              	.LFE3:
 239              		.align	1
 240              		.global	delay_milli
 241              		.syntax unified
 242              		.code	16
 243              		.thumb_func
 244              		.fpu softvfp
 246              	delay_milli:
 247              	.LFB4:
  56:D:/mop/laborationer/5-3\delay.c **** 
  57:D:/mop/laborationer/5-3\delay.c **** void delay_milli(unsigned int ms)
  58:D:/mop/laborationer/5-3\delay.c **** {
 248              		.loc 1 58 1
 249              		.cfi_startproc
 250              		@ args = 0, pretend = 0, frame = 8
 251              		@ frame_needed = 1, uses_anonymous_args = 0
 252 00ae 80B5     		push	{r7, lr}
 253              		.cfi_def_cfa_offset 8
 254              		.cfi_offset 7, -8
 255              		.cfi_offset 14, -4
 256 00b0 82B0     		sub	sp, sp, #8
 257              		.cfi_def_cfa_offset 16
 258 00b2 00AF     		add	r7, sp, #0
 259              		.cfi_def_cfa_register 7
 260 00b4 7860     		str	r0, [r7, #4]
  59:D:/mop/laborationer/5-3\delay.c **** #ifdef  SIMULATOR
  60:D:/mop/laborationer/5-3\delay.c ****     ms = ms / 1000;
 261              		.loc 1 60 8
 262 00b6 7B68     		ldr	r3, [r7, #4]
 263 00b8 FA22     		movs	r2, #250
 264 00ba 9100     		lsls	r1, r2, #2
 265 00bc 1800     		movs	r0, r3
 266 00be FFF7FEFF 		bl	__aeabi_uidiv
 267              	.LVL1:
 268 00c2 0300     		movs	r3, r0
 269 00c4 7B60     		str	r3, [r7, #4]
  61:D:/mop/laborationer/5-3\delay.c ****     ms++;
 270              		.loc 1 61 7
 271 00c6 7B68     		ldr	r3, [r7, #4]
 272 00c8 0133     		adds	r3, r3, #1
 273 00ca 7B60     		str	r3, [r7, #4]
  62:D:/mop/laborationer/5-3\delay.c **** #endif
  63:D:/mop/laborationer/5-3\delay.c ****     while(ms > 0)
 274              		.loc 1 63 10
 275 00cc 07E0     		b	.L13
 276              	.L14:
  64:D:/mop/laborationer/5-3\delay.c ****     {
  65:D:/mop/laborationer/5-3\delay.c ****         delay_micro(1000);
 277              		.loc 1 65 9
 278 00ce FA23     		movs	r3, #250
 279 00d0 9B00     		lsls	r3, r3, #2
 280 00d2 1800     		movs	r0, r3
 281 00d4 FFF7FEFF 		bl	delay_micro
  66:D:/mop/laborationer/5-3\delay.c ****         ms--;
 282              		.loc 1 66 11
 283 00d8 7B68     		ldr	r3, [r7, #4]
 284 00da 013B     		subs	r3, r3, #1
 285 00dc 7B60     		str	r3, [r7, #4]
 286              	.L13:
  63:D:/mop/laborationer/5-3\delay.c ****     {
 287              		.loc 1 63 10
 288 00de 7B68     		ldr	r3, [r7, #4]
 289 00e0 002B     		cmp	r3, #0
 290 00e2 F4D1     		bne	.L14
  67:D:/mop/laborationer/5-3\delay.c ****     }
  68:D:/mop/laborationer/5-3\delay.c **** }
 291              		.loc 1 68 1
 292 00e4 C046     		nop
 293 00e6 C046     		nop
 294 00e8 BD46     		mov	sp, r7
 295 00ea 02B0     		add	sp, sp, #8
 296              		@ sp needed
 297 00ec 80BD     		pop	{r7, pc}
 298              		.cfi_endproc
 299              	.LFE4:
 301              		.align	1
 302              		.global	main
 303              		.syntax unified
 304              		.code	16
 305              		.thumb_func
 306              		.fpu softvfp
 308              	main:
 309              	.LFB5:
  69:D:/mop/laborationer/5-3\delay.c **** 
  70:D:/mop/laborationer/5-3\delay.c **** void main(void)
  71:D:/mop/laborationer/5-3\delay.c **** {
 310              		.loc 1 71 1
 311              		.cfi_startproc
 312              		@ args = 0, pretend = 0, frame = 0
 313              		@ frame_needed = 1, uses_anonymous_args = 0
 314 00ee 80B5     		push	{r7, lr}
 315              		.cfi_def_cfa_offset 8
 316              		.cfi_offset 7, -8
 317              		.cfi_offset 14, -4
 318 00f0 00AF     		add	r7, sp, #0
 319              		.cfi_def_cfa_register 7
  72:D:/mop/laborationer/5-3\delay.c ****     init_app();
 320              		.loc 1 72 5
 321 00f2 FFF7FEFF 		bl	init_app
 322              	.L16:
  73:D:/mop/laborationer/5-3\delay.c ****     while(1)
  74:D:/mop/laborationer/5-3\delay.c ****     {
  75:D:/mop/laborationer/5-3\delay.c ****         *Bargraph = 0;
 323              		.loc 1 75 9 discriminator 1
 324 00f6 084B     		ldr	r3, .L17
 325              		.loc 1 75 19 discriminator 1
 326 00f8 0022     		movs	r2, #0
 327 00fa 1A70     		strb	r2, [r3]
  76:D:/mop/laborationer/5-3\delay.c ****         delay_milli(500);
 328              		.loc 1 76 9 discriminator 1
 329 00fc FA23     		movs	r3, #250
 330 00fe 5B00     		lsls	r3, r3, #1
 331 0100 1800     		movs	r0, r3
 332 0102 FFF7FEFF 		bl	delay_milli
  77:D:/mop/laborationer/5-3\delay.c ****         *Bargraph = 0xFF;
 333              		.loc 1 77 9 discriminator 1
 334 0106 044B     		ldr	r3, .L17
 335              		.loc 1 77 19 discriminator 1
 336 0108 FF22     		movs	r2, #255
 337 010a 1A70     		strb	r2, [r3]
  78:D:/mop/laborationer/5-3\delay.c ****         delay_milli(500);
 338              		.loc 1 78 9 discriminator 1
 339 010c FA23     		movs	r3, #250
 340 010e 5B00     		lsls	r3, r3, #1
 341 0110 1800     		movs	r0, r3
 342 0112 FFF7FEFF 		bl	delay_milli
  75:D:/mop/laborationer/5-3\delay.c ****         delay_milli(500);
 343              		.loc 1 75 19 discriminator 1
 344 0116 EEE7     		b	.L16
 345              	.L18:
 346              		.align	2
 347              	.L17:
 348 0118 14100240 		.word	1073877012
 349              		.cfi_endproc
 350              	.LFE5:
 352              	.Letext0:
