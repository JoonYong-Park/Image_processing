#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main_62() {
    ////////// 감마수정 //////////

    FILE* fp;                         // 파일 포인터 선언

    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    unsigned char Writebuf[256][256]; // 영상   쓸 배열 선언
    double Histogram[256] = { 0 };    // 히스토그램 배열 선언
    double cnt[256] = { 0 };          // 이미지 픽셀 개수를 세기 위한 변수입니다.

    // 영상 읽기
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }
    fclose(fp);

    // 감마수정
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // 감마값을 1.5로 설정합니다.
            Writebuf[i][j] = (unsigned char)(255 * (pow((double)Readbuf[i][j]/255, 5.1)));

            // 픽셀의 값을 제한합니다.
            if (Writebuf[i][j] > 255) {
                Writebuf[i][j] = 255;
                printf("밝은색");
            }
            else if (Writebuf[i][j] < 0) {
                Writebuf[i][j] = 0;
                printf("어두운색");
            }
        }
    }

    // 합성곱
    /*for (int i = 1; i < 255; i++) {
    		for (int j = 1; j < 255; j++) {
            			Writebuf[i][j] = (Readbuf[i - 1][j - 1] + Readbuf[i - 1][j] + Readbuf[i - 1][j + 1] + Readbuf[i][j - 1] + Readbuf[i][j] + Readbuf[i][j + 1] + Readbuf[i + 1][j - 1] + Readbuf[i + 1][j] + Readbuf[i + 1][j + 1]) / 9;
                        		}
    }*/

    // 영상 저장
    fp = fopen("AVE256_Gamma.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}