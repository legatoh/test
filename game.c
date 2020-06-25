#include "game.h"

int main(){
    int cursor;

    SetConsoleView();
    ClearConsoleView();
    DrawMainWindow();

    cursor = getch();
    if (cursor){
        ClearConsoleView();
        
        //x 키를 입력할 경우 (대소문자관계X)
        if (cursor == 88 || cursor == 120){
            printf("3초 후 프로그램을 종료합니다.");
            Sleep(3000);
            return 0;
        }

        DrawReadyWindow();

    }


}