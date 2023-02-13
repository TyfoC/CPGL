#include "CPGL.hpp"

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
	}
}

CPGL::CPGL(void*& buffer, size_t width, size_t height, const DisplayMode displayMode) {
	m_width = width;
	m_height = height;
	m_displayMode = displayMode;
	m_bufferAllocatedManually = true;

	m_buffer = (uint8_t*)buffer;
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

void CPGL::DrawRectangle(const Color color, ptrdiff_t x, ptrdiff_t y, size_t width, size_t height) {
	if (x < 0) {
		width += x;
		x = 0;
	}
	if (y < 0) {
		height += y;
		y = 0;
	}
	if (x + width > m_width) width = m_width - x;
	if (y + height > m_height) height = m_height - y;

	if (!m_buffer) return;

	size_t colorShift = 0;
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		colorShift = 3;
		break;
	}

	if (!colorShift) return;

	uint8_t* buffPos = &m_buffer[y * m_width * colorShift + x * colorShift];

	width += x;
	height += y;

	const size_t shiftedWidth = m_width * colorShift;
	const size_t extraShiftedValue = (width - x) * colorShift;
	for (; (size_t)y < height; y++) {
		for (size_t xCopy = x; (size_t)xCopy < width; xCopy++) {
			if (m_displayMode == DisplayMode::RGB24) {
				*buffPos++ = color.Value & 0xff;
				*buffPos++ = (color.Value >> 8) & 0xff;
				*buffPos++ = (color.Value >> 16) & 0xff;
			}
		}
		buffPos = (uint8_t*)((size_t)buffPos + shiftedWidth - extraShiftedValue);
	}
}