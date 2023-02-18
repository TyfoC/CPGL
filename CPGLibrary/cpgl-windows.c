#include "cpgl-windows.h"

#ifdef __cplusplus
extern "C" {
#endif
	cpgl_windows_ctx_t cpgl_create_windows_context(const HDC device_context) {
		cpgl_windows_ctx_t context = { 0 };

		context.cpgl_context.size.width = GetDeviceCaps(device_context, HORZRES);
		context.cpgl_context.size.height = GetDeviceCaps(device_context, VERTRES);
		context.cpgl_context.mode = CPGL_MODE_RGB24;
		context.cpgl_context.buffer = 0;

		BITMAPINFO bmi;
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = (LONG)context.cpgl_context.size.width;
		bmi.bmiHeader.biHeight = -(LONG)context.cpgl_context.size.height;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;

		context.device_context = device_context;
		context.dib_section_bitmap = CreateDIBSection(context.device_context, &bmi, DIB_RGB_COLORS, (void**)&context.cpgl_context.buffer, 0, 0);
		context.bitmap_context = CreateCompatibleDC(context.device_context);
		context.old_bitmap_context = context.dib_section_bitmap ? SelectObject(context.bitmap_context, context.dib_section_bitmap) : 0;

		return context;
	}

	void cpgl_free_windows_context(const cpgl_windows_ctx_t context) {
		cpgl_free_context(context.cpgl_context);

		if (context.dib_section_bitmap) {
			SelectObject(context.bitmap_context, context.old_bitmap_context);
			DeleteDC(context.bitmap_context);
			DeleteObject(context.dib_section_bitmap);
		}
	}

	cpgl_status_t cpgl_windows_update_buffer(const cpgl_windows_ctx_t context) {
		if (!context.cpgl_context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;

		if (context.dib_section_bitmap) {
			switch (context.cpgl_context.mode) {
			case CPGL_MODE_RGB24:
				BitBlt(
					context.bitmap_context, 0, 0, (int)context.cpgl_context.size.width, (int)context.cpgl_context.size.height,
					context.device_context, 0, 0, SRCCOPY
				);
				break;
			default:
				return CPGL_STATUS_UNDEFINED_MODE;
			}
		}

		return CPGL_STATUS_SUCCESS;
	}

	cpgl_status_t cpgl_windows_draw_buffer(const cpgl_windows_ctx_t context) {
		if (!context.cpgl_context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;

		if (context.dib_section_bitmap) {
			switch (context.cpgl_context.mode) {
			case CPGL_MODE_RGB24:
				BitBlt(
					context.device_context, 0, 0, (int)context.cpgl_context.size.width, (int)context.cpgl_context.size.height,
					context.bitmap_context, 0, 0, SRCCOPY
				);
				break;
			default:
				return CPGL_STATUS_UNDEFINED_MODE;
			}
		}

		return CPGL_STATUS_SUCCESS;
	}
#ifdef __cplusplus
}
#endif