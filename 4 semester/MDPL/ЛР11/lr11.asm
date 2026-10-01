.386
.model flat,stdcall
option casemap:none

include D:\irvine\Irvine32.inc

.data
ClassName db "SimpleWinClass",0
AppName db "Our First Window",0
hello_mess1 db "Нажата левая клавиша мыши",0
hello_mess2 db "Нажата правая клавиша мыши",0
hello_title db "Ура!",0

.data?
hInstance HINSTANCE ?
hInst HINSTANCE ?
CommandLine LPSTR ?
wc WNDCLASSEX <>
msg MSG <>
hwnd HWND ?

.code
start:
invoke GetModuleHandle,NULL
mov hInstance,eax
mov wc.cbSize,SIZEOF WNDCLASSEX
mov wc.style,CS_HREDRAW or CS_VREDRAW
mov wc.lpfnWndProc,OFFSET WndProc
mov wc.cbClsExtra,NULL
mov wc.cbWndExtra,NULL
push hInstance
pop wc.hInstance
mov wc.hbrBackground,COLOR_WINDOW+1
mov wc.lpszMenuName,NULL
mov wc.lpszClassName,OFFSET ClassName
invoke LoadIcon,NULL,IDI_APPLICATION
mov wc.hIcon,eax
mov wc.hIconSm,eax
invoke LoadCursor,NULL,IDC_ARROW
mov wc.hCursor,eax
invoke RegisterClassEx,addr wc
INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL
mov hwnd,eax
invoke ShowWindow,hwnd,SW_SHOWNORMAL
invoke UpdateWindow,hwnd

MSG_LOOP:
invoke GetMessage,ADDR msg,NULL,0,0
cmp eax,0
je END_LOOP
invoke TranslateMessage,ADDR msg
invoke DispatchMessage,ADDR msg
jmp MSG_LOOP

END_LOOP:
mov eax,msg.wParam
invoke ExitProcess,eax

WndProc proc hWnd:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
cmp uMsg,WM_DESTROY
je WMDESTROY
cmp uMsg,WM_LBUTTONDOWN
je LBUTTON
cmp uMsg,WM_RBUTTONDOWN
je RBUTTON
JMP DEFWNDPROC

WMDESTROY:
invoke PostQuitMessage,NULL
xor eax,eax
jmp FINISH

LBUTTON:
invoke MessageBoxA,hwnd,addr hello_mess1,addr hello_title,MB_APPLMODAL
jmp FINISH

RBUTTON:
invoke MessageBoxA,hwnd,addr hello_mess2,addr hello_title,MB_OK
jmp FINISH

DEFWNDPROC:
invoke DefWindowProc,hWnd,uMsg,wParam,lParam

FINISH:
ret
WndProc endp

end start