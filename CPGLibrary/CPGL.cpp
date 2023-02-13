#ifndef CPGL_HPP
#include "CPGL.hpp"

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

bool CPGL::IsPointOnEdge(Vector2D point, Vector2D start, Vector2D end) {
	return (point.Y - start.Y) * (end.X - start.X) - (point.X - start.X) * (end.Y - start.Y) >= 0;
}

void CPGL::DrawRectangle(const Color color, Vector2D start, Size2D size) {
	if (start.X < 0) {
		size.Width += start.X;
		start.X = 0;
	}
	else if (start.X >= m_width) return;

	if (start.Y < 0) {
		size.Height += start.Y;
		start.Y = 0;
	}
	else if (start.Y >= m_height) return;

	if (start.X + size.Width > m_width) size.Width = m_width - start.X;
	if (start.Y + size.Height > m_height) size.Height = m_height - start.Y;

	if (!m_buffer) return;

	size_t colorShift = 0;
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		colorShift = 3;
		break;
	}

	if (!colorShift) return;

	uint8_t* buffPos = &m_buffer[start.Y * m_width * colorShift + start.X * colorShift];

	size.Width += start.X;
	size.Height += start.Y;

	const size_t shiftedWidth = m_width * colorShift;
	const size_t extraShiftedValue = (size.Width - start.X) * colorShift;
	for (; (size_t)start.Y < size.Height; start.Y++) {
		for (size_t xCopy = start.X; (size_t)xCopy < size.Width; xCopy++) {
			if (m_displayMode == DisplayMode::RGB24) {
				*buffPos++ = color.Value & 0xff;
				*buffPos++ = (color.Value >> 8) & 0xff;
				*buffPos++ = (color.Value >> 16) & 0xff;
			}
		}
		buffPos = (uint8_t*)((size_t)buffPos + shiftedWidth - extraShiftedValue);
	}
}

void CPGL::DrawLine(const Color color, Vector2D start, Vector2D end) {
	if (!m_buffer) return;
	else if (start.X > m_width || start.Y > m_height) return;
	else if (end.X > m_width || end.Y > m_height) return;

	size_t colorShift = 0;
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		colorShift = 3;
		break;
	}

	if (!colorShift) return;
	const size_t shiftedWidth = m_width * colorShift;

	ptrdiff_t dx = end.X - start.X;
	ptrdiff_t dy = end.Y - start.Y;

	ptrdiff_t dLong = Math::Abs(dx);
	ptrdiff_t dShort = Math::Abs(dy);

	ptrdiff_t offsetLong = (ptrdiff_t)colorShift * (dx > 0 ? 1 : -1);
	ptrdiff_t offsetShort = (ptrdiff_t)shiftedWidth * (dy > 0 ? 1 : -1);

	if (dLong < dShort) {
		Math::Swap(dShort, dLong);
		Math::Swap(offsetShort, offsetLong);
	}

	ptrdiff_t error = 2 * dShort - dLong;
	ptrdiff_t index = start.Y * shiftedWidth + start.X * colorShift;
	const ptrdiff_t offset[] = { offsetLong, offsetLong + offsetShort };
	const ptrdiff_t abs_d[] = { 2 * dShort, 2 * (dShort - dLong) };
	for (ptrdiff_t i = 0; i <= dLong; ++i) {
		if (m_displayMode == DisplayMode::RGB24) {
			m_buffer[index] = color.Value & 0xff;
			m_buffer[index + 1] = (color.Value >> 8) & 0xff;
			m_buffer[index + 2] = (color.Value >> 16) & 0xff;
		}
		const ptrdiff_t errorIsTooBig = error >= 0;
		index += offset[errorIsTooBig];
		error += abs_d[errorIsTooBig];
	}
}

void CPGL::DrawTriangle(const Color color, Vector2D vertex1, Vector2D vertex2, Vector2D vertex3) {
	float minX = (float)Math::Min(Math::Min(vertex1.X, vertex2.X), vertex3.X);
	float minY = (float)Math::Min(Math::Min(vertex1.Y, vertex2.Y), vertex3.Y);
	float maxX = (float)Math::Max(Math::Max(vertex1.X, vertex2.X), vertex3.X);
	float maxY = (float)Math::Max(Math::Max(vertex1.Y, vertex2.Y), vertex3.Y);

	bool inside;
	float px, py;
	
	size_t colorShift = 0;
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		colorShift = 3;
		break;
	}

	if (!colorShift) return;
	const size_t shiftedWidth = m_width * colorShift;

	for (ptrdiff_t x = (ptrdiff_t)minX; x < (ptrdiff_t)maxX; x++) {
		for (ptrdiff_t y = (ptrdiff_t)minY; y < (ptrdiff_t)maxY; y++) {
			px = x + 0.5f;
			py = y + 0.5f;

			inside = true;
			inside &= IsPointOnEdge({ vertex1.X, vertex1.Y }, { vertex2.X, vertex2.Y }, { (ptrdiff_t)px, (ptrdiff_t)py });
			inside &= IsPointOnEdge({ vertex2.X, vertex2.Y }, { vertex3.X, vertex3.Y }, { (ptrdiff_t)px, (ptrdiff_t)py });
			inside &= IsPointOnEdge({ vertex3.X, vertex3.Y }, { vertex1.X, vertex1.Y }, { (ptrdiff_t)px, (ptrdiff_t)py });

			if (inside) {
				if (m_displayMode == DisplayMode::RGB24) {
					m_buffer[y * shiftedWidth + x * colorShift] = color.Value & 0xff;
					m_buffer[y * shiftedWidth + x * colorShift + 1] = (color.Value >> 8) & 0xff;
					m_buffer[y * shiftedWidth + x * colorShift + 2] = (color.Value >> 16) & 0xff;
				}
			}
		}
	}
}

#endif