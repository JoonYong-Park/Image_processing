#include <stdio.h>
#include <windows.h>

// Otsu 알고리즘의 주요 아이디어는 이미지의 히스토그램을 분석하여 
// 최적의 임계값을 찾는 것입니다. 

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문
#define W 256  //영상의 크기를 정의합니다.
#define H 256

// 클래스 내의 분산과 클래스 간의 분산을 저장하기 위한 구조체를 정의합니다.
struct VAR {
	float black;    //흑색 영역에 대한 분산
	float white;    //백색 영역에 대한 분산
	float vbetween; // 클래스 간의 분산
};

// 히스토그램 생성, 정규화
void hist(unsigned char f[W * H], float hist_E[256]){ // f: 입력 영상, hist_E: 출력 히스토그램
	// 영상 히스토그램 생성
	float hist[256] = {0.0};
	for (int i = 0; i < W * H; i++) {
		hist[f[i]]++;
	} 

	// 영상 히스토그램 정규화
	for (int i = 0; i < 256; i++) {
		hist_E[i] = (float)hist[i] / (W * H); // 출력 히스토그램을 저장하는 배열입니다.
	} 
}

// <클래스 내의 분산>
// T값을 기준으로 두개의 클래스(흑, 백)를 분할하고 
// 각 클래스의 분산을 계산하여 구조체 VAR에 저장
void Varwithin(int T, struct VAR* V, unsigned char* readbuf) {
	long int bc = 0, wc = 0;    // 흑색, 백색 클래스 픽셀수
	float bv  = 0.0, wv  = 0.0; // 흑색, 백색 클래스 픽셀 값의 합
	float bbv = 0.0, wwv = 0.0; // 흑색, 백색 클래스 내의 분산 
	
	for (int i = 0; i < W * H; i++) {  // 클래스의 픽셀 합과 분산을 계산합니다.
		if (readbuf[i] < T) {    // 백색
			bv += readbuf[i]; // 픽셀 합
			bc++;             // 픽셀 수
		}
		else {                   // 흑색
			wv += readbuf[i]; 
			wc++;
		}
	}
	// 클래스의 픽셀 값의 평균
	float ba = bv / (float)bc;  // 평균 = 합 / 수
	float wa = wv / (float)wc;

	// 분산 계산
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			bbv += readbuf[i] * (readbuf[i] - ba) * (readbuf[i] - ba);
		}
		else {
			wwv += readbuf[i] * (readbuf[i] - wa) * (readbuf[i] - wa);
		}
	}
	// 분산을 구조체 VAR에 저장
	V->black = bbv / bv;
	V->white = wwv / wv;
}


// <클래스 간의 분산>
// T를 기준으로 클래스 간의 분산을 계산
// 클래스 간의 차이를 분석하여 최적의 임계값을 찾는 데 사용
void Varwibetween(int T, struct VAR* V, unsigned char* readbuf) {
	float w0[256] = { 0.0 };  // T보다 작은 픽셀 값의 누적 빈도수
	float h [256] = { 0.0 };  // 픽셀 값을 히스토그램에 저장
	float m0[256] = { 0.0 };  // T보다 작은 픽셀 값의 평균
	float m1[256] = { 0.0 };  // T보다 큰 픽셀 값의 평균
	float m = 0.0;			  // 전체 픽셀 값의 평균을 저장


	hist(readbuf, h);  // 히스토그램 계산 함수
	
	// 전체 픽셀 값의 평균을 계산합니다.
	for (int i = 0; i < W * H; i++) {  
		m += readbuf[i];
	}
	m = m / (W * H);

	for (int i = 1; i < T; i++) {
		w0[i] = w0[i - 1] + h[i];
		m0[i] = (w0[i - 1] * m0[i - 1] + i * h[i]) / w0[i];
		m1[i] = (m - w0[i] * m0[i]) / (1 - w0[i]);
	}
	// 클래스 간의 분산을 계산
	V -> vbetween = w0[T - 1] * (1 - w0[T - 1]) * (m0[T - 1] - m1[T - 1]) * (m0[ T - 1 ] - m1[T - 1]);
	
	

}

int main(void) {

	FILE* fp; // 파일 포인터 선언

	unsigned char* readbuf = NULL;
	unsigned char* writebuf = NULL;
	readbuf = (unsigned char*)malloc(W * H);
	writebuf = (unsigned char*)malloc(W * H);
	struct VAR V = { 0,0 };

	// 영상 읽기
	fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit.raw" 파일을 읽기 모드로 열기
	fread(readbuf, 1, W * H, fp);
	fclose(fp); // 파일 닫기


	// 임계값 T 설정
	int T = 200;

	// 영상의 평균을 임계값으로 사용한다.
	/*float average = 0.0;    
	for (int i = 1; i < W * H; i++) {
		average += (float)readbuf[i];
	}
	T = (int)average / (W * H);*/

	/*printf("T가 120일때\n");
	Varwithin(T = 120, &V, readbuf);
	printf("@@black %f \n@@white %f \n", V.black, V.white);
	Varwibetween(T = 120, &V, readbuf);
	printf("@@between %f\n", V.vbetween);*/

	// 임계값을 구하기
	float min_withhin = 99999999999999.0;
	int min_withhin_t = 0;
	float max_between = 0;
	int max_between_t = 0;
	for (int i = 1; i < 257; i++) {
		Varwithin(T = i , &V, readbuf);
		printf("<%d> \nblack: %f white: %f \n",i, V.black, V.white);
		if (V.black + V.white < min_withhin) {
			min_withhin = V.black + V.white;
			min_withhin_t = T;
		}
		Varwibetween(T = i , &V, readbuf);
		printf("between: %f\n", V.vbetween);
		if (V.vbetween > max_between) {
			max_between = V.vbetween;
			max_between_t = T;
		}
	}
	// <결과>
	// min_withhin: -2147483648
	// min_withhin_t : 122
	// max_between : -1610612736
	// max_between_t : 256
	
	// T를 사용하여 영상이진화
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			writebuf[i] = 0;
		}
		else {
			writebuf[i] = 255;
		}
	} 

	// 분산값, T값 출력
	printf("\nmin_withhin(b+w): %f\n", min_withhin);
	printf("min_withhin_t: %d\n", min_withhin_t);
	printf("max_between: %f\n", max_between);
	printf("max_between_t: %d\n", max_between_t);

	// 영상 저장
	fp = fopen("LENA_256x256_8bit_t_Otsu_2.raw", "wb"); // "LENA_256x256_8bit_new.raw" 파일을 쓰기 모드로 열기
	fwrite(writebuf, 1, W * H, fp); // Writebuf 배열의 데이터를 파일에 쓰기
	
	// 파일 닫기
	fclose(fp); 

	free(readbuf);  // 동적 할당 해제
	free(writebuf); // 동적 할당 해제

	return 0; // 프로그램 종료
}