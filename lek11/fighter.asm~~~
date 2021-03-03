

main:
	ldr	r0,=wizard
	

@ int GetDamage(Monster * m)
GetDamage:
	ldrb	r1,[r0,#0]
	cmp	r1,#0
	bne	Wizard
Fighter:
	ldr	r1,[r0,#4]	@ m->stregnth -> r1
	ldrh	r2,[r0,#8]	@ m->agility ->r2
	add	r0,r1,r2
	bx	lr
Wizard:
	ldr	r1,[r0,#4]	@ m->mana_points -> r1
	ldrh	r2,[r0,#8]	@ m->hat_size -> r1
	@ldrb	r3,[r1,#10]	@ doesn't work because only multiples of
	add	r0,#10
	ldrb	r3,[r0]
	add	r0,r1,r2
	add	r0,r3
	bx	lr










.align 	4
fighter:
.byte	0	@ MonsterType = Fighter
.space	3	@ Align to word
.word	10	@ strength = 10
.short	5	@ agility = 5
.space	2	@ Align to word

wizard:
.byte	1	@ MonsterType = Wizard
.space	3	@ Align to word
.word	6	@ mana_points = 6
.short	3	@ hat_size ? 3
.byte	10	@ staff_damage = 10
.space	1	@ Align to word


