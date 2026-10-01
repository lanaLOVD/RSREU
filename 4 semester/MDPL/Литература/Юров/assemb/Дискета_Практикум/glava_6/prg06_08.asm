;----------------------------------------------------------
;prg06_08.asm - программа вывода целых десятичных чисел из диапазона 0..µ.
;Вход: многобайтное двоичное число для преобразование в области памяти bin_dd.
;Выход: вывод десятичного числа из диапазона 0..µ на экран
;----------------------------------------------------------
masm
model small
.486
.stack	256
div_unsign_N_1_I	macro	u,N,v,w,r
local	m1
;------------------------------------------------------------------------------------------;
;div_unsign_N_1_I  ? макрокоманда деления N-разрядного беззнакового целого на одноразрядное число размером 1 байт (порядок следования байт - младший байт по младшему адресу (Intel))
;Вход: u - делимое; N - длина делимого, v - делитель.
;Выход: w - частное, r - остаток.
;------------------------------------------------------------------------------------------;
push	si
push	cx
push	dx
push	bx
push	ax
	mov	r,0
	mov	si,N-1	;j=N-1
	mov	cx,N
	xor	dx,dx
	xor	bx,bx
m1:	mov	ax,256	;основание с.с.
	mul	word ptr r	;результат в dx:ax
	mov	bl,u[si]
	add	ax,bx
	div	v
;сформировать результат:
	mov	w[si],al	;частное
	shr	ax,8
	mov	r,ax	;остаток в r
	dec	si
	loop	m1
pop	ax
pop	bx
pop	dx
pop	cx
pop	si
	endm
.data
string	db	10 dup (0)	;пусть максимальное десятичное число состоит из 10 цифр
len_string=$-string
adr_string	dd	string
bin_dd	label	BYTE
	dd	0ffffffffh
len_bin_dd=$-bin_dd
ten	db	10
remainder	dw	0
.code
main:
	mov	ax,@data	;адрес сегмента данных - в регистр ax
	mov	ds,ax	;ax в ds
;значение для преобразования должно быть в памяти
	les	di,adr_string	строка с десятичными символами
	cld	;обработка в прямом направлении
continue:
	div_unsign_N_1_I	bin_dd,len_bin_dd,ten,bin_dd,remainder
	mov	ax,remainder
	or	al,30h	;преобразуем в символьное представление
	stosb	;сохраняем в string очередную десятичную цифру
	inc	cx	;подсчитываем количество цифр
	cmp	bin_dd,0
	jne	continue
;вывод на консоль с конца строки
	mov	ah,2
	std
	mov	si,di
	dec	si
m1:
	lodsb
	mov	dl,al
	int	21h
	loop	m1
exit:
;выход из программы
	mov	ax,4c00h	;пересылка 4c00h в регистр ax
	int	21h	;вызов прерывания с номером 21h
end	main		;конец программы с точкой входа main
