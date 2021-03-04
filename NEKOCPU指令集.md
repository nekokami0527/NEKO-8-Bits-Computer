# 内存定义

![image-20210302164822355](.\image\memory.png)

主程序引导从0x0010处开始，前方空出16字节预留。

# 术语定义

## 指令周期

​	由于此处指令集均为2字节，占用两个时钟周期，因此指令周期不在包含指令集接收的两个时钟周期

​	此处指令周期定义为:

##### 		从指令集接收完全(2时钟周期)后,直至此指令所有操作执行完成为止所消耗的时钟周期

# FLAG寄存器

## 定义

|  7   |  6   |  5   |       4       |     3      |    2     |      1      |    0    |
| :--: | :--: | :--: | :-----------: | :--------: | :------: | :---------: | :-----: |
|  0   |  0   |  0   |    S(ign)     | O(verflow) | C(arry)  |   Z(ero)    |  H(LT)  |
| 未定 | 未定 | 未定 | 符号位（0/1） |  计算溢出  | 计算进位 | 比较结果位0 | CPU停止 |

符号位 1为 大于等于 0

符号位 0为 	小于 	0

## 控制总线定义

| 总线位 |  2   |  1   |  0   |
| :----: | :--: | :--: | :--: |
|  功能  |  NC  | RE#  | WE#  |
|  状态  |  NC  | H/L# | H/L  |



# 指令定义

## MOV指令 - A0

### 介绍

​	给某个寄存器赋值

### 参数个数

​	2个

### 指令周期

​	 1个指令周期

### 指令定义

```
mov ax,bx		A0	01
mov ax,cx		A0	02
mov ax,dx		A0	03
mov ax,sp		A0	04
mov ax,bp		A0	05
mov ax,ds		A0 	06

mov bx,ax		A0	11
mov bx,cx		A0	12
mov bx,dx		A0	13
mov bx,sp		A0	14
mov bx,bp		A0	15
mov bx,ds		A0	16

mov cx,ax		A0	21
mov cx,bx		A0	22
mov cx,dx		A0	23
mov cx,sp		A0	24
mov cx,bp		A0	25
mov cx,ds		A0	26

mov dx,ax		A0	31
mov dx,bx		A0	32
mov dx,cx		A0	33
mov dx,sp		A0	34
mov dx,bp		A0	35
mov dx,ds		A0	36

mov bp,ax		A0	41
mov bp,bx		A0	42
mov bp,cx		A0	43	
mov bp,dx		A0	44
mov bp,sp		A0	45


mov sp,ax		A0	51
mov sp,bx		A0	52
mov sp,cx		A0	53
mov sp,dx		A0	54
mov sp,bp		A0	55

mov ds,ax		A0	61
mov ds,bx		A0	62
mov ds,cx		A0	63
mov ds,dx		A0	64

mov ax,num		A0	71	NUM
mov bx,num		A0	72	NUM
mov cx,num		A0	73	NUM
mov dx,num		A0	74	NUM

1010 0000
0111 0001
0101 0101

```

### 实现细节

![image-20210210233647274](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210233647274.png)

## JMP指令 - A1

### 介绍

​	跳转 程序执行地址

### 参数个数

​	1个

### 指令周期

​	 5个指令周期

### 指令定义

````
jmp ax			A1	01		//默认DS:AX
jmp address		A1	02	ADDR(L)	ADDR(H)
````

### 实现细节

![image-20210210233347860](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210233347860.png)



## LOD指令 - A2

### 介绍

​	从内存指定地址读入内容到寄存器

### 参数个数

​	2个

### 指令周期

​	 2个或4个指令周期

### 指令定义

```
lod ax,[ds:ax]		A2	01
lod ax,[ds:bx]		A2	02
lod ax,[ds:cx]		A2	03
lod ax,[ds:dx]		A2	04

lod bx,[ds:ax]		A2	11
lod bx,[ds:bx]		A2	12
lod bx,[ds:cx]		A2	13
lod bx,[ds:dx]		A2	14

lod cx,[ds:ax]		A2	21
lod cx,[ds:bx]		A2	22
lod cx,[ds:cx]		A2	23
lod cx,[ds:dx]		A2	24

lod dx,[ds:ax]		A2	31
lod dx,[ds:bx]		A2	32
lod dx,[ds:cx]		A2	33
lod dx,[ds:dx]		A2	34

lod	ax,address	A2	41	ADDR(L)	ADDR(H)
lod	bx,address	A2	42	ADDR(L)	ADDR(H)
lod	cx,address	A2	43	ADDR(L)	ADDR(H)
lod	dx,address	A2	44	ADDR(L)	ADDR(H)
```

### 实现细节

![image-20210210224137991](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210224137991.png)

## SAE指令 - A3

### 介绍

​	向指定内存存储指定寄存器内容

### 参数个数

​	2个

### 指令周期

​	 2个或4个指令周期

### 指令定义

```
sae	[ds:ax],ax		A3	01
sae	[ds:ax],bx		A3	02
sae	[ds:ax],cx		A3  03
sae	[ds:ax],dx		A3	04

sae	[ds:bx],ax		A3	11
sae	[ds:bx],bx		A3	12
sae	[ds:bx],cx		A3	13
sae	[ds:bx],dx		A3	14

sae	[ds:cx],ax		A3	21
sae	[ds:cx],bx		A3	22
sae	[ds:cx],cx		A3	23
sae	[ds:cx],dx		A3	24

sae	[ds:dx],ax		A3	31
sae	[ds:dx],bx		A3	32
sae	[ds:dx],cx		A3	33
sae	[ds:dx],dx		A3	34

sae	address,ax	A3	41	ADDR(L)	ADDR(H)
sae	address,bx	A3	42	ADDR(L)	ADDR(H)	
sae	address,cx	A3	43	ADDR(L)	ADDR(H)
sae	address,dx	A3	44	ADDR(L)	ADDR(H)
```

### 实现细节

![image-20210210232226585](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210232226585.png)



## 计算指令 - A4

### 介绍

​	使用指定寄存器进行计算

### 参数个数

​	2个

### 指令周期

​	 1个或 2个指令周期

### 指令定义

```
add ax,ax		A4	01
add ax,bx		A4	02
add ax,cx		A4	03
add ax,dx		A4	04

add bx,ax		A4	11
add bx,bx		A4	12
add bx,cx		A4	13
add bx,dx		A4	14

add cx,ax		A4	21
add cx,bx		A4	22
add cx,cx		A4	23
add cx,dx		A4	24

add dx,ax		A4	31
add dx,bx		A4	32
add dx,cx		A4	33
add dx,dx		A4	34

add ax,num		A4	41	NUM
add bx,num		A4	42	NUM
add cx,num		A4	43	NUM
add dx,num		A4	44	NUM




sub ax,ax		A4	51
sub ax,bx		A4	52
sub ax,cx		A4	53
sub ax,dx		A4	54

sub bx,ax		A4	61
sub bx,bx		A4	62
sub bx,cx		A4	63
sub bx,dx		A4	64

sub cx,ax		A4	71
sub cx,bx		A4	72
sub cx,cx		A4	73
sub cx,dx		A4	74

sub dx,ax		A4	81
sub dx,bx		A4	82
sub dx,cx		A4	83
sub dx,dx		A4	84

sub ax,num		A4	91	NUM
sub bx,num		A4	92	NUM
sub cx,num		A4	93	NUM
sub dx,num		A4	94	NUM
```

### 实现细节

![image-20210210231827766](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210231827766.png)



## OUT指令 - A5

### 介绍

​	向输出GPIO (8位输出内容)

### 参数个数

​	1个

### 指令周期

​	1个指令周期

### 指令定义

```
out	ax			A5	01
out bx			A5	02
out cx			A5	03
out dx			A5	04
```

### 实现细节

![image-20210210231555320](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210231555320.png)

## IN指令 - A6

### 介绍



​	从GPIO读入内容 (8位输出内容)

### 参数个数

​	1个

### 指令周期

​	 2个指令周期

### 指令定义

```
in ax			A6	01
in bx			A6	02
in cx			A6 	03
in dx			A6	04
```

### 实现细节

![image-20210210231428218](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210231428218.png)

## PUSH指令 - A7

### 介绍

​	向堆栈PUSH内容

### 参数个数

​	1个

### 指令周期

​	 5个指令周期

### 指令定义

```
push ax			A7	01
push bx			A7	11
push cx			A7	21
push dx			A7	31
push sp			A7	41
push bp			A7	51
push num		A7	61	NUM
```

### 实现细节

![image-20210210233503750](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210233503750.png)



## POP指令 - A8

### 介绍

​	从堆栈POP内容

### 参数个数

​	1个

### 指令周期

​	 3个指令周期

### 指令定义

```
pop ax			A8	01
pop bx			A8	11
pop cx			A8	21
pop dx			A8	31
pop sp			A8	41
pop bp			A8	51
```

### 实现细节

```
堆栈结构
+-----------------+
|       DATA      |
+-----------------+
1.以当前栈顶的数值赋值给指定寄存器
2.SP = SP + 1

1~2.读取指令
3.(*x/*p) = [sp]
4.SP = SP + 1
```

![image-20210210225713419](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210225713419.png)

## RET指令 - A9

### 介绍

​	return 根据堆栈返回地址返回

### 参数个数

​	0个

### 指令周期

​	4 个指令周期

### 指令定义

```
ret				A9	00
```

### 实现细节

```
堆栈结构
+-----------------+
|  RET Address(L) |
+-----------------+
|  RET Address(H) |
+-----------------+
以当前栈顶的数值作为跳转地址给IP寄存器赋值

```

![image-20210210224854363](C:\Users\nekokami\AppData\Roaming\Typora\typora-user-images\image-20210210224854363.png)

## CMP - AA

### 介绍

​	比较寄存器值，结果存储在Flag寄存器 -> ZF中

### 参数个数

​	2个

### 指令周期

​	4个指令周期

### 指令定义

```
cmp	ax,ax	AA	01
cmp	ax,bx	AA	02
cmp	ax,cx	AA	03
cmp	ax,dx	AA	04

cmp	bx,ax	AA	11
cmp	bx,bx	AA	12
cmp	bx,cx	AA	13
cmp	bx,dx	AA	14

cmp	cx,ax	AA	21
cmp	cx,bx	AA	22
cmp	cx,cx	AA	23
cmp	cx,dx	AA	24

cmp	dx,ax	AA	31
cmp	dx,bx	AA	32
cmp	dx,cx	AA	33
cmp	dx,dx	AA	34

cmp	ax,NUM	AA	41	NUM
cmp	bx,NUM	AA	42	NUM
cmp	cx,NUM	AA	43	NUM
cmp	dx,NUM	AA	44	NUM
```

### 实现细节

```

```



## 条件跳转 - AB

### 介绍

​	根据比较结果有条件跳转

### 参数个数

​	1个

### 指令周期

​	3 个指令周期

### 指令定义

```
JE		AB 01	ADDR(L)	ADDR(H)		//相等则跳转
JNE		AB 02	ADDR(L)	ADDR(H)		//不等则跳转
JC 		AB 10	ADDR(L)	ADDR(H)		//进位则跳转
JNC  	AB 11	ADDR(L)	ADDR(H)		//不进位则跳转
JO		AB 20	ADDR(L)	ADDR(H)		//溢出则跳转
JNO		AB 21	ADDR(L)	ADDR(H)		//未溢出则跳转

JA		AB 30	ADDR(L)	ADDR(H)		//大于则跳转
JNA		AB 31	ADDR(L)	ADDR(H)		//不大于则跳转
JAE		AB 32	ADDR(L)	ADDR(H)		//大于等于则跳转
JNAE	AB 33	ADDR(L)	ADDR(H)		//不大于等于则跳转

JB   	AB 34	ADDR(L)	ADDR(H)		//小于则跳转
JNB  	AB 35	ADDR(L)	ADDR(H)		//不小于则跳转
JBE  	AB 36	ADDR(L)	ADDR(H)		//小于等于则跳转
JNBE	AB 37	ADDR(L)	ADDR(H)		//不小于等于则跳转






```

## LOOP - AC

### 介绍

​	根据CX数值进行循环跳转

### 参数个数

​	1个

### 指令周期

​	1个 或 3 个指令周期

### 指令定义

```
loop Address	AC 00 ADDR(L) ADDR(H)
```

---

## CALL - AD

### 介绍

​	函数调用

### 参数个数

​	1个

### 指令周期

​	 个指令周期

### 指令定义

```
call Address	AD 01 ADDR(L) ADDR(H)
```

---

## NOP - B0

### 介绍

​	啥也不做，这个都能理解吧，无用指令，占用时钟周期

### 参数个数

​	0个

### 指令周期

​	1 个指令周期

### 指令定义

```
NOP		B0
```



---

## HLT - C0

### 介绍

​	处理器停机

### 参数个数

​	0个

### 指令周期

​	1 个指令周期

### 指令定义

```
HLT		C0
```

---

---

# 测试

## OUT测试 - OK

```
mov ax,0xCA			A0 71 CA
out ax				A5 01
```

## MOV测试 - OK

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

## SUB测试 - OK

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

## ADD测试 - OK

```
mov ax,0x10			A0 71 10
mov bx,0x01			A0 72 01
out ax				A5 01
add ax,01			A4 41 01
cmp ax,FF			AA 41 FF
jne 00 ??			AB 02 ?? 00
HLT					C0

```

## LOOP测试 - OK

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

## LOD测试 - OK

```
mov ax,AA			A0 71 AA
out ax				A5 01

lod	ax,A0			A2 41 00 A0	
out ax				A5 01	
HLT					C0
```



## CMP测试 - OK

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

## EEPROM写入测试 - OK

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

## EEPROM Stack段写入测试

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



## PUSH测试 - OK

```
mov cx,FF			A0 73 FF
l1:
push cx				A7 21
loop cx				AC 00 03 00
HLT					C0
```

## POP测试 - OK

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

## CALL测试 - OK

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

