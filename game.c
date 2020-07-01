#include <Windows.h>
#include "game.h"

boolean game_status_start = FALSE;
boolean game_status_active = FALSE;
boolean game_status_end = FALSE;
boolean server_status_connet = FALSE;

struct ClientInfo m_info;
struct ServerInfo s_info;

HANDLE hThread_s; // 서버 담당 스레드
unsigned threadID_s;
int num = 0;
HANDLE hThread_m; // 게임 담당 스레드
unsigned threadID_m;

int main(){
    int cursor;

    SetConsoleView();

	while (TRUE) {
		ClearConsoleView();
		DrawMainWindow();

		cursor = getch();
		if (cursor) {
			ClearConsoleView();

			//x 키를 입력할 경우 (대소문자관계X)
			if (cursor == 88 || cursor == 120) {
				game_status_end = TRUE;
				printf("Exit 1");
				Sleep(1000);
				return 0;
			}
			else {
				//스레드1:서버담당
				hThread_s = (HANDLE)_beginthreadex(NULL, 0, DrawReadyWindow,
													(void*)&num, 0, &threadID_s);
				if (hThread_s == 0) {
					printf("Error:Back to Main\n");
					Sleep(2000);
					continue;
				} // 스레드 생성이 안 되면 다시 처음부터

				else {
					while (TRUE) {
						if ((server_status_connet) && (game_status_start)) {
							hThread_m = (HANDLE)_beginthreadex(NULL, 0, 
									DrawGameWindow, (void*)&num, 0, &threadID_m);
							game_status_start = FALSE;

						}

						if (game_status_active) {
							//게임 돌아가는 중...
						}

						if (game_status_end) {
							CloseHandle(hThread_s);
							CloseHandle(hThread_m);
							return 0;
						}
					}
					
				}

			}
			
			
		}
	}//end:while()

}