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

	void DrawRectangle(const Color color, ptrdiff_t x, ptrdiff_t y, size_t width, size_t height);

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