#define Window_width 150
#define Window_height 40
#define Map_width
#define Map_height

#define ERROR_CON 404

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
void DrawGameWindow();

//----------------------------------------------------

// 서버 연결 생성
int Connect();