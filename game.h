extern boolean game_status_start;
extern boolean game_status_active;
extern boolean game_status_end;
extern boolean server_status_connet;

extern HANDLE hThread_s; // 서버 담당 스레드
extern unsigned threadID_s;
extern HANDLE hThread_m; // 게임 담당 스레드
extern unsigned threadID_m;
extern int num;

//----------------------------------------------------

struct ClientInfo {
	char host_name[15]; // 플레이어의 IP 정보
	int host_num; // 플레이어의 서버상 순서값(1, 2)

	COORD pos; // 내 캐릭터의 현재 위치
	int cnt_apple; // 내 캐릭터가 입수한 공통자원(apple=@) 수
	char input[2]; // 입력받은 키 (다음 위치를 계산하기 위한 입력값)
	boolean collide_wall; // 벽과 충돌했는지
};

struct ServerInfo {
	COORD pos; // 상대방 캐릭터의 위치
	int cnt_apple; // 상대방 캐릭터가 입수한 공통자원 수
	
	COORD pos_apple; // 공통자원의 위치
};

//----------------------------------------------------

//콘솔 창 이름 / 화면 크기 설정(150x40)
void SetConsoleView();

void GotoXY(int x, int y);

//화면 잠시 멈추기
void PauseConsoleView();

//화면 초기화(지우기)
void ClearConsoleView();

//시작 대기 화면
void DrawMainWindow();

//서버 접속 대기 화면
void DrawReadyWindow();

//게임 화면
int DrawGameWindow();

void DrawGameLogic();

void RecvMyInfo();

//게임 종료
void ExitGame();

//----------------------------------------------------

// 서버 연결 생성
int Connect();