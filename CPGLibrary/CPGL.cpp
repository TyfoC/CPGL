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

ptrdiff_t CPGL::Math::DoubleToLong(const double& value) {
	return (ptrdiff_t)value + ((value - (double)(ptrdiff_t)value) >= 0.5 ? 1 : 0);
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
	m_bufferSize = { 0, 0 };
	m_displayMode = DisplayMode::Undefined;
	m_bufferAllocatedManually = false;
	m_buffer = 0;
}

CPGL::CPGL(Size2D bufferSize, const DisplayMode displayMode) {
	m_bufferSize = bufferSize;
	m_displayMode = displayMode;
	m_bufferAllocatedManually = false;

	switch (m_displayMode) {
	case DisplayMode::RGB24:
		m_buffer = new uint8_t[(size_t)(m_bufferSize.Width * m_bufferSize.Height) * 3];
		break;
	default:
		m_buffer = 0;
		break;
	}
}

CPGL::CPGL(void*& buffer, Size2D bufferSize, const DisplayMode displayMode) {
	m_bufferSize = bufferSize;
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
	m_bufferSize = { 0, 0 };
	m_displayMode = DisplayMode::Undefined;
	if (!m_bufferAllocatedManually && m_buffer) delete[] m_buffer;
}

void CPGL::SetBufferSize(Size2D bufferSize) {
	m_bufferSize = m_bufferSize;
}

void CPGL::SetDisplayMode(const DisplayMode displayMode) {
	m_displayMode = displayMode;
}

CPGL::Size2D CPGL::GetBufferSize() {
	return m_bufferSize;
}

CPGL::DisplayMode CPGL::GetDisplayMode() {
	return m_displayMode;
}

bool CPGL::IsBufferAllocatedManually() {
	return m_bufferAllocatedManually;
}

CPGL::Status CPGL::DrawPoint(const Color color, Point2D point) {
	size_t offset;
	switch (m_displayMode) {
	case DisplayMode::RGB24:
		offset = 3 * (size_t)(point.Y * m_bufferSize.Width + point.X);
		m_buffer[offset] = color.Value & 0xff;
		m_buffer[offset + 1] = (color.Value >> 8) & 0xff;
		m_buffer[offset + 2] = (color.Value >> 16) & 0xff;
		break;
	default:
		return Status::UndefinedDisplayMode;
	}

	return Status::Success;
}

CPGL::Status CPGL::DrawLine(Color color, Point2D startPoint, Point2D endPoint) {
	ptrdiff_t x1 = Math::DoubleToLong(startPoint.X);
	ptrdiff_t y1 = Math::DoubleToLong(startPoint.Y);
	ptrdiff_t x2 = Math::DoubleToLong(endPoint.X);
	ptrdiff_t y2 = Math::DoubleToLong(endPoint.Y);

	const ptrdiff_t distanceX = Math::Abs(x2 - x1);
	const ptrdiff_t distanceY = Math::Abs(y2 - y1);
	const ptrdiff_t signX = x1 < x2 ? 1 : -1;
	const ptrdiff_t signY = y1 < y2 ? 1 : -1;

	DrawPoint(color, { (double)x2, (double)y2 });

	ptrdiff_t differenceXY = distanceX - distanceY, tmp;
	while (x1 != x2 || y1 != y2) {
		DrawPoint(color, { (double)x1, (double)y1 });

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

CPGL::Status CPGL::DrawSquare(const Color color, Point2D leftPoint, Size2D size) {
	ptrdiff_t x = Math::DoubleToLong(leftPoint.X);
	ptrdiff_t y = Math::DoubleToLong(leftPoint.Y);
	ptrdiff_t width = Math::DoubleToLong(size.Width);
	ptrdiff_t height = Math::DoubleToLong(size.Height);

	const ptrdiff_t stepX = width > 0 ? 1 : -1;
	const ptrdiff_t stepY = height > 0 ? 1 : -1;

	width += x;
	height += y;

	ptrdiff_t x1;
	for (; y != height; y += stepY) for (x1 = x; x1 != width; x1 += stepX) DrawPoint(color, { (double)x1, (double)y });

	return Status::Success;
}

CPGL::Status CPGL::DrawCircle(const Color color, Point2D centerPoint, size_t radius) {
	ptrdiff_t x = Math::DoubleToLong(centerPoint.X);
	ptrdiff_t y = Math::DoubleToLong(centerPoint.Y);
	ptrdiff_t offsetX = 0;
	ptrdiff_t offsetY = radius;
	ptrdiff_t f = 1 - radius;

	DrawLine(color, { (double)x, (double)y }, { (double)(x + radius), (double)y });
	DrawLine(color, { (double)x, (double)y }, { (double)(x - radius), (double)y });
	DrawLine(color, { (double)x, (double)y }, { (double)x, (double)(y + radius) });
	DrawLine(color, { (double)x, (double)y }, { (double)x, (double)(y - radius) });

	while (offsetX < offsetY) {
		offsetX += 1;
		if (f < 0) f += 2 * offsetX + 1;
		else {
			f += 2 * (offsetX - offsetY + 1);
			offsetY -= 1;
		}

		DrawLine(color, { (double)(x + offsetX), (double)(y + offsetX) }, { (double)(x + offsetX), (double)(y + offsetY) });
		DrawLine(color, { (double)(x - offsetX), (double)(y + offsetX) }, { (double)(x - offsetX), (double)(y + offsetY) });
		DrawLine(color, { (double)(x + offsetX), (double)(y - offsetX) }, { (double)(x + offsetX), (double)(y - offsetY) });
		DrawLine(color, { (double)(x - offsetX), (double)(y - offsetX) }, { (double)(x - offsetX), (double)(y - offsetY) });
		DrawLine(color, { (double)(x + offsetX), (double)(y + offsetX) }, { (double)(x + offsetY), (double)(y + offsetX) });
		DrawLine(color, { (double)(x + offsetX), (double)(y + offsetX) }, { (double)(x - offsetY), (double)(y + offsetX) });
		DrawLine(color, { (double)(x + offsetX), (double)(y - offsetX) }, { (double)(x + offsetY), (double)(y - offsetX) });
		DrawLine(color, { (double)(x + offsetX), (double)(y - offsetX) }, { (double)(x - offsetY), (double)(y - offsetX) });
	}

	return Status::Success;
}

CPGL::Status CPGL::DrawPolygon(const Color color, const Point2D* points, size_t count) {
	if (count < 3) return count == 2 ? DrawLine(color, points[0], points[1]) : Status::InvalidParameter;

	ptrdiff_t minX = Math::DoubleToLong(points[0].X);
	ptrdiff_t minY = Math::DoubleToLong(points[0].Y);
	ptrdiff_t maxX = minX;
	ptrdiff_t maxY = minY;

	ptrdiff_t tmpX, tmpY;
	for (size_t i = 1; i < count; i++) {
		tmpX = Math::DoubleToLong(points[i].X);
		tmpY = Math::DoubleToLong(points[i].Y);
		if (tmpX < minX) minX = tmpX;
		if (tmpX > maxX) maxX = tmpX;

		if (tmpY < minY) minY = tmpY;
		if (tmpY > maxY) maxY = tmpY;
	}

	ptrdiff_t currentX = minX;
	for (; minY <= maxY;) {
		if (IsPointInPolygon(points, count, { (double)currentX, (double)minY })) DrawPoint(color, { (double)currentX, (double)minY });

		if (currentX <= maxX) ++currentX;
		else {
			currentX = 0;
			++minY;
		}
	}

	return Status::Success;
}

bool CPGL::IsPointInPolygon(const Point2D* points, size_t count, Point2D point) {
	ptrdiff_t x = Math::DoubleToLong(point.X);
	ptrdiff_t y = Math::DoubleToLong(point.Y);

	bool pointInPolygon = false;
	size_t j = count - 1;
	ptrdiff_t slope;
	for (size_t i = 0; i < count; i++) {
		if (x == Math::DoubleToLong(points[i].X) && y == Math::DoubleToLong(points[i].Y)) return true;
		else if ((Math::DoubleToLong(points[i].Y) > y) != (Math::DoubleToLong(points[j].Y) > y)) {
			slope = Math::DoubleToLong((x - points[i].X) * (points[j].Y - points[i].Y) - (points[j].X - points[i].X) * (y - points[i].Y));
			if (!slope) return true;
			else if ((slope < 0) != (points[j].Y < points[i].Y)) pointInPolygon = !pointInPolygon;
		}
		j = i;
	}

	return pointInPolygon;
}

#endif
