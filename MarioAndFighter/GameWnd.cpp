#include "pch.h"
#include "GameWnd.h"
#include "Text.h"
#include "SceenManager.h"
GameWnd::GameWnd(HINSTANCE _hInstance, const TCHAR* _title, const TCHAR* _className, DWORD _width, DWORD _height, int _ncmdShow)
{
	m_width = _width;
	m_height = _height;
	m_hInstance = _hInstance;

	WNDCLASSEX wecx;
	wecx.cbSize = sizeof(WNDCLASSEX);
	wecx.style = CS_HREDRAW | CS_VREDRAW;
	wecx.cbClsExtra = 0;
	wecx.cbWndExtra = sizeof(LONG_PTR);
	wecx.hInstance = _hInstance;
	wecx.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wecx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wecx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wecx.lpszClassName = _className;
	wecx.lpszMenuName = nullptr;
	wecx.hIconSm = LoadIcon(wecx.hInstance, IDI_APPLICATION);
	wecx.lpfnWndProc = WndProc;  // �����Լ�
	if (!RegisterClassEx(&wecx))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx Main failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return;
	}

	m_hwnd = CreateWindow(
		_className,
		_title,
		WS_OVERLAPPEDWINDOW,
		1200, 0,
		_width, _height,
		NULL,
		NULL,
		_hInstance,
		this);

	D2D1Core::GetInstance()->CreateRenderTarget(m_hwnd, &m_rt);
	D2D1Core::GetInstance()->CreateRenderTarget(m_rt, &m_brt);
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"��������", 15.0f);
	SetBrush(D2D1::ColorF::Black);
	SetBrush(D2D1::ColorF(D2D1::ColorF::Red, 0.6f), &m_brush1);
	SetBrush(D2D1::ColorF::CadetBlue, &m_brush2);

	ShowWindow(m_hwnd, _ncmdShow);
	UpdateWindow(m_hwnd);
}

LRESULT GameWnd::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GameWnd* pWnd = nullptr;
	if (message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)lParam;
		SetLastError(0);
		pWnd = reinterpret_cast<GameWnd*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd)))
		{
			if (GetLastError() != 0) return E_FAIL;
		}
	}
	else
	{
		pWnd = reinterpret_cast<GameWnd*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (message == WM_GETMINMAXINFO && pWnd == nullptr)
		return S_OK;

	return pWnd->Dispatch(hWnd, message, wParam, lParam);
}

LRESULT GameWnd::Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_KEYUP:
		SceenManager::GetInstance()->KeyUpBind(wParam);
		break;

	case WM_KEYDOWN:
			SceenManager::GetInstance()->KeyDownBind(wParam);
		break;

	case WM_TIMER:
		break;

	case WM_SIZE:
		break;

	case WM_COMMAND:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_VSCROLL:
		break;

	case WM_PAINT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

void GameWnd::RenderProcess(ID2D1Bitmap* _bitmap)
{
	m_rt->BeginDraw();

	if (_bitmap)
		m_rt->DrawBitmap(_bitmap);

	m_rt->EndDraw();
}

void GameWnd::SetBrush(D2D1::ColorF _color)
{
	m_rt->CreateSolidColorBrush(
		_color,
		&m_brush
	);
}

void GameWnd::SetBrush(D2D1::ColorF _color, ID2D1SolidColorBrush** _brsuh)
{
	m_rt->CreateSolidColorBrush(
		_color,
		_brsuh
	);
}
