# NEKO-8-Bits-Computer

## 介绍

你是否想过从0开始设计一台自己的电脑，跟我一起回到8086/8088的年代，虽然只是简单的8位机但是我们需要从0开始搭建，从元件到电路，从CPU到汇编，步一步搭建起我们自己的电脑。

## 结构

使用7个AT28C64作为内存
使用单片机模拟显存
16位地址总线
8位数据总线
8位I0输出
从0设计CPU指令集
FPGA模拟CPU
8位I0状态指示LED
16位地址总线状态指示
8位数据总线状态指示
CPU时钟状态指示
CPU HLT指示
支持手动编程
独立设计FLASH烧录器

## 内存定义

![image-20210302164822355](.\image\memory.png)

## 指令集

```
mov 		A0
jmp			A1
lod			A2
sae			A3
alu			A4
in			A5
out 		A6
push		A7
pop			A8
ret			A9
cmp			AA
je...	 	AB
loop		AC
call		AD
NOP			B0
HLT			C0
```

## 演示视频

https://www.bilibili.com/video/BV13U4y1s7hN/

https://www.bilibili.com/video/BV1ny4y1a7Ad

## 例程

### display 函数 - 0x2000

```
mov cx,00			A0 73 00	//指定字符串偏移
mov bx,00			A0 72 00    //指定显存偏移

l1:
mov ax,A0			A0 71 A0	
mov ds,ax			A0 61
lod ax,[ds:cx]		A2 03 //A000地址开始读取	
cmp	ax,00			AA 41 00 //比较是否为字符串结尾
JE	l2				AB 01 ?? 20	//相等则跳转
mov dx,C0			A0 74 C0 //
mov ds,dx			A0 64	
sae	[ds:bx],ax		A3 11
add bx,1			A4 42 01		
add cx,1			A4 43 01
jmp l1				A1 02 06 20
l2:
RET					A9 00
```

### OUT测试 - OK

```
mov ax,0xCA			A0 71 CA
out ax				A5 01
```

### MOV测试 - OK

```
mov ax,0xC0			A0 71 C0		
mov ds,ax			A0 61	

mov ax,0x00			A0 71 00
mov bx,'n'			A0 72 6E
sae [ax],bx			A3 02	

add ax,1			A4 41 01
mov bx,'e'			A0 72 65
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'k'			A0 72 6B
sae [ax],bx			A3 02	

add ax,1			A4 41 01
mov bx,'o'			A0 72 6F
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'k'			A0 72 6B
sae [ax],bx			A3 02	

add ax,1			A4 41 01
mov bx,'a'			A0 72 61
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'m'			A0 72 6D
sae [ax],bx			A3 02	

add ax,1			A4 41 01
mov bx,'i'			A0 72 69
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'0'			A0 72 30
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'5'			A0 72 35
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'2'			A0 72 32
sae [ax],bx			A3 02

add ax,1			A4 41 01
mov bx,'7'			A0 72 37
sae [ax],bx			A3 02

HLT					C0
```

### SUB测试 - OK

```
mov ax,0xBA        	A0 71 10
out ax				A5 01
mov bx,0x10			A0 72 05
out bx				A5 02
sub ax,bx			A4 52
out ax				A5 01
hlt					C0


mov ax,0xFF			A0 71 FF
mov bx,0x01			A0 72 01
out ax				A5 01
sub ax,bx			A4 52
NOP					B0
//sub ax,num		A4 91 01
cmp ax,00			AA 41 00
jne 00 ??			AB 02 ?? 00
HLT					C0
```

### ADD测试 - OK

```
mov ax,0x10			A0 71 10
mov bx,0x01			A0 72 01
out ax				A5 01
add ax,01			A4 41 01
cmp ax,FF			AA 41 FF
jne 00 ??			AB 02 ?? 00
HLT					C0

```

### LOOP测试 - OK

```
mov ax,0xC0			A0 71 C0		
mov ds,ax			A0 61	
mov ax,0x00			A0 71 00

mov cx,0x10			A0 73 10
mov bx,'a'			A0 72 61
loop1:
sae [ax],bx			A3 02
add ax,1			A4 41 01
add bx,1			A4 42 01
LOOP				AC 00 ?? 00
HAL					C0
```

### LOD测试 - OK

```
mov ax,AA			A0 71 AA
out ax				A5 01

lod	ax,A0			A2 41 00 A0	
out ax				A5 01	
HLT					C0
```



### CMP测试 - OK

```
mov cx,00			A0 73 00	//指定字符串偏移
mov bx,00			A0 72 00    //指定显存偏移

l1:
mov ax,A0			A0 71 A0	
mov ds,ax			A0 61
lod ax,[ds:cx]		A2 03 //A000地址开始读取	
cmp	ax,00			AA 41 00 //比较是否为字符串结尾
JE	l2				AB 01 ?? 00	//相等则跳转
mov dx,C0			A0 74 C0 //
mov ds,dx			A0 64	
sae	[ds:bx],ax		A3 11
add bx,1			A4 42 01		
add cx,1			A4 43 01
jmp l1				A1 02 ?? 00
l2:
HLT					C0
```

### EEPROM写入测试 - OK

```
mov ax,E0			A0 71 E0
mov ds,ax			A0 61
mov cx,FF			A0 73 FF
mov dx,AA			A0 74 AA
mov ax,00			A0 71 00
l1:
sae [ds:ax],dx		A3 04
add ax,1			A4 41 01
loop l1				AC 00 ?? 00
HLT					C0
```

### EEPROM Stack段写入测试

```
mov ax,FF			A0 71 FF
mov ds,ax			A0 61
mov cx,FF			A0 73 FF
mov dx,AA			A0 74 AA
mov ax,00			A0 71 00

l1:
sae [ds:ax],dx		A3 04
//sub ax,1			A4 91 01
add ax,1			A4 41 01
loop l1				AC 00 ?? 00
HLT					C0
```



### PUSH测试 - OK

```
mov cx,FF			A0 73 FF
l1:
push cx				A7 21
loop cx				AC 00 03 00
HLT					C0
```

### POP测试 - OK

```
mov cx,FF			A0 73 FF
l1:
push cx				A7 21
loop l1				AC 00 03 00

mov cx,FF			A0 73 FF
l2:
pop bx				A8 11
out bx				A5 02
loop l2				AC 00 ?? 00

HLT					C0

	
mov ax,0x00			A0 73 00
mov sp,ax			A0 51
mov cx,0xff			A0 73 FF
l1:
pop bx				A8 11
out bx				A5 02
loop l1				AC 00 ?? 00
hlt					C0
```

### CALL测试 - OK

```
display 函数 - 0x2000

mov cx,00			A0 73 00	//指定字符串偏移
mov bx,00			A0 72 00    //指定显存偏移

l1:
mov ax,A0			A0 71 A0	
mov ds,ax			A0 61
lod ax,[ds:cx]		A2 03 //A000地址开始读取	
cmp	ax,00			AA 41 00 //比较是否为字符串结尾
JE	l2				AB 01 ?? 20	//相等则跳转
mov dx,C0			A0 74 C0 //
mov ds,dx			A0 64	
sae	[ds:bx],ax		A3 11
add bx,1			A4 42 01		
add cx,1			A4 43 01
jmp l1				A1 02 06 20
l2:
RET					A9 00

main函数 - 0x0000
mov ax,0xff			A0 71 FF
out ax				A5 01

call display		AD 01 00 60		

mov ax,0xAA			A0 71 AA
out ax				A5 01
HLT					C0



test_ret_function - 6000
mov ax,10			A0 71 10
out ax				A5 01
ret					A9 00
```

