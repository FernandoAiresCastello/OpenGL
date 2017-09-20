#include "WinMain.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcBasic = { 0 };
	wcBasic.lpszClassName = TEXT("wcMainWindow");
	wcBasic.cbSize = sizeof(WNDCLASSEX);
	wcBasic.hInstance = hInstance;
	wcBasic.hIcon = NULL;
	wcBasic.hIconSm = NULL;
	wcBasic.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcBasic.lpszMenuName = NULL;
	wcBasic.cbClsExtra = 0;
	wcBasic.cbWndExtra = 0;
	wcBasic.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcBasic.lpfnWndProc = MainWindowProc;
	wcBasic.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	RegisterClassEx(&wcBasic);

	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;

	HWND hMainWin = CreateWindowEx(dwExStyle, TEXT("wcMainWindow"), TEXT(""),
		dwStyle, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, NULL, NULL, hInstance, NULL);

	ShowWindow(hMainWin, TRUE);
	UpdateWindow(hMainWin);

	HdcMainWindow = GetDC(hMainWin);
	
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
		1,                     // version number  
		PFD_DRAW_TO_WINDOW |   // support window  
		PFD_SUPPORT_OPENGL |   // support OpenGL  
		PFD_DOUBLEBUFFER,      // double buffered  
		PFD_TYPE_RGBA,         // RGBA type  
		24,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		0,                     // no alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		32,                    // 32-bit z-buffer  
		0,                     // no stencil buffer  
		0,                     // no auxiliary buffer  
		PFD_MAIN_PLANE,        // main layer  
		0,                     // reserved  
		0, 0, 0                // layer masks ignored  
	};

	int pf = ChoosePixelFormat(HdcMainWindow, &pfd);
	BOOL ok = SetPixelFormat(HdcMainWindow, pf, &pfd);
	HGLRC gl = wglCreateContext(HdcMainWindow);
	DWORD error = GetLastError();
	wglMakeCurrent(HdcMainWindow, gl);

	InitGl();
	RenderGl();

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseDC(hMainWin, HdcMainWindow);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(gl);

	return msg.wParam;
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_SIZE:
		case WM_SIZING:
		{
			RenderGl();
			break;
		}
		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	return 0;
}

void InitGl()
{
}

void RenderGl()
{
	glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
		glColor3i(1, 0, 0);
		glVertex2i(0, 0);
		glVertex2i(0, 1);
		glVertex2i(1, 1);
		//glVertex2i(1, 0);
	glEnd();

	glFlush();
	wglSwapLayerBuffers(HdcMainWindow, WGL_SWAP_MAIN_PLANE);
}
