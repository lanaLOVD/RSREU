#include <stdio.h>

/*
В примере ниже в структуре кодируется значение флагов, возвращаемых неким устройством 
а также номер процесса, в результате размер структуры будет упакован в всего 1 байт: 
*/

typedef struct  //typedef позволяет не писать struct в объявлении
{
	unsigned char isReady:1; //используем только первый бит
	unsigned char isError:1; //используем только первый бит
	unsigned char processId:6; //используем только первые 6 бит (т.е. диапазон значений [0...63])
} State;

int main() 
{
	State state={1,0,7};

	printf("[%d bytes] ready=%d err=%d proc=%d",sizeof(State), 
												state.isReady, 
												state.isError, 
												state.processId);
	
	//[1 bytes] ready=1 err=0 proc=7
	
	return 0;
}

