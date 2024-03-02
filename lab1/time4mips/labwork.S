  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
.global delay
.global time2string
.global hex
 .data
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
 .text
.global delay
.global time2string
.global hexasc
 
hexasc:
  	andi $a0, $a0, 0xF
  	li $t0, 9
  	
  	ble $a0,$t0, if
  	addi $t0, $t0, 55
  	j exit
 if: 	
  	addi $a0, $a0, 48
 exit:
	move $v0, $a0
	jr $ra
		
time2string:
    # a0, timstr, should change to mm:ss
    # a1, mytime, get time from this

    # m----
    andi $t1, $a1, 0x0000f000 # isolating before pushing a1 to stack
    srl  $t1, $t1, 12         # shift to far right

    PUSH $a0
    PUSH $a1
    PUSH $ra

    add $a0, $zero, $t1 # setting argument
    jal hexasc
    nop
    # now we have the ascii stored in v0

    POP $ra
    POP $a1
    POP $a0

    sb $v0, 0($a0)

    # -m---
    andi $t1, $a1, 0x00000f00 # isolating before pushing a1 to stack
    srl  $t1, $t1, 8          # shift to far right

    PUSH $a0
    PUSH $a1
    PUSH $ra

    add $a0, $zero, $t1 # setting argument
    jal hexasc
    nop
    # now we have the ascii stored in v0

    POP $ra
    POP $a1
    POP $a0

    sb $v0, 1($a0)

    # --:--
    li $t1, 0x3a
    sb $t1, 2($a0)

    # ---s-
    andi $t1, $a1, 0x000000f0 # isolating s1, before pushing a1 to stack
    srl  $t1, $t1, 4          # shift to far right

    PUSH $a0
    PUSH $a1
    PUSH $ra

    add $a0, $zero, $t1 # setting argument
    jal hexasc
    nop
    # now we have the ascii stored in v0    

    POP $ra
    POP $a1
    POP $a0

    sb $v0, 3($a0)

    # ----s
    andi $t1, $a1, 0x0000000f # isolating s2, before pushing a1 to stack
    #srl  $t1, $t1, 4          # shift to far right # don't actually need to shift this one

    PUSH $a0
    PUSH $a1
    PUSH $ra

    add $a0, $zero, $t1 # setting argument
    jal hexasc
    nop
    # now we have the ascii stored in v0    

    POP $ra 
    POP $a1
    POP $a0

    sb $v0, 4($a0)

    # NULL
    li $t1, 0x00
    sb $t1, 5($a0)

    jr $ra
    nop
	
delay:
	beqz  $a0, end # if Num of Ms is 0, then break
	addi $a0, $a0, -1 # Ms = Ms - 1
	
	li $t0, 4711 # I, number of iterations in for loop
	
loop:
	bne $t0, 0, end # if I is 0, break
	addi    $t0, $t0, -1
	
	j  loop
end:
	jr $ra
        nop
