#include <iostream>
#include "CPGLWinAPI.h"

int main(int argc, char** argv) {
	CPGLWinAPI devCtx(GetDC(0));

	const CPGL::Size2D bufferSize = devCtx.GetBufferSize();
	const size_t width = (size_t)bufferSize.Width, height = (size_t)bufferSize.Height;
	const ptrdiff_t centerX = width / 2, centerY = height / 2;

	const CPGL::Point2D points[] = {
		{ 100, 100 },
		{ 200, 200 },
		{ 100, 300 },
		{ 300, 400 },
		{ 700, 700 },
		{ 400, 50 },
		{ 10, 800 }
	};

	(void)std::getchar();

	devCtx.CopyOutputToBuffer();

	devCtx.DrawCircle(CPGL::Color(0xff, 255, 0), { 355, 355 }, 100);
	devCtx.DrawPolygon({ 0xff, 0xff, 0xff }, points, sizeof(points) / sizeof(points[0]));

	devCtx.CopyBufferToOutput();
}