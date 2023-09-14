#include <stdio.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main() {

	FILE* fp; // 파일 포인터 선언

	unsigned char Readbuf[256][256]; // 256x256 크기의 8비트 배열 선언
	unsigned char Writebuf[256][256]; // 256x256 크기의 8비트 배열 선언

	// 영상 읽기
	fp = fopen("LENA_256x256_8bit.raw", "rb"); // "LENA_256x256_8bit.raw" 파일을 읽기 모드로 열기
	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp); // 파일에서 데이터 읽어와 Readbuf 배열에 저장
	fclose(fp); // 파일 닫기

	// 영상 편집: 영상을 수직으로 뒤집기
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			Writebuf[j][i] = Readbuf[256 - j][256 - i]; // Readbuf의 값을 뒤집어 Writebuf에 저장

	// 영상 저장
	fp = fopen("LENA_256x256_8bit_up_down_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" 파일을 쓰기 모드로 열기
	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp); // Writebuf 배열의 데이터를 파일에 쓰기
	fclose(fp); // 파일 닫기

	return 0; // 프로그램 종료
}
