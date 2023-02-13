#include <iostream>
#include "CPGLWinAPI.hpp"

int main(int argc, char** argv) {
	CPGLWinAPI devCtx(GetDC(0));
	while (1) {
		devCtx.CopyOutputToBuffer();

		devCtx.DrawRectangle(CPGL::Color(0xff, 0, 0), { 100, 100 }, { 200, 200 });
		devCtx.DrawLine(CPGL::Color(0xff, 0, 0xff), { 100, 100 }, { 299, 299 });
		devCtx.DrawTriangle(CPGL::Color(0xff, 0x7f, 0x3f), { 500, 500 }, { 700, 800 }, { 200, 600 });

		devCtx.CopyBufferToOutput();
		Sleep(1);
	}
}