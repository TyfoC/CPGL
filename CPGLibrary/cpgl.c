#include "cpgl.h"

#ifdef __cplusplus
extern "C" {
#endif
	size_t cpgl_math_abs(const ptrdiff_t value) {
		return (size_t)(value >= 0 ? value : -value);
	}

	cpgl_ctx_t cpgl_create_context(const cpgl_sz2l_t size, const cpgl_mode_t mode) {
		cpgl_ctx_t context = { 0 };
		context.size = size;
		context.mode = mode;

		switch (mode) {
		case CPGL_MODE_RGB24:
			context.buffer = (uint8_t*)malloc(size.width * size.height * 3);
			break;
		default:
			context.buffer = 0;
			break;
		}

		return context;
	}

	cpgl_ctx_t cpgl_resize_context(const cpgl_ctx_t context, const cpgl_sz2l_t size) {
		cpgl_sz2l_t new_size = size;
		cpgl_mode_t new_mode = context.mode;
		cpgl_free_context(context);
		return cpgl_create_context(new_size, new_mode);
	}

	void cpgl_free_context(const cpgl_ctx_t context) {
		if (context.buffer) free((void*)context.buffer);
	}

	cpgl_status_t cpgl_draw_pointl(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t vertex) {
		if (!context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;
		//	else if (vertex.x < 0 || vertex.y < 0) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (vertex.x >= context.size.width || vertex.y >= context.size.height) return CPGL_STATUS_INVALID_PARAMETER;

		size_t buffer_offset;
		switch (context.mode) {
		case CPGL_MODE_RGB24:
			buffer_offset = 3 * (vertex.y * context.size.width + vertex.x);
			context.buffer[buffer_offset++] = CpglExtractBlue(color);
			context.buffer[buffer_offset++] = CpglExtractGreen(color);
			context.buffer[buffer_offset] = CpglExtractRed(color);
			break;
		default:
			return CPGL_STATUS_UNDEFINED_MODE;
		}

		return CPGL_STATUS_SUCCESS;
	}

	cpgl_status_t cpgl_draw_linel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t start, const cpgl_vx2l_t end) {
		if (!context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;
		//	else if (start.x < 0 || start.y < 0) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (start.x >= context.size.width || start.y >= context.size.height) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (end.x < 0 || end.y < 0) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (end.x >= context.size.width || end.y >= context.size.height) return CPGL_STATUS_INVALID_PARAMETER;

		ptrdiff_t x1 = start.x;
		ptrdiff_t y1 = start.y;
		ptrdiff_t x2 = end.x;
		ptrdiff_t y2 = end.y;

		const ptrdiff_t distanceX = cpgl_math_abs(x2 - x1);
		const ptrdiff_t distanceY = cpgl_math_abs(y2 - y1);
		const ptrdiff_t signX = x1 < x2 ? 1 : -1;
		const ptrdiff_t signY = y1 < y2 ? 1 : -1;

		cpgl_draw_pointl(context, color, CpglFastStruct(cpgl_vx2l_t, x2, y2));

		ptrdiff_t differenceXY = distanceX - distanceY, tmp;
		while (x1 != x2 || y1 != y2) {
			cpgl_draw_pointl(context, color, CpglFastStruct(cpgl_vx2l_t, x1, y1));

			tmp = differenceXY << 1;
			if (tmp > -distanceY) {
				differenceXY -= distanceY;
				x1 += signX;
			}
			if (tmp < distanceX) {
				differenceXY += distanceX;
				y1 += signY;
			}
		}

		return CPGL_STATUS_SUCCESS;
	}

	cpgl_status_t cpgl_draw_squarel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t start, const cpgl_sz2l_t size) {
		if (!context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;
		//	else if (start.x < 0 || start.y < 0) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (start.x >= context.size.width || start.y >= context.size.height) return CPGL_STATUS_INVALID_PARAMETER;

		ptrdiff_t x = start.x;
		ptrdiff_t y = start.y;
		ptrdiff_t width = size.width;
		ptrdiff_t height = size.height;

		const ptrdiff_t stepX = width > 0 ? 1 : -1;
		const ptrdiff_t stepY = height > 0 ? 1 : -1;

		width += x;
		height += y;

		//	if (width < 0 || height < 0) return CPGL_STATUS_INVALID_PARAMETER;
		//	else if (width > context.size.width || height > context.size.height) return CPGL_STATUS_INVALID_PARAMETER;

		ptrdiff_t x1;
		for (; y != height; y += stepY) {
			for (x1 = x; x1 != width; x1 += stepX) {
				cpgl_draw_pointl(context, color, CpglFastStruct(cpgl_vx2l_t, x1, y));
			}
		}

		return CPGL_STATUS_SUCCESS;
	}

	cpgl_status_t cpgl_draw_circlel(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t center, const ptrdiff_t radius) {
		if (!context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;

		ptrdiff_t x = center.x;
		ptrdiff_t y = center.y;
		ptrdiff_t offsetX = 0;
		ptrdiff_t offsetY = radius;
		ptrdiff_t f = 1 - radius;

		cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x, y), CpglFastStruct(cpgl_vx2l_t, x + radius, y));
		cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x, y), CpglFastStruct(cpgl_vx2l_t, x - radius, y));
		cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x, y), CpglFastStruct(cpgl_vx2l_t, x, y + radius));
		cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x, y), CpglFastStruct(cpgl_vx2l_t, x, y - radius));

		while (offsetX < offsetY) {
			offsetX += 1;
			if (f < 0) f += 2 * offsetX + 1;
			else {
				f += 2 * (offsetX - offsetY + 1);
				offsetY -= 1;
			}

			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y + offsetX), CpglFastStruct(cpgl_vx2l_t, x + offsetX, y + offsetY));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x - offsetX, y + offsetX), CpglFastStruct(cpgl_vx2l_t, x - offsetX, y + offsetY));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y - offsetX), CpglFastStruct(cpgl_vx2l_t, x + offsetX, y - offsetY));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x - offsetX, y - offsetX), CpglFastStruct(cpgl_vx2l_t, x - offsetX, y - offsetY));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y + offsetX), CpglFastStruct(cpgl_vx2l_t, x + offsetY, y + offsetX));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y + offsetX), CpglFastStruct(cpgl_vx2l_t, x - offsetY, y + offsetX));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y - offsetX), CpglFastStruct(cpgl_vx2l_t, x + offsetY, y - offsetX));
			cpgl_draw_linel(context, color, CpglFastStruct(cpgl_vx2l_t, x + offsetX, y - offsetX), CpglFastStruct(cpgl_vx2l_t, x - offsetY, y - offsetX));
		}

		return CPGL_STATUS_SUCCESS;
	}

	cpgl_status_t cpgl_draw_polygonl(const cpgl_ctx_t context, const cpgl_color_t color, const cpgl_vx2l_t* vertices, size_t count) {
		if (!context.buffer) return CPGL_STATUS_UNINITIALIZED_BUFFER;
		else if (count < 3) return count == 2 ? cpgl_draw_linel(context, color, vertices[0], vertices[1]) : CPGL_STATUS_INVALID_PARAMETER;

		ptrdiff_t minX = vertices[0].x;
		ptrdiff_t minY = vertices[0].y;
		ptrdiff_t maxX = minX;
		ptrdiff_t maxY = minY;

		ptrdiff_t tmpX, tmpY;
		for (size_t i = 1; i < count; i++) {
			tmpX = vertices[i].x;
			tmpY = vertices[i].y;
			if (tmpX < minX) minX = tmpX;
			if (tmpX > maxX) maxX = tmpX;

			if (tmpY < minY) minY = tmpY;
			if (tmpY > maxY) maxY = tmpY;
		}

		ptrdiff_t currentX = minX;
		for (; minY <= maxY;) {
			if (cpgl_is_point_in_polygonl(CpglFastStruct(cpgl_vx2l_t, currentX, minY), vertices, count)) {
				cpgl_draw_pointl(context, color, CpglFastStruct(cpgl_vx2l_t, currentX, minY));
			}

			if (currentX <= maxX) ++currentX;
			else {
				currentX = 0;
				++minY;
			}
		}


		return CPGL_STATUS_SUCCESS;
	}

	bool cpgl_is_point_in_polygonl(const cpgl_vx2l_t point, const cpgl_vx2l_t* vertices, size_t count) {
		ptrdiff_t x = point.x;
		ptrdiff_t y = point.y;

		bool pointInPolygon = false;
		size_t j = count - 1;
		ptrdiff_t slope;
		for (size_t i = 0; i < count; i++) {
			if (x == vertices[i].x && y == vertices[i].y) return true;
			else if ((vertices[i].y > y) != (vertices[j].y > y)) {
				slope = (x - vertices[i].x) * (vertices[j].y - vertices[i].y) - (vertices[j].x - vertices[i].x) * (y - vertices[i].y);

				if (!slope) return true;
				else if ((slope < 0) != (vertices[j].y < vertices[i].y)) pointInPolygon = !pointInPolygon;
			}
			j = i;
		}

		return pointInPolygon;
	}
#ifdef __cplusplus
}
#endif