#include <windows.h>

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];

INT		WindowWidth;
INT		WindowHeight;

//entry point
//input 1 HINSTANCE = representation of entire program that is running
//HINSTANCE HPrevInstance= doesn't operate correctly on win 10 or 11, legacy stuff - removed
//lpCmdLine = ability to put commands in at runtime
//nCmdShow = command on whether to show window at beginning
//removed variable names, will reference manually below
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	/*
		three steps to show window on screen:
		1 create window class
		2 create and display the window
		3 listen for message events <- can change features of window
	*/

	//initialize global variables
	wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
	wcscpy_s(WindowTitle, TEXT("Our First Window"));
	WindowWidth = 1366;
	WindowHeight = 768;
	
	//
	//1 create window class
	//
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); //size of our class 
	wcex.style = CS_HREDRAW | CS_VREDRAW; //style has horizontal and verticle redraw
	wcex.cbClsExtra = 0; //add extra memory at runtime
	wcex.cbWndExtra = 0; //add extra memory at runtime

	//cursor
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//background- default to white
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	//icon
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION); //IDI_APPLICATION is default for windows
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;

	//reference to instance of program running
	wcex.hInstance = HInstance();

	//instructions for how window will perform, resize, close, etc.
	
	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

	//
	//create and display window
	//
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	
	//check if window was successfully created, if not shut down program
	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window!.", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	//
	//message listener/listen for message events
	//
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}