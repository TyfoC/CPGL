#pragma once
#ifndef CPGL_WINAPI_H
#define CPGL_WINAPI_H

#include <CPGL.h>

#if not defined(_MSC_VER) || not defined(WINAPI)
#include <Windows.h>
#endif

class CPGLWinAPI : public CPGL {
public:
	CPGLWinAPI(const HDC devCtx = GetDC(0));
	~CPGLWinAPI();

	virtual Status CopyOutputToBuffer() override;
	virtual Status CopyBufferToOutput() override;
protected:
	HDC		m_devCtx;
	HBITMAP	m_dibSection;
	HDC		m_bmpCtx;
	HGDIOBJ	m_oldBmp;
};

#endif