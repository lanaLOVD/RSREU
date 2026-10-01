.386
.model flat,stdcall 

include C:\masm32\include\windows.inc 
include C:\masm32\include\kernel32.inc

includelib C:\masm32\lib\kernel32.lib 

.const 
ConsoleTitle db "DEMO CONSOLE PROGRAM",0 

.data 
msg1 db "Your name: " 
msg1_len = $-msg1 
msg2 db "Hello, " 
msg2_len = $-msg2 
InputBuffer db 100 dup (?)
len_InputBuffer = $-InputBuffer 

.data? hOutput dd ? 
hInput dd ? 
nRead dd ?
nWriten dd ?

.code 
start: 
invoke SetConsoleTitleA, addr ConsoleTitle 
invoke GetStdHandle,STD_OUTPUT_HANDLE 
mov hOutput,eax 
invoke WriteConsoleA,hOutput,addr msg1,msg1_len,addr nWriten,NULL
invoke GetStdHandle,STD_INPUT_HANDLE 
mov hInput,eax 
invoke ReadConsoleA,hInput,addr InputBuffer,len_InputBuffer,addr nRead,NULL 
invoke WriteConsoleA,hOutput,addr msg2,msg2_len,addr nWriten,NULL 
invoke WriteConsoleA,hOutput,addr InputBuffer,nRead,addr nWriten,NULL 
invoke ExitProcess,0 
end start