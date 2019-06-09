#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <debug_screen.h>

#define printf psvDebugScreenPrintf

int main(int argc, char *argv[]) {
	psvDebugScreenInit();
	printf("Hello, world!\n");

	sceKernelDelayThread(5*1000000);
	sceKernelExitProcess(0);
	return 0;
}
