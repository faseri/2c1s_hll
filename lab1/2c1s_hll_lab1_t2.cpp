#include <windows.h>
#include <gdiplus.h>

#include <cstdlib>
#include <iostream>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw(HDC hdc,BYTE,BYTE,BYTE);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {
	// Initialize GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	// Register the window class
	const char *CLASS_NAME = "winapistudyclass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	// Create the window
	CreateWindow(CLASS_NAME, "2c1s_hlp_lab1_2",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,            // Window style
		CW_USEDEFAULT, CW_USEDEFAULT,                // Window initial position
		800, 600,                                    // Window size
		nullptr, nullptr, nullptr, nullptr);

	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
	BYTE red=255,green=0,blue=255;
	bool why=false;
LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	HDC hdc;
	switch (msg) {
	case WM_LBUTTONDOWN:
		if(why){
			red = 0; green = 255; blue = 0;
		} else {
			red = 255; green = 0; blue = 255;
		}
		why=!why;

		break;
	case WM_PAINT:
		hdc = GetDC(hwnd);
		draw(hdc,red,green,blue);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
	return 0;
}

void draw(HDC hdc,BYTE r, BYTE g, BYTE b) {
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, r, g, b));               // For lines, rectangles and curves
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, r, g, b));      // For filled shapes
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 24.0f, 1, Gdiplus::UnitPixel);
	Gdiplus::PointF pointF(30.0f, 30.0f);

	gf.DrawString(L"Кривых А.С. И595 12", -1, &font, pointF, &brush);
	pointF.X = 50.0f;
	pointF.Y = 50.0f;
	DWORD dwMajorVersion = 0;
	DWORD dwMinorVersion = 0;

	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(GetVersion())));
	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(GetVersion())));
	WCHAR szBuff[30];
	wsprintfW(szBuff, L"WinApi version: %d.%d\0",dwMajorVersion,dwMinorVersion);

	Gdiplus::LinearGradientBrush linGrBrush(
			Gdiplus::Point(0, 10),
			Gdiplus::Point(200, 10),
			Gdiplus::Color(255, r, b, g),
			Gdiplus::Color(255, g, b, r));

	gf.DrawString(szBuff,-1,&font,pointF,&brush);
	gf.FillRectangle(&linGrBrush, 333, 222, 300, 150);
	gf.DrawRectangle(&pen, 666, 333, 100, 150);
	gf.FillEllipse(&brush, 222, 400, 250, 100);
}
