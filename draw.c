#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>
#include <stddef.h>
#include <process.h>
#include "game.h"

#define Window_width 100
#define Window_height 40
#define Map_width
#define Map_height

#define ERROR_CON 404
#define SIZE_BACKLOG 2048

void SetConsoleView(){
	system("title Block Battle Game by DB");
	system("mode con: cols=100 lines=40");
}

void GotoXY(int x, int y){
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
} 

void hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//화면 잠시 멈추기
void PauseConsoleView(){
    system("pause");
}

//화면 초기화(지우기)
void ClearConsoleView(){
    system("CLS");
}

//시작 대기 화면
void DrawMainWindow(){
	for (int i = 0; i < Window_width; i++) {
		printf("=");
	}
    
	GotoXY(35, 20);
	printf("[Start] Any Key Press\n");
	GotoXY(35, 26);
	printf("[Exit] 'X' Button\n");

	GotoXY(0, 39);
	for (int i = 0; i < Window_width; i++) {
		printf("=");
	}
}

//서버 접속 대기 화면
void DrawReadyWindow(){
	HANDLE hThread;
	unsigned threadID;
	LPDWORD tCode;
	int num = 0;

	while (TRUE) {
		ClearConsoleView();
		GotoXY(20, 20);
		printf("Waiting Server...\n");

		//서버 접속 스레드
		hThread = (HANDLE)_beginthreadex(NULL, 0, Connect, (void*)&num, 0, &threadID);
		//WaitForSingleObject(hThread, INFINITE); //스레드가 종료되기 전까지 대기

		//스레드 생성에 실패했다면
		if (hThread == 0) {
			GotoXY(20, 20);
			printf("Failed create thread\n");
			GotoXY(20, 21);
			printf("Back to Main Page\n");
			Sleep(3000);
			DrawMainWindow();
			continue; //처음부터 다시
		}
		else {
			while (TRUE) {
				//스레드 상태 체크
				GetExitCodeThread(hThread, &tCode);
				//스레드가 종료되는 경우: 게임 끝
				if (!(tCode == STILL_ACTIVE)) {
					server_status_connet = FALSE; //연결이 종료되었음을 보내고
					CloseHandle(hThread); //핸들을 반환한 뒤
					return 0; //연결을 유지할 이유가 없기 때문에 함수(스레드)를 종료
				}
			}
		}
	}//end:while

}

//게임 화면 (틀)
int DrawGameWindow(){
	ClearConsoleView();
	COORD startP;
	startP.X = 9;
	startP.Y = 4;
	int width = 40;
	int height = 30;

	while (TRUE) {
		GotoXY(startP.X, startP.Y);
		for (int i = 0; i < width; i++) {
			printf("* ");
		}
		for (int i = 0; i < height; i++) {
			GotoXY(startP.X, startP.Y + i);
			printf("*");
			GotoXY(startP.X + (width * 2), startP.Y + i);
			printf("*");
		}
		GotoXY(startP.X, startP.Y + height);
		for (int i = 0; i < width; i++) {
			printf("* ");
		}
		printf("*");

		DrawGameLogic();

		if (game_status_end) {
			return 0;
		}
	}
}


void DrawGameLogic() {
	Sleep(3000);
	ExitGame();
}


void RecvMyInfo() {

}

// 게임 종료
void ExitGame() {
	game_status_active = FALSE;
	game_status_end = TRUE;

}