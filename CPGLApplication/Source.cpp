#include <cpgl-windows.h>

int main(int argc, char** argv) {
	cpgl_windows_ctx_t ctx = cpgl_create_windows_context(GetDC(0));

	Sleep(1000);

	while (true) {
		cpgl_windows_update_buffer(ctx);

		cpgl_draw_circlel(ctx.cpgl_context, CpglCreateColor(0xff, 0, 0), CpglFastStruct(cpgl_vx2l_t, 200, 200), 100);
		cpgl_draw_linel(ctx.cpgl_context, CpglCreateColor(0xff, 0x7f, 0x3f), CpglFastStruct(cpgl_vx2l_t, 100, 100), CpglFastStruct(cpgl_vx2l_t, 300, 300));
		cpgl_draw_squarel(ctx.cpgl_context, CPGL_COLOR_AZURE, CpglFastStruct(cpgl_vx2l_t, 400, 400), CpglFastStruct(cpgl_vx2l_t, -100, -100));

		cpgl_vx2l_t vertices[] = { { 500, 500 }, { 600, 600 }, { 400, 550 } };
		cpgl_draw_polygonl(ctx.cpgl_context, CPGL_COLOR_YELLOW, vertices, sizeof(vertices) / sizeof(vertices[0]));

		cpgl_windows_draw_buffer(ctx);
		Sleep(1);
	}

	cpgl_free_windows_context(ctx);
}