.386P 

.model flat,stdcall
 
include C:\masm32\include\windows.inc 
include C:\masm32\include\user32.inc 
include C:\masm32\include\kernel32.inc
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\user32.lib 

.data 
hello_mess db "Windows", 0 
hello_title db "Hello, World!", 0 

.code 
start: 
push MB_OKCANCEL 
push offset hello_title 
push offset hello_mess 
;push 0 
;call MessageBoxA
invoke MessageBoxA,0,addr hello_mess,addr hello_title, MB_OKCANCEL 

push 0 
call ExitProcess
 
end start