#pragma once
#ifndef CPGL_WINAPI_HXX
#define CPGL_WINAPI_HXX

#include <CPGL.hpp>

#if not defined(_MSC_VER) || not defined(WINAPI)
#pragma message("Windows.h library wasn't included!")
#include <Windows.h>
#endif

class CPGLWinAPI : public CPGL {
public:
	CPGLWinAPI(const HDC devCtx = GetDC(0));
	~CPGLWinAPI();

	virtual void CopyOutputToBuffer() override;
	virtual void CopyBufferToOutput() override;
protected:
	HDC		m_devCtx;
	HBITMAP	m_dibSection;
	HDC		m_bmpCtx;
	HGDIOBJ	m_oldBmp;
};

#endif