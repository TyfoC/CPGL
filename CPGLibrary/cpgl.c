#include "cpgl.h"

const cpgl_color_t CpglPaletteVGA8[] = {
	0x000000, 0x030303, 0x171717, 0x181818,
	0xb8b8b8, 0xb9b9b9, 0xbababa, 0xbbbbbb,
	0x7e7e7e, 0x7f7f7f, 0x828282, 0x838383,
	0xdbdbdb, 0xdcdcdc, 0xf0f0f0, 0xf3f3f3,
	0x000000, 0x202020, 0x252525, 0x424242,
	0x717171, 0x7e7e7e, 0x8a8a8a, 0xa8a8a8,
	0xb4b4b4, 0xb5b5b5, 0xbbbbbb, 0xbcbcbc,
	0xcbcbcb, 0xcfcfcf, 0xd3d3d3, 0xf3f3f3,
	0x040404, 0x585858, 0xa9a9a9, 0xc6c6c6,
	0xd9d9d9, 0xd8d8d8, 0xd7d7d7, 0xd6d6d6,
	0xd5d5d5, 0xdadada, 0xdddddd, 0xe9e9e9,
	0xefefef, 0xc8c8c8, 0xaeaeae, 0x6f6f6f,
	0x1a1a1a, 0x1b1b1b, 0x1c1c1c, 0x1d1d1d,
	0x1e1e1e, 0x191919, 0x161616, 0x0f0f0f,
	0xaaaaaa, 0xb6b6b6, 0xc7c7c7, 0xcdcdcd,
	0xe2e2e2, 0xe1e1e1, 0xe0e0e0, 0xdfdfdf,
	0xdedede, 0xe3e3e3, 0xeaeaea, 0xececec,
	0xf1f1f1, 0xd0d0d0, 0xc9c9c9, 0xb7b7b7,
	0xafafaf, 0xb0b0b0, 0xb1b1b1, 0xb2b2b2,
	0xb3b3b3, 0xadadad, 0xacacac, 0xababab,
	0xbdbdbd, 0xcacaca, 0xcecece, 0xd2d2d2,
	0xe8e8e8, 0xe7e7e7, 0xe6e6e6, 0xe5e5e5,
	0xe4e4e4, 0xebebeb, 0xededed, 0xeeeeee,
	0xf2f2f2, 0xd4d4d4, 0xd1d1d1, 0xcccccc,
	0xc1c1c1, 0xc2c2c2, 0xc3c3c3, 0xc4c4c4,
	0xc5c5c5, 0xc0c0c0, 0xbfbfbf, 0xbebebe,
	0x020202, 0x222222, 0x444444, 0x7c7c7c,
	0x919191, 0x909090, 0x8f8f8f, 0x8e8e8e,
	0x8d8d8d, 0x929292, 0x939393, 0x9f9f9f,
	0xa5a5a5, 0x808080, 0x4b4b4b, 0x232323,
	0x111111, 0x121212, 0x131313, 0x141414,
	0x151515, 0x101010, 0x090909, 0x060606,
	0x464646, 0x707070, 0x7d7d7d, 0x868686,
	0x989898, 0x979797, 0x969696, 0x959595,
	0x949494, 0x999999, 0xa0a0a0, 0xa2a2a2,
	0xa6a6a6, 0x888888, 0x818181, 0x727272,
	0x4c4c4c, 0x4d4d4d, 0x4e4e4e, 0x4f4f4f,
	0x505050, 0x4a4a4a, 0x494949, 0x484848,
	0x737373, 0x848484, 0x878787, 0x8b8b8b,
	0x9e9e9e, 0x9d9d9d, 0x9c9c9c, 0x9b9b9b,
	0x9a9a9a, 0xa1a1a1, 0xa3a3a3, 0xa4a4a4,
	0xa7a7a7, 0x8c8c8c, 0x898989, 0x858585,
	0x777777, 0x787878, 0x797979, 0x7a7a7a,
	0x7b7b7b, 0x767676, 0x757575, 0x747474,
	0x010101, 0x1f1f1f, 0x242424, 0x3b3b3b,
	0x575757, 0x565656, 0x555555, 0x545454,
	0x535353, 0x595959, 0x5a5a5a, 0x666666,
	0x6c6c6c, 0x3e3e3e, 0x2a2a2a, 0x212121,
	0x0a0a0a, 0x0b0b0b, 0x0c0c0c, 0x0d0d0d,
	0x0e0e0e, 0x080808, 0x070707, 0x050505,
	0x262626, 0x303030, 0x3c3c3c, 0x454545,
	0x5f5f5f, 0x5e5e5e, 0x5d5d5d, 0x5c5c5c,
	0x5b5b5b, 0x606060, 0x676767, 0x6a6a6a,
	0x6d6d6d, 0x474747, 0x3f3f3f, 0x313131,
	0x2b2b2b, 0x2c2c2c, 0x2d2d2d, 0x2e2e2e,
	0x2f2f2f, 0x292929, 0x282828, 0x272727,
	0x323232, 0x3d3d3d, 0x414141, 0x515151,
	0x656565, 0x646464, 0x636363, 0x626262,
	0x616161, 0x686868, 0x696969, 0x6b6b6b,
	0x6e6e6e, 0x525252, 0x434343, 0x404040,
	0x363636, 0x373737, 0x383838, 0x393939,
	0x3a3a3a, 0x353535, 0x343434, 0x333333,
	0x000000, 0x000000, 0x000000, 0x000000,
	0x000000, 0x000000, 0x000000, 0x000000
};

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
		case CPGL_MODE_VGA8:
			context.buffer = (uint8_t*)malloc(size.width * size.height);
			break;
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
		case CPGL_MODE_VGA8:
			// uint8_t color_index;				//	only for index color palettes
			// color_index = (uint8_t)cpgl_find_nearest_color_index(color, CpglPaletteVGA8, sizeof(CpglPaletteVGA8) / sizeof(CpglPaletteVGA8[0]));
			buffer_offset = vertex.y * context.size.width + vertex.x;
			context.buffer[buffer_offset] = (uint8_t)color;
			break;
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

	size_t cpgl_get_color_distance_square(const cpgl_color_t color1, const cpgl_color_t color2) {
		const size_t distanceRed = CpglExtractRed(color1) - CpglExtractRed(color2);
		const size_t distanceGreen = CpglExtractGreen(color1) - CpglExtractGreen(color2);
		const size_t distanceBlue = CpglExtractBlue(color1) - CpglExtractBlue(color2);
		return distanceRed * distanceRed + distanceGreen * distanceGreen + distanceBlue * distanceBlue;
	}

	size_t cpgl_find_nearest_color_index(const cpgl_color_t color, const cpgl_color_t* palette, size_t count) {
		size_t currentColorDistance,  nearestColorDistance = 0x2FA03;	//	255 * 255 + 255 * 255 + 255 * 255 - square of max color distance
		size_t nearestIndex = CpglWrongIndex;

		for (size_t i = 0; i < count; i++) {
			currentColorDistance = cpgl_get_color_distance_square(color, palette[i]);
			if (currentColorDistance < nearestColorDistance) {
				nearestColorDistance = currentColorDistance;
				nearestIndex = i;
			}
		}

		return nearestIndex;
	}
#ifdef __cplusplus
}
#endif