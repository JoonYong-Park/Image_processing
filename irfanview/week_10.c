#include <stdio.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main_10() {
    FILE* fp; // 파일 포인터 선언
    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    unsigned char Writebuf[256][256]; // 영상 쓸 배열 선언

    // 영상 읽기
    fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit_1.raw" 파일을 읽기 모드로 열기
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);

    // 영상 회전(전방 변환) 동차 행렬
    





    /*for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			int x = (int)(i * 0.8660254 + j * 0.5);
			int y = (int)(-i * 0.5 + j * 0.8660254);
			if (x >= 0 && x < 256 && y >= 0 && y < 256) {
				Writebuf[i][j] = Readbuf[x][y];
			}
			else {
				Writebuf[i][j] = 0;
			}
		}
	}*/
    // 영상의 중심을 기준으로 회전(전방계산) 동차 행렬 알고리즘
    //for (int i = 0; i < 256; i++) {
    //    for (int j = 0; j < 256; j++) {
    //        
    //        int x = (int)((i - 128) * 0.8660254 + (j - 128) * 0.5 + 128);  // 입력 영상의 픽셀의 새로운 x 좌표를 계산
    //        int y = (int)((-i + 128) * 0.5 + (j - 128) * 0.8660254 + 128); // 입력 영상의 픽셀의 새로운 y 좌표를 계산

    //        // 새로운 좌표가 영상의 범위 내에 있는지 확인합니다.
    //        if (x >= 0 && x < 256 && y >= 0 && y < 256) {
    //            // 새로운 좌표가 영상의 범위 내에 있으면, 읽기 버퍼의 픽셀 값을 쓰기 버퍼에 복사합니다.
    //            Writebuf[i][j] = Readbuf[x][y];
    //        }
    //        else {
    //            // 새로운 좌표가 영상의 범위 내에 없으면, 픽셀 값을 0으로 설정합니다.
    //            Writebuf[i][j] = 0;
    //        }
    //    }
    //}

    // 영상을 2배 확대(최근방 이웃 보간법) 동차 행렬
    /*for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int x = (int)(i * 0.5);
            int y = (int)(j * 0.5);
            if (x >= 0 && x < 256 && y >= 0 && y < 256) {
                 Writebuf[i][j] = Readbuf[x][y];
            }
            else {
                Writebuf[i][j] = 0;
            }
        }
    }*/

    // 영상을 2배 축소(burt필터) 동차행렬
    for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {

			int x = (int)(i * 2);
			int y = (int)(j * 2);
			if (x >= 0 && x < 256 && y >= 0 && y < 256) {
				Writebuf[i][j] = Readbuf[x][y];
			}
			else {
				Writebuf[i][j] = 0;
			}
		}
	}








    

    // 영상 저장
    fp = fopen("LENA_256x256_8bit_2_up_down3333333333333333.raw", "wb");
    for (int i = 0; i < 256; i++) {
        fwrite(Writebuf[i], 1, 256, fp);
    }
    fclose(fp);

    return 0;
}
