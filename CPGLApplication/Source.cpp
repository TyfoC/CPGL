#include <iostream>
#include "CPGLWinAPI.hpp"

int main(int argc, char** argv) {
	CPGLWinAPI devCtx(GetDC(0));
	while (1) {
		devCtx.CopyOutputToBuffer();
		devCtx.DrawRectangle(CPGL::Color(0xff, 0, 0), 100, 100, 200, 200);
		devCtx.CopyBufferToOutput();
		Sleep(1);
	}
}