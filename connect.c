#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <errno.h>
#include "game.h"

#pragma comment(lib, "ws2_32.lib")

extern struct ClientInfo m_info;
extern struct ServerInfo s_info;

void error_handling(char* message);

int Connect(int argc, char* argv[]) {
	char sv_host[15] = "192.168.1.3";
	int port = 15518;

	HOSTENT *ptr;
	IN_ADDR addr;

	int    nRet;
	WSADATA wsaData;

	int sock;
	struct sockaddr_in serv_addr;
	char my_host[15] = { 0x00, };
	char *ipad = NULL;
	int player_num = 0;
	char message[256] = { 0x00, };
	char *pMsg = NULL;
	int i = 0;
	char *pMessage[5] = { NULL, };

	nRet = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (nRet != 0)
	{
		switch (nRet) {
		case WSASYSNOTREADY:
			printf("네트워크 접속을 준비 못함\n");
			break;
		case WSAVERNOTSUPPORTED:
			printf("요구한 윈속 버전이 서포트 안됨\n");
			break;
		case WSAEINPROGRESS:
			printf("블로킹 조작이 실행중\n");
			break;
		case WSAEPROCLIM:
			printf("최대 윈속 프로세스 처리수 초과\n");
			break;
		case WSAEFAULT:
			printf("두번째 인수의 포인터가 무효\n");
			break;
		}
	}

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
		error_handling("socket error\n");
		return 0;
    }
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_addr.s_addr = inet_addr(sv_host);
	//serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("connect error\n");
		return 0;
	}

	gethostname(my_host, sizeof(my_host));
	strcpy(m_info.host_name, my_host);
	ptr = gethostbyname(my_host);
	memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
	ipad = inet_ntoa(addr);

	if (send(sock, ipad, 14, 0) == -1) {
		error_handling("send error\n");
		return 0;
	}

	if (recv(sock, message, sizeof(message), 0) == -1) {
		if (errno == ECONNREFUSED) {
			fprintf(stderr, "recv Error: %s\n", strerror(errno));
		}
		else {
			fprintf(stderr, "recv Error: %s\n", strerror(errno));
		}
	}
	GotoXY(10, 0);
	//message case1:"1%WAITING" case2:"2%MATCHING"
	pMsg = strtok(message, "%");
	while (pMsg != NULL) {
		pMessage[i] = pMsg;
		i++;
		pMsg = strtok(NULL, "%");
	}

	//서버 연결 성공 이후 처리되는 구문들
	if (strcmp(pMessage[0], "first") == 0) {
		m_info.host_num = 1;
	}
	else if (strcmp(pMessage[0], "second") == 0) {
		m_info.host_num = 2;
	}
	server_status_connet = TRUE;
	
	strcpy(message, "");
	while (1) {
		if (m_info.host_num == 1) {
			recv(sock, message, sizeof(message), 0);
			printf("%s", message);
			if (strcmp(message, "MATCHING") == 0)
				break;
		}
		if (m_info.host_num == 2) {
			GotoXY(20, 20);
			printf("&&&&&&&&&");
			break;
		}
	}

	game_status_start = TRUE;
	game_status_active = TRUE;

	//변수 재활용을 위한 초기화
	strcpy(message, "");
	pMsg = NULL;
	while (i >= 0) {
		pMessage[i] = NULL;
		i--;
	}
	i = 0;

	while (game_status_active) {
		strcat(message, m_info.pos.X);
		strcat(message, "%");
		strcat(message, m_info.pos.Y);
		strcat(message, "%");
		strcat(message, m_info.cnt_apple);
		strcat(message, "%");
		strcat(message, m_info.input);
		strcat(message, "%");
		strcat(message, m_info.collide_wall);
		send(sock, message, sizeof(message), 0);

		recv(sock, message, sizeof(message), 0);
		pMsg = strtok(message, "%");
		while (pMsg != NULL) {
			pMessage[i] = pMsg;
			i++;
			pMsg = strtok(NULL, "%");
		}
		s_info.pos.X = (short)pMessage[0];
		s_info.pos.Y = (short)pMessage[1];
		s_info.cnt_apple = (int)pMessage[2];
		s_info.pos_apple.X = (short)pMessage[3];
		s_info.pos_apple.Y = (short)pMessage[4];
	}

	close(sock);
	return 0; //스레드 종료
}

void error_handling(char* message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	//exit(1);
}