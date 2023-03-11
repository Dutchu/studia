.thumb

.equ RCC_BASE ,              0x40021000	@(AHBPERIPH_BASE + 0x00001000)
.equ GPIOC_BASE,             0x48000800	@ (AHB2PERIPH_BASE + 0x00000800)
.equ ECC_AHB2ENR_OFFSET, 	 0x4c
.equ BSSR,					 0x18
.equ BSR,       			 0x28

.global main


.thumb_func

main:
	@ Enable clock for GPIOC peripheral in RCC registers
    LDR R0, =(RCC_BASE + ECC_AHB2ENR_OFFSET)
    LDR R1, =(1 << 2)
    STR R1, [r0]

    @ Enable GPIOC pin 6 as output
    LDR R0, =(GPIOC_BASE + 0x00)
    LDR R1, =(1 << (6*2))
    STR R1, [r0]

blinking:
    @ Write high to pin PC9
    LDR R0, =(GPIOC_BASE + BSSR)
    LDR R1, =(1 << 6)
    STR R1, [r0]

    @ Delay
	LDR R0, =600000
	DELAY1:
	SUB R0, R0, #1
    BNE DELAY1

    @ Write low to PC9
    LDR R0, =(GPIOC_BASE + BSR)
    LDR R1, =(1 << 6)
    STR R1, [r0]     @Store R1 value to address pointed by R0

	@ Delay
    LDR R0, =600000
    DELAY2:
    SUB R0, R0, #1
    BNE DELAY2

	B blinking
