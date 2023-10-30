#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main_7() {
    ////////// 중간값 필터 //////////

    FILE* fp;                         // 파일 포인터 선언

    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    unsigned char Writebuf[256][256]; // 영상   쓸 배열 선언
    double Histogram[256] = { 0 };    // 히스토그램 배열 선언
    double cnt[256] = { 0 };          // 이미지 픽셀 개수를 세기 위한 변수입니다.

    // 영상 읽기
    fp = fopen("노이즈-LENA_256x256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }
    fclose(fp);

    // 메디안 필터: 3x3
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
			unsigned char temp[9] = { 0 };
			temp[0] = Readbuf[i - 1][j - 1];
			temp[1] = Readbuf[i - 1][j];
			temp[2] = Readbuf[i - 1][j + 1];
			temp[3] = Readbuf[i][j - 1];
			temp[4] = Readbuf[i][j];
			temp[5] = Readbuf[i][j + 1];
			temp[6] = Readbuf[i + 1][j - 1];
			temp[7] = Readbuf[i + 1][j];
			temp[8] = Readbuf[i + 1][j + 1];

            for (int k = 0; k < 9; k++) {
                for (int l = 0; l < 9 - k - 1; l++) {
                    if (temp[l] > temp[l + 1]) {
						unsigned char tmp = temp[l];
						temp[l] = temp[l + 1];
						temp[l + 1] = tmp;
					}
				}
			}

			Writebuf[i][j] = temp[4];
		}
	}

    // 영상 저장
    fp = fopen("노이즈-LENA_256x256_new.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}