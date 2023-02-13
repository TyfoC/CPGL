#pragma once
#ifndef CPGL_HPP
#define CPGL_HPP

#include <cstdint>

class CPGL {
public:
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

	typedef struct Vector2D {
		ptrdiff_t	X;
		ptrdiff_t	Y;
	} VectorD2, *PVector2D;

	typedef struct Size2D {
		ptrdiff_t	Width;
		ptrdiff_t	Height;
	} Size2D, *PSize2D;

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

	bool IsPointOnEdge(Vector2D point, Vector2D start, Vector2D end);

	void DrawRectangle(const Color color, Vector2D start, Size2D size);
	void DrawLine(const Color color, Vector2D start, Vector2D end);				//	Bresenham's line drawing algorithm
	void DrawTriangle(const Color color, Vector2D vertex1, Vector2D vertex2, Vector2D vertex3);	//	^^^

	virtual void CopyOutputToBuffer() = 0;
	virtual void CopyBufferToOutput() = 0;
protected:
	size_t		m_width;
	size_t		m_height;
	DisplayMode	m_displayMode;
	uint8_t*	m_buffer;
	bool		m_bufferAllocatedManually;
};

#endif