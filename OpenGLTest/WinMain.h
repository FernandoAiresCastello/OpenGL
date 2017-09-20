#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define WINDOW_W	640
#define WINDOW_H	480
#define WINDOW_X	400
#define WINDOW_Y	200

HDC HdcMainWindow = NULL;

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void InitGl();
void RenderGl();
