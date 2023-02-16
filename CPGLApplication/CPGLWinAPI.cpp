#ifndef CPGL_WINAPI_H
#include "CPGLWinAPI.h"

CPGLWinAPI::CPGLWinAPI(const HDC devCtx) : CPGL() {
	m_devCtx = devCtx;
	m_width = GetDeviceCaps(devCtx, HORZRES);
	m_height = GetDeviceCaps(devCtx, VERTRES);
	m_displayMode = DisplayMode::RGB24;
	m_buffer = 0;
	m_bufferAllocatedManually = true;

	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = (LONG)m_width;
	bmi.bmiHeader.biHeight = -(LONG)m_height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	m_dibSection = CreateDIBSection(devCtx, &bmi, DIB_RGB_COLORS, (void**)&m_buffer, 0, 0);
	m_bmpCtx = CreateCompatibleDC(m_devCtx);
	m_oldBmp = m_dibSection ? SelectObject(m_bmpCtx, m_dibSection) : 0;
}

CPGLWinAPI::~CPGLWinAPI() {
	if (m_dibSection) {
		SelectObject(m_bmpCtx, m_oldBmp);
		DeleteDC(m_bmpCtx);
		DeleteObject(m_dibSection);
	}
}

CPGL::Status CPGLWinAPI::CopyOutputToBuffer() {
	if (m_dibSection) switch (m_displayMode) {
	case DisplayMode::RGB24:
		BitBlt(m_bmpCtx, 0, 0, (int)m_width, (int)m_height, m_devCtx, 0, 0, SRCCOPY);
		break;
	default:
		return Status::UndefinedDisplayMode;
	}

	return Status::Success;
}

CPGL::Status CPGLWinAPI::CopyBufferToOutput() {
	if (m_dibSection) switch (m_displayMode) {
	case DisplayMode::RGB24:
		BitBlt(m_devCtx, 0, 0, (int)m_width, (int)m_height, m_bmpCtx, 0, 0, SRCCOPY);
		break;
	default:
		return Status::UndefinedDisplayMode;
	}

	return Status::Success;
}

#endif