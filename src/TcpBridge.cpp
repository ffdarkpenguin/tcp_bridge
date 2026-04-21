#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

static SOCKET sock = INVALID_SOCKET;

extern "C" __declspec(dllexport)
int tcp_connect(const char* ip, int port)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) return -1;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
        return -2;

    return 0;
}

extern "C" __declspec(dllexport)
int tcp_send(unsigned char* data, int len)
{
    return send(sock, (const char*)data, len, 0);
}

extern "C" __declspec(dllexport)
void tcp_close()
{
    closesocket(sock);
    WSACleanup();
}
