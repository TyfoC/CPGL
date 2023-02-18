#pragma once
#ifndef CPGL_H
#define CPGL_H

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#define CpglFastStruct($struct_type, ...)		{ __VA_ARGS__ }
#else
#define CpglFastStruct($struct_type, ...)		($struct_type) { __VA_ARGS__ }

#include <stdint.h>
#include <stdlib.h>		//	malloc, realloc, free

typedef uint8_t bool;
#define false	0
#define true	1
#endif

#define CpglWrongIndex							((size_t)-1)

#define CpglCreateColor($red, $green, $blue)	(cpgl_color_t)(((size_t)$red << 16) | ((size_t)$green << 8) | ($blue & 0xff))
#define CpglExtractRed($color)					(uint8_t)(((size_t)$color >> 16) & 0xff)
#define CpglExtractGreen($color)				(uint8_t)(((size_t)$color >> 8) & 0xff)
#define CpglExtractBlue($color)					(uint8_t)((size_t)$color & 0xff)
#define CpglAddColors($first, $second)			(cpgl_color_t)($first + $second)
#define CpglSubColors($first, $second)			(cpgl_color_t)($first - $second)
#define CpglMulColors($first, $second)			(cpgl_color_t)($first * $second)
#define CpglDivColors($first, $second)			(cpgl_color_t)($first / $second)
#define CpglModColors($first, $second)			(cpgl_color_t)($first % $second)

enum CpglStatuses {
	CPGL_STATUS_SUCCESS,
	CPGL_STATUS_UNDEFINED_MODE,
	CPGL_STATUS_INVALID_PARAMETER,
	CPGL_STATUS_UNINITIALIZED_BUFFER,
	CPGL_STATUS_CANNOT_ALLOCATE_MEMORY
};

//	Display modes
enum CpglModes {
	CPGL_MODE_UNDEFINED,
	CPGL_MODE_VGA8,
	CPGL_MODE_RGB24
};

enum CpglColors {
	CPGL_COLOR_BLACK = 0x000000,
	CPGL_COLOR_GRAY = 0x7f7f7f,
	CPGL_COLOR_WHITE = 0xffffff,
	CPGL_COLOR_RED = 0xff0000,
	CPGL_COLOR_GREEN = 0x00ff00,
	CPGL_COLOR_BLUE = 0x0000ff,
	CPGL_COLOR_YELLOW = 0xffff00,
	CPGL_COLOR_AZURE = 0x00ffff,
	CPGL_COLOR_MAGENTA = 0xff00ff,
	CPGL_COLOR_ORANGE = 0xff7f00,
	CPGL_COLOR_LIME = 0x00ff7f,
	CPGL_COLOR_BROWN = 0x8b4513
};

typedef ptrdiff_t	cpgl_status_t, * pcpgl_status_t;
typedef size_t		cpgl_mode_t, * pcpgl_mode_t;
typedef size_t		cpgl_color_t, * pcpgl_color_t;

typedef struct cpgl_vx2l_t {
	ptrdiff_t	x;
	ptrdiff_t	y;
} cpgl_vx2l_t, * pcpgl_vx2l_t;

typedef struct cpgl_sz2l_t {
	ptrdiff_t	width;
	ptrdiff_t	height;
} cpgl_sz2l_t, * pcpgl_sz2l_t;

/*
	Features (not usable for now):
	typedef struct cpgl_vx2f_t {
		float	x;
		float	y;
	} cpgl_vx2f_t, * pcpgl_vx2f_t;
	typedef struct cpgl_sz2f_t {
		float	width;
		float	height;
	} cpgl_sz2f_t, * pcpgl_sz2f_t;
*/

typedef struct cpgl_ctx_t {
	cpgl_sz2l_t	size;
	cpgl_mode_t	mode;
	uint8_t* buffer;
} cpgl_ctx_t, * pcpgl_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif
	size_t cpgl_math_abs(const ptrdiff_t value);

	cpgl_ctx_t cpgl_create_context(const cpgl_sz2l_t size, const cpgl_mode_t mode);
	cpgl_ctx_t cpgl_resize_context(const cpgl_ctx_t context, const cpgl_sz2l_t size);
	void cpgl_free_context(const cpgl_ctx_t context);

	cpgl_status_t cpgl_draw_pointl(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t vertex);
	cpgl_status_t cpgl_draw_linel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t start, const cpgl_vx2l_t end);
	cpgl_status_t cpgl_draw_squarel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t start, const cpgl_sz2l_t size);
	cpgl_status_t cpgl_draw_circlel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t center, const ptrdiff_t radius);
	cpgl_status_t cpgl_draw_polygonl(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t* vertices, size_t count);
	bool cpgl_is_point_in_polygonl(const cpgl_vx2l_t point, const cpgl_vx2l_t* vertices, size_t count);

	size_t cpgl_get_color_distance_square(const cpgl_color_t color1, const cpgl_color_t color2);
	size_t cpgl_find_nearest_color_index(const cpgl_color_t color, const cpgl_color_t* palette, size_t count);
#ifdef __cplusplus
}
#endif

#endif