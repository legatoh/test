#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>

#define Window_width 150
#define Window_height 40
#define Map_width
#define Map_height

//콘솔 창 이름 / 화면 크기 설정(150x40)
void SetConsoleView(){
    system("title Block Battle Game by DB");
    system("mode con: cols=150 lines=40");
}

void GotoXY(int x, int y){
    COORD pos;
    pos.X = 2 * x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
    GotoXY(Window_width / 2, 5);
    printf("Start : Any Key Press");
    GotoXY(Window_width / 2, 6);
    printf("Exit : x");

}

//서버 접속 대기 화면
void DrawReadyWindow(){

}

//게임 화면
void DrawGameWindow(){

}