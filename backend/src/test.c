#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *quiz_question = "Câu 1: 2 + 2 = ?\nA. 3\nB. 4\nC. 5\n";
    // email:dinhvanluan2k3@gmail.com;password:luan2003
    // Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Đặt thuộc tính cho địa chỉ
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Gắn socket vào cổng
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Lắng nghe kết nối từ client
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Chấp nhận kết nối từ client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Gửi câu hỏi thi về cho client
    send(new_socket, quiz_question, strlen(quiz_question), 0);
    printf("Đã gửi câu hỏi thi cho client.\n");

    close(new_socket);
    close(server_fd);
    return 0;
}