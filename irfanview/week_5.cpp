#include <stdio.h>
#include <windows.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

#define W 256
#define H 256

int main_5() {
	/////// 이진 영상 만들기 ///////

	FILE* fp; // 파일 포인터 선언

	unsigned char* readbuf = NULL; 
	unsigned char* writebuf = NULL;
	readbuf = (unsigned char*)malloc(W * H);  // 영상 읽을 배열 선언
	writebuf = (unsigned char*)malloc(W * H); // 영상 쓸 배열 선언

	// 영상 읽기
	fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit.raw" 파일을 읽기 모드로 열기
	fread(readbuf, 1, W * H, fp);
	fclose(fp); // 파일 닫기

	// 임계값 설정 : 각 픽셀의 밝기 값이 그 임계값보다 크면 1(또는 흰색), 작으면 0(또는 검은색)으로 변환
	int T = 200;

	// 영상이진화 : 0과 1 또는 검은색과 흰색으로 나누는 과정
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			writebuf[i] = 0;
		}
		else {
			writebuf[i] = 255;
		}
	} 

	// 영상 저장
	fp = fopen("LENA_256x256_8bit_t_200.raw", "wb"); // "LENA_256x256_8bit_new.raw" 파일을 쓰기 모드로 열기
	fwrite(writebuf, 1, W*H, fp); // Writebuf 배열의 데이터를 파일에 쓰기
	
	// 파일 닫기
	fclose(fp); 

	free(readbuf);  // 동적 할당 해제
	free(writebuf); // 동적 할당 해제

	return 0; // 프로그램 종료
}
