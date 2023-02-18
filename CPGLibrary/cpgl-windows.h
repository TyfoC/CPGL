#pragma once
#ifndef CPGL_WINDOWS_H
#define CPGL_WINDOWS_H

#include "cpgl.h"

#ifndef WINAPI
#include <Windows.h>
#endif

typedef struct cpgl_windows_ctx_t {
	cpgl_ctx_t	cpgl_context;
	HDC			device_context;
	HBITMAP		dib_section_bitmap;
	HDC			bitmap_context;
	HGDIOBJ		old_bitmap_context;
} cpgl_windows_ctx_t, * pcpgl_windows_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif
	cpgl_windows_ctx_t cpgl_create_windows_context(const HDC device_context);
	void cpgl_free_windows_context(const cpgl_windows_ctx_t context);
	cpgl_status_t cpgl_windows_update_buffer(const cpgl_windows_ctx_t context);
	cpgl_status_t cpgl_windows_draw_buffer(const cpgl_windows_ctx_t context);
#ifdef __cplusplus
}
#endif

#endif