#ifndef CPGL_H
#include "CPGL.h"

template<typename T> T CPGL::Math::Abs(const T value) {
	return value >= 0 ? value : -value;
}

template<typename T> void CPGL::Math::Swap(T& left, T& right) {
	T tmp = left;
	left = right;
	right = tmp;
}

template<typename T> T& CPGL::Math::Min(T& left, T& right) {
	return left < right ? left : right;
}

template<typename T> T& CPGL::Math::Max(T& left, T& right) {
	return left > right ? left : right;
}

CPGL::Color::Color() {
	Value = 0;
}

CPGL::Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
	Value = (uint32_t)((red << 16) | (green << 8) | blue);
}

CPGL::Color& CPGL::Color::operator=(const Color& value) {
	Value = value.Value;
	return *this;
}

CPGL::Color::operator uint32_t() const {
	return Value;
}

CPGL::CPGL() {
	m_width = 0;
	m_height = 0;
	m_displayMode = DisplayMode::Undefined;
	m_bufferAllocatedManually = false;
	m_buffer = 0;
}

CPGL::CPGL(size_t width, size_t height, const DisplayMode displayMode) {
	m_width = width;
	m_height = height;
	m_displayMode = displayMode;
	m_bufferAllocatedManually = false;

	switch (m_displayMode) {
	case DisplayMode::RGB24:
		m_buffer = new uint8_t[width * height * 3];
		break;
	default:
		m_buffer = 0;
		break;
	}
}

CPGL::CPGL(void*& buffer, size_t width, size_t height, const DisplayMode displayMode) {
	m_width = width;
	m_height = height;
	m_displayMode = displayMode;
	m_bufferAllocatedManually = true;
	m_buffer = (uint8_t*)buffer;

	switch (m_displayMode) {
	case DisplayMode::RGB24:
		break;
	default:
		m_buffer = 0;
		break;
	}
}

CPGL::~CPGL() {
	m_width = 0;
	m_height = 0;
	m_displayMode = DisplayMode::Undefined;
	if (!m_bufferAllocatedManually && m_buffer) delete[] m_buffer;
}

void CPGL::SetWidth(size_t width) {
	m_width = width;
}

void CPGL::SetHeight(size_t height) {
	m_height = height;
}

void CPGL::SetDisplayMode(const DisplayMode displayMode) {
	m_displayMode = displayMode;
}

size_t CPGL::GetWidth() {
	return m_width;
}

size_t CPGL::GetHeight() {
	return m_height;
}

CPGL::DisplayMode CPGL::GetDisplayMode() {
	return m_displayMode;
}

bool CPGL::IsBufferAllocatedManually() {
	return m_bufferAllocatedManually;
}

CPGL::Status CPGL::DrawPixel(const Color color, ptrdiff_t x1, ptrdiff_t y1) {
	return DrawPixel(color, y1 * m_width + x1);
}

CPGL::Status CPGL::DrawPixel(const Color color, size_t offset) {
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		offset *= 3;
		m_buffer[offset] = color.Value & 0xff;
		m_buffer[offset + 1] = (color.Value >> 8) & 0xff;
		m_buffer[offset + 2] = (color.Value >> 16) & 0xff;
		break;
	default:
		return Status::UndefinedDisplayMode;
	}

	return Status::Success;
}

CPGL::Status CPGL::DrawLine(Color color, ptrdiff_t x1, ptrdiff_t y1, ptrdiff_t x2, ptrdiff_t y2) {
	const ptrdiff_t distanceX = Math::Abs(x2 - x1);
	const ptrdiff_t distanceY = Math::Abs(y2 - y1);
	const ptrdiff_t signX = x1 < x2 ? 1 : -1;
	const ptrdiff_t signY = y1 < y2 ? 1 : -1;

	DrawPixel(color, x2, y2);

	ptrdiff_t differenceXY = distanceX - distanceY, tmp;
	while (x1 != x2 || y1 != y2) {
		DrawPixel(color, x1, y1);

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

	return Status::Success;
}

CPGL::Status CPGL::DrawSquare(const Color color, ptrdiff_t x, ptrdiff_t y, ptrdiff_t width, ptrdiff_t height) {
	const ptrdiff_t stepX = width > 0 ? 1 : -1;
	const ptrdiff_t stepY = height > 0 ? 1 : -1;

	width += x;
	height += y;

	ptrdiff_t x1;
	for (; y != height; y += stepY) for (x1 = x; x1 != width; x1 += stepX) DrawPixel(color, x1, y);

	return Status::Success;
}

CPGL::Status CPGL::DrawCircle(const Color color, ptrdiff_t x, ptrdiff_t y, size_t radius) {
	ptrdiff_t offsetX = 0;
	ptrdiff_t offsetY = radius;
	ptrdiff_t f = 1 - radius;

	DrawLine(color, x, y, x + radius, y);
	DrawLine(color, x, y, x - radius, y);
	DrawLine(color, x, y, x, y + radius);
	DrawLine(color, x, y, x, y - radius);

	while (offsetX < offsetY) {
		offsetX += 1;
		if (f < 0) f += 2 * offsetX + 1;
		else {
			f += 2 * (offsetX - offsetY + 1);
			offsetY -= 1;
		}

		DrawLine(color, x + offsetX, y + offsetX, x + offsetX, y + offsetY);
		DrawLine(color, x - offsetX, y + offsetX, x - offsetX, y + offsetY);
		DrawLine(color, x + offsetX, y - offsetX, x + offsetX, y - offsetY);
		DrawLine(color, x - offsetX, y - offsetX, x - offsetX, y - offsetY);
		DrawLine(color, x + offsetX, y + offsetX, x + offsetY, y + offsetX);
		DrawLine(color, x + offsetX, y + offsetX, x - offsetY, y + offsetX);
		DrawLine(color, x + offsetX, y - offsetX, x + offsetY, y - offsetX);
		DrawLine(color, x + offsetX, y - offsetX, x - offsetY, y - offsetX);
	}

	return Status::Success;
}

#endif