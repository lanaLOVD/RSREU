.386
.model flat,stdcall
option casemap:none 
include C:\masm32\include\windows.inc 
include C:\masm32\include\kernel32.inc 
include C:\masm32\include\fpu.inc 
includelib C:\masm32\lib\user32.lib 
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\fpu.lib 
BSIZE equ 30 
.data 
num1 dd 45.56  
num2 dd 30.13
result dt ?
stdout dd ?
cWritten dd ?
buf db BSIZE dup (?) 

.code start: 
main proc 
invoke GetStdHandle,STD_OUTPUT_HANDLE 
mov stdout,eax 
fld num1 
fld num2
fadd 
fstp result
invoke FpuFLtoA,ADDR result,5
invoke WriteConsoleA,stdout,ADDR buf,BSIZE,ADDR cWritten,NULL 
invoke ExitProcess,0 
main endp 
end start