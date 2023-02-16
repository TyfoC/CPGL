#include <iostream>
#include "CPGLWinAPI.h"

int main(int argc, char** argv) {
	CPGLWinAPI devCtx(GetDC(0));

	const size_t width = devCtx.GetWidth(), height = devCtx.GetHeight();
	const ptrdiff_t centerX = width / 2, centerY = height / 2;

	while (1) {
		devCtx.CopyOutputToBuffer();

		devCtx.DrawCircle(CPGL::Color(0xff, 255, 0), 355, 355, 100);

		devCtx.CopyBufferToOutput();
		Sleep(1);
	}
}