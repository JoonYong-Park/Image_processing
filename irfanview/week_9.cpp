#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main_9() {
    ////////// 모폴로지 //////////

    FILE* fp;                         // 파일 포인터 선언

    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    unsigned char Writebuf[256][256]; // 영상   쓸 배열 선언
    double Histogram[256] = { 0 };    // 히스토그램 배열 선언
    double cnt[256] = { 0 };          // 이미지 픽셀 개수를 세기 위한 변수입니다.

    // 영상 읽기
    fp = fopen("LENA_256x256_8bit_t_Otsu.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }
    fclose(fp);

    // 모노로지 팽창 알고리즘
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            if (Readbuf[i][j-1] == 255 || Readbuf[i][j] == 255 || Readbuf[i][j+1] == 255) {
				Writebuf[i][j] = 255;
			}
            else {
				Writebuf[i][j] = 0;
			}
		}
	}

    // 모노로지 침식 알고리즘
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            if (Readbuf[i][j - 1] == 255 && Readbuf[i][j] == 255 && Readbuf[i][j + 1] == 255) {
                Writebuf[i][j] = 255;
            }
            else {
                Writebuf[i][j] = 0;
            }
        }
    }

    // 형태학적 그라디언트
    for (int i = 1; i < 255; i++) {
    		for (int j = 1; j < 255; j++) {
            			Writebuf[i][j] = Readbuf[i][j] - Readbuf[i][j - 1];
      		}
    }

    








    // 영상 저장
    fp = fopen("LENA_256x256_8bit_t_Otsu_morphology.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}