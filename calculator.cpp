#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_CREATE:
        {
            CreateWindow("STATIC", "Please input two numbers",
    		WS_VISIBLE | WS_CHILD,
    		20, 15, 210, 25,
    		hwnd, NULL, NULL, NULL);

			CreateWindow("EDIT", "",
    		WS_VISIBLE | WS_CHILD | WS_BORDER,
    		50, 45, 150, 25,
    		hwnd, (HMENU)ID_EDIT1, NULL, NULL);

			CreateWindow("EDIT", "",
    		WS_VISIBLE | WS_CHILD | WS_BORDER,
    		50, 80, 150, 25,
    		hwnd, (HMENU)ID_EDIT2, NULL, NULL);

			CreateWindow("BUTTON", "+",
    		WS_VISIBLE | WS_CHILD,
    		50,125, 35, 25,
    		hwnd, (HMENU)ID_ADD, NULL, NULL);

			CreateWindow("BUTTON", "-",
   			WS_VISIBLE | WS_CHILD,
    		90, 125, 35, 25,
    		hwnd, (HMENU)ID_SUB, NULL, NULL);

			CreateWindow("BUTTON", "*",
    		WS_VISIBLE | WS_CHILD,
    		130, 125, 35, 25,
    		hwnd, (HMENU)ID_MUL, NULL, NULL);

			CreateWindow("BUTTON", "/",
    		WS_VISIBLE | WS_CHILD,
    		170, 125, 35, 25,
    		hwnd, (HMENU)ID_DIV, NULL, NULL);
        }	
        break;

        case WM_COMMAND:
        {
            char buf1[50], buf2[50], resultStr[100];
            double a, b, result = 0;

            GetDlgItemText(hwnd, ID_EDIT1, buf1, 50);
            GetDlgItemText(hwnd, ID_EDIT2, buf2, 50);

            a = atof(buf1);
            b = atof(buf2);

            switch (LOWORD(wParam))
            {
                case ID_ADD: result = a + b; break;
                case ID_SUB: result = a - b; break;
                case ID_MUL: result = a * b; break;
                case ID_DIV: result = (b != 0) ? a / b : 0; break;
                default: return 0;
            }

            sprintf(resultStr, "%f", result);
            MessageBox(hwnd, resultStr, "Result", MB_OK);
        }
        break;

        /* Upon destruction, tell the main thread to stop */
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        /* Default message handler */
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc  = WndProc;
    wc.hInstance    = hInstance;
    wc.hCursor      = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(200, 0, 100));
    wc.lpszClassName = "WindowClass";
    wc.hIcon        = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm      = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!",
                   "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        "WindowClass",
        "My Calculator",
        WS_VISIBLE | WS_CAPTION | WS_SYSMENU, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        250, 200,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!",
                   "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}