


[0x0010 - main]
	mov ax,AAh			A0 71 AA
	out ax				A5 01
	
	call display		AD 01 00 20
	call led_flow		AD 01 00 60
	hlt					C0
	
[0x2000 - display]
	mov cx,00h			A0 73 00
l1:
	mov ax,A0			A0 71 A0
	mov ds,ax			A0 61
	
	mov ax,cx			A0 02
	lod ax,[ds:ax]		A2 01
	cmp ax,00h			AA 41 00
	je l2				AB 01 20 20
	mov bx,C0h			A0 72 C0
	mov ds,bx			A0 62
	mov bx,cx			A0 12
	sae [ds:bx],ax		A3 11
	add cx,01			A4 43 01
	jmp l1				A1 02 03 20
l2:
	ret					A9 00
	
[0x6000 - led_flow]
	mov cx,FF			A0 73 FF
l3:
	out cx				A5 03
	loop l3				AC 00 03 60
	ret					A9 00
	
	
	
[0xA000 - .text]
	db "NEKO 8-Bits Computer"
						4e 45 4b 4f 20 38 2d 42 69 74 73 20 43 6f 6d 70 75 74 65 72