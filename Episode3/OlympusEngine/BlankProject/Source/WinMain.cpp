#include "pch.h"

//
//global variables
//
#pragma region GlobalVariables

WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];

INT		WindowWidth;
INT		WindowHeight;

HICON	hIcon;

#pragma endregion 


//
//Pre-Declarations
//
#pragma region Pre-Declarations

VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID MessageLoop();

#pragma endregion


//function for window
//must return LRESULT
//uses CALLBACK macro
//four parameters important fore every windows process
//HWND = copy of windows hangle, instance of window that is running
//UINT message = message type parameter (ex: windows close, or windows resize)
//WPARAM wparam, LPARAM lparam = arguments for how message is received
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {
	
	switch (message){
		case WM_DESTROY: //once destroy message received, PostQuitMessage simply states please close the program
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}


//
//Operations
//

#pragma region Operations



//entry point
//input 1 HINSTANCE = representation of entire program that is running
//HINSTANCE HPrevInstance= doesn't operate correctly on win 10 or 11, legacy stuff - removed
//lpCmdLine = ability to put commands in at runtime
//nCmdShow = command on whether to show window at beginning
//removed variable names, will reference manually below
int CALLBACK WinMain(HINSTANCE, HINSTANCE , LPSTR , INT) {
	/*
		three steps to show window on screen:
		1 create window class
		2 create and display the window
		3 listen for message events <- can change features of window
	*/

	//initialize global variables
	InitializeVariables();
	
	//
	//1 create window class
	//
	CreateWindowClass();

	//
	//2 create and display window
	//
	InitializeWindow();

	//
	//3 message listener/listen for message events
	//
	MessageLoop();

	return 0;
}

//
//functions
//
#pragma region Functions

VOID InitializeVariables() {

	LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

	WindowWidth = 1366;
	WindowHeight = 768;
	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
}

VOID CreateWindowClass() {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;
	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;
	wcex.hInstance = HInstance();
	wcex.lpfnWndProc = WindowProcess;
	RegisterClassEx(&wcex);
}

VOID InitializeWindow() {
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

	//check if window was successfully created, if not shut down program
	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window!.", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(hWnd, SW_SHOW);
}

VOID MessageLoop() {
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
}

#pragma endregion