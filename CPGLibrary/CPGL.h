#pragma once
#ifndef CPGL_H
#define CPGL_H

#include <cstdint>

class CPGL {
public:
	enum class Status {
		Success,
		UndefinedDisplayMode,
		InvalidParameter,
		UninitializedBuffer,
		CannotAllocateMemory,
	};

	enum class DisplayMode {
		Undefined,
		RGB24
	};

	typedef struct Color {
		Color();
		Color(uint8_t red, uint8_t green, uint8_t blue);
		Color& operator=(const Color& value);
		operator uint32_t() const;

		uint32_t	Value;
	} Color, *PColor;

	typedef struct Point2D {
		double	X;
		double	Y;
	} Point2D, *PPoint2D;

	typedef struct Size2D {
		double	Width;
		double	Height;
	} Size2D, *PSize2D;

	class Math {
	public:
		template<typename T> static T Abs(const T value);
		template<typename T> static void Swap(T& left, T& right);
		template<typename T> static T& Min(T& left, T& right);
		template<typename T> static T& Max(T& left, T& right);
		static ptrdiff_t DoubleToLong(const double& value);
	};

	CPGL();
	CPGL(Size2D bufferSize, const DisplayMode displayMode = DisplayMode::RGB24);
	CPGL(void*& buffer, Size2D bufferSize, const DisplayMode displayMode = DisplayMode::RGB24);
	~CPGL();

	void SetBufferSize(Size2D size);
	void SetDisplayMode(const DisplayMode displayMode);

	Size2D GetBufferSize();
	DisplayMode GetDisplayMode();

	bool IsBufferAllocatedManually();

	Status DrawPoint(const Color color, Point2D point);
	Status DrawLine(const Color color, Point2D startPoint, Point2D endPoint);
	Status DrawSquare(const Color color, Point2D leftPoint, Size2D size);
	Status DrawCircle(const Color color, Point2D centerPoint, size_t radius);
	Status DrawPolygon(const Color color, const Point2D* points, size_t count);

	bool IsPointInPolygon(const Point2D* points, size_t count, Point2D point);

	virtual Status CopyOutputToBuffer() = 0;
	virtual Status CopyBufferToOutput() = 0;
protected:
	Size2D		m_bufferSize;
	DisplayMode	m_displayMode;
	uint8_t*	m_buffer;
	bool		m_bufferAllocatedManually;
};

#endif