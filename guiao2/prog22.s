		.equ		resetCoreTimer,		12
		.equ		readCoreTimer,			11
		.equ		printInt,				 6
		.equ		readInt10,			 5
		.data
		.text
		.globl	main

main:	
		addiu	$sp, $sp, -4
		sw		$ra, 0($sp)
		
		li		$t0, 0			# counter = 0;
while1:
		li		$a0, 0
		move		$a0, $v0
		

		jal		delay			# delay($a0)
		
		addi		$t0, $t0, 1		# counter++;
		move		$a0, $t0			# $a0 = $t0;
		li		$a1, 0x0004000A	# $a1 = 10 | 4 << 16;
		li		$v0, printInt		# $v0 = PRINT_INT
		syscall
		
		li		$a0, '\r'			# $a0 = '\r';
		li		$v0, 3			# $v0 = PUT_CHAR;
		syscall					# putChar('\r');
		
		j		while1			#
		
		
end:		lw		$ra, 0($sp)		#
		addiu	$sp, $sp, 4		#
		jr		$ra				
		
# -------------------------------------- FUNÇÃO DELAY -----------------------------------------

delay:		
		ble		$a0, 0, enddelay
		li		$v0, resetCoreTimer
		syscall	
while:	
		li		$v0, readCoreTimer
		syscall	
		blt		$v0, 20000, while
		addi		$a0, $a0, -1
		j		delay
		
enddelay: 
		
		jr		$ra
