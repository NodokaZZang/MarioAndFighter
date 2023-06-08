#pragma once
#include <Windows.h>
#include <d2d1.h>
class GameWnd
{
private:
	HINSTANCE		   m_hInstance;
	DWORD			   m_width;
	DWORD			   m_height;
	HWND			   m_hwnd;

	IDWriteTextFormat* m_textFormat;
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_brt;
	ID2D1SolidColorBrush* m_brush;
	ID2D1SolidColorBrush* m_brush1;
	ID2D1SolidColorBrush* m_brush2;
	ID2D1SolidColorBrush* m_brush3;
public:
	GameWnd(HINSTANCE, const TCHAR*, const TCHAR*, DWORD, DWORD, int);
	~GameWnd() {};
public:
	static LRESULT CALLBACK  WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void  RenderProcess(ID2D1Bitmap* _bitmap);
public:
	ID2D1BitmapRenderTarget* GetBRT() { return m_brt; }
	ID2D1HwndRenderTarget* GetRT() { return m_rt; }
	ID2D1HwndRenderTarget** GetRRT() { return &m_rt; }
	HWND	GetHwnd() { return m_hwnd; }
	void	SetBrush(D2D1::ColorF _color);
	void	SetBrush(D2D1::ColorF _color, ID2D1SolidColorBrush** _brsuh);
};

