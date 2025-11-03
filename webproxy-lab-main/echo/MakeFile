# Echo 서버 Makefile

CC = gcc
CFLAGS = -Wall -g

# 타겟 파일
SERVER = server
CLIENT = client
OBJS = csapp.o

# 기본 빌드: 서버와 클라이언트
all: $(SERVER) $(CLIENT)

# 서버 빌드
$(SERVER): server.c $(OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) server.c csapp.c

# 클라이언트 빌드
$(CLIENT): client.c $(OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) client.c csapp.c

# 객체 파일 생성 (csapp.o 필요 시)
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

# clean: 빌드 결과 삭제
clean:
	rm -f $(SERVER) $(CLIENT) *.o
