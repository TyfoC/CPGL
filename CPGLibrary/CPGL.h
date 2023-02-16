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

	typedef struct EdgesX {
		ptrdiff_t*	LeftEdgesX;
		ptrdiff_t* RightEdgesX;
	} EdgesX, *PEdgesX;

	class Math {
	public:
		template<typename T> static T Abs(const T value);
		template<typename T> static void Swap(T& left, T& right);
		template<typename T> static T& Min(T& left, T& right);
		template<typename T> static T& Max(T& left, T& right);
	};

	CPGL();
	CPGL(size_t width, size_t height, const DisplayMode displayMode = DisplayMode::RGB24);
	CPGL(void*& buffer, size_t width, size_t height, const DisplayMode displayMode = DisplayMode::RGB24);
	~CPGL();

	void SetWidth(size_t width);
	void SetHeight(size_t height);
	void SetDisplayMode(const DisplayMode displayMode);

	size_t GetWidth();
	size_t GetHeight();
	DisplayMode GetDisplayMode();

	bool IsBufferAllocatedManually();

	Status DrawPixel(const Color color, ptrdiff_t x1, ptrdiff_t y1);
	Status DrawPixel(const Color color, size_t offset);
	Status DrawLine(const Color color, ptrdiff_t x1, ptrdiff_t y1, ptrdiff_t x2, ptrdiff_t y2);
	Status DrawSquare(const Color color, ptrdiff_t x, ptrdiff_t y, ptrdiff_t width, ptrdiff_t height);
	Status DrawCircle(const Color color, ptrdiff_t x, ptrdiff_t y, size_t radius);

	virtual Status CopyOutputToBuffer() = 0;
	virtual Status CopyBufferToOutput() = 0;
protected:
	size_t		m_width;
	size_t		m_height;
	DisplayMode	m_displayMode;
	uint8_t*	m_buffer;
	bool		m_bufferAllocatedManually;
};

#endif