#include <stdio.h>
#pragma warning(disable:4996)// 경고 메시지 4996을 무시하는 pragma 지시문

int main_3(void) {
    ////////// 1. 히스토그램 정규화 //////////

    FILE* fp;  // 파일 포인터 선언

    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    double Histogram[256] = { 0 };    // 히스토그램 배열 선언
    double cnt = 0;                   // 누적합

    // 영상 읽기
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);  // (저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }
    fclose(fp);


    // 히스토그램 작성
    for (int j = 0; j < 256; j++) {
        for (int i = 0; i < 256; i++) {
            Histogram[Readbuf[j][i]]++; 
        }
    }

    // 히스토그램 정규화 (히스토그램 값 총합 = 1) - 정규화 안하면 누적합은 256*256값이 나옴
    for (int i = 0; i < 256; i++) {
        Histogram[i] = Histogram[i] / (256 * 256);
    }

    // 히스토그램 출력
    for (int i = 0; i < 256; i++)
        printf("%3d: %3f\n", i, Histogram[i]); // 히스토그램 출력

    // 히스토그램의 합
    for (int i = 0; i < 256; i++) {
        cnt += Histogram[i];
    }
    // 누적합 출력
    printf("총합: %f\n", cnt);
    return 0;
}