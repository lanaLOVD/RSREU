
{
Dialogbox Template by: Edwin Pelleng
e-mail: ewin_p@eprojex.890m.com
Compile parameters: fpc.exe -WG dialogapp.pas
}

{$MODE DELPHI}
{$R dialogapp.rc}
{$APPTYPE GUI}

Program DialogApp;
uses
Windows;

type
	pt=record
		x:Integer;
		y:Integer;
	End;

const
	IDC_BTN1=1001;

var
	hinstance:HANDLE;
	p:pt;

Function DlgProc (Window:HWND;AMessage:UINT;WParam : WPARAM; LParam:LPARAM):LResult;StdCall;Export;
Var
	nrmenu:LongInt;
	trect:RECT;
	x,y:Integer;
	hBtn:HWND;

Begin
	Case AMessage Of
	WM_CLOSE:
		Begin
		EndDialog(Window,0);
		End;
 	WM_COMMAND:
		Begin
			NrMenu := WParam And $FFFF;
			Case NrMenu Of
			IDC_BTN1:
				Begin
					MessageBox (Window, 'Hello world, hello pascal!' , 'FreePascal', MB_OK);
					EndDialog(Window,0);
				End;
			End;
		End;
	WM_SIZE:
	    Begin
			GetClientRect(Window,trect);
			hBtn:=GetDlgItem(Window,IDC_BTN1);
			x:=trect.right-100;
			y:=trect.bottom-35;
			MoveWindow(hBtn,x,y,82,22,TRUE);
	    End;
	WM_NULL:
		Begin
			DlgProc := DefDlgProc(Window,AMessage,WParam,LParam);
		End;
	End;
	DlgProc := 0;
End;

Begin
	hinstance:=GetModuleHandle(NIL);
	DialogBoxParam(hinstance, 'MAIN',0, DlgProc, 0);   //execute the MAIN dialog
	ExitProcess(0);
end.
