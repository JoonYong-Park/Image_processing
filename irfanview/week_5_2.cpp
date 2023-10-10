#include <stdio.h>
#include <windows.h>

// Otsu �˰����� �ֿ� ���̵��� �̹����� ������׷��� �м��Ͽ� 
// ������ �Ӱ谪�� ã�� ���Դϴ�. 

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�
#define W 256  //������ ũ�⸦ �����մϴ�.
#define H 256

// Ŭ���� ���� �л�� Ŭ���� ���� �л��� �����ϱ� ���� ����ü�� �����մϴ�.
struct VAR {
	float black;    //��� ������ ���� �л�
	float white;    //��� ������ ���� �л�
	float vbetween; // Ŭ���� ���� �л�
};

// ������׷� ����, ����ȭ
void hist(unsigned char f[W * H], float hist_E[256]){ // f: �Է� ����, hist_E: ��� ������׷�
	// ���� ������׷� ����
	float hist[256] = {0.0};
	for (int i = 0; i < W * H; i++) {
		hist[f[i]]++;
	} 

	// ���� ������׷� ����ȭ
	for (int i = 0; i < 256; i++) {
		hist_E[i] = (float)hist[i] / (W * H); // ��� ������׷��� �����ϴ� �迭�Դϴ�.
	} 
}

// <Ŭ���� ���� �л�>
// T���� �������� �ΰ��� Ŭ����(��, ��)�� �����ϰ� 
// �� Ŭ������ �л��� ����Ͽ� ����ü VAR�� ����
void Varwithin(int T, struct VAR* V, unsigned char* readbuf) {
	long int bc = 0, wc = 0;    // ���, ��� Ŭ���� �ȼ���
	float bv  = 0.0, wv  = 0.0; // ���, ��� Ŭ���� �ȼ� ���� ��
	float bbv = 0.0, wwv = 0.0; // ���, ��� Ŭ���� ���� �л� 
	
	for (int i = 0; i < W * H; i++) {  // Ŭ������ �ȼ� �հ� �л��� ����մϴ�.
		if (readbuf[i] < T) {    // ���
			bv += readbuf[i]; // �ȼ� ��
			bc++;             // �ȼ� ��
		}
		else {                   // ���
			wv += readbuf[i]; 
			wc++;
		}
	}
	// Ŭ������ �ȼ� ���� ���
	float ba = bv / (float)bc;  // ��� = �� / ��
	float wa = wv / (float)wc;

	// �л� ���
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			bbv += readbuf[i] * (readbuf[i] - ba) * (readbuf[i] - ba);
		}
		else {
			wwv += readbuf[i] * (readbuf[i] - wa) * (readbuf[i] - wa);
		}
	}
	// �л��� ����ü VAR�� ����
	V->black = bbv / bv;
	V->white = wwv / wv;
}


// <Ŭ���� ���� �л�>
// T�� �������� Ŭ���� ���� �л��� ���
// Ŭ���� ���� ���̸� �м��Ͽ� ������ �Ӱ谪�� ã�� �� ���
void Varwibetween(int T, struct VAR* V, unsigned char* readbuf) {
	float w0[256] = { 0.0 };  // T���� ���� �ȼ� ���� ���� �󵵼�
	float h [256] = { 0.0 };  // �ȼ� ���� ������׷��� ����
	float m0[256] = { 0.0 };  // T���� ���� �ȼ� ���� ���
	float m1[256] = { 0.0 };  // T���� ū �ȼ� ���� ���
	float m = 0.0;			  // ��ü �ȼ� ���� ����� ����


	hist(readbuf, h);  // ������׷� ��� �Լ�
	
	// ��ü �ȼ� ���� ����� ����մϴ�.
	for (int i = 0; i < W * H; i++) {  
		m += readbuf[i];
	}
	m = m / (W * H);

	for (int i = 1; i < T; i++) {
		w0[i] = w0[i - 1] + h[i];
		m0[i] = (w0[i - 1] * m0[i - 1] + i * h[i]) / w0[i];
		m1[i] = (m - w0[i] * m0[i]) / (1 - w0[i]);
	}
	// Ŭ���� ���� �л��� ���
	V -> vbetween = w0[T - 1] * (1 - w0[T - 1]) * (m0[T - 1] - m1[T - 1]) * (m0[ T - 1 ] - m1[T - 1]);
	
	

}

int main(void) {

	FILE* fp; // ���� ������ ����

	unsigned char* readbuf = NULL;
	unsigned char* writebuf = NULL;
	readbuf = (unsigned char*)malloc(W * H);
	writebuf = (unsigned char*)malloc(W * H);
	struct VAR V = { 0,0 };

	// ���� �б�
	fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit.raw" ������ �б� ���� ����
	fread(readbuf, 1, W * H, fp);
	fclose(fp); // ���� �ݱ�


	// �Ӱ谪 T ����
	int T = 200;

	// ������ ����� �Ӱ谪���� ����Ѵ�.
	/*float average = 0.0;    
	for (int i = 1; i < W * H; i++) {
		average += (float)readbuf[i];
	}
	T = (int)average / (W * H);*/

	/*printf("T�� 120�϶�\n");
	Varwithin(T = 120, &V, readbuf);
	printf("@@black %f \n@@white %f \n", V.black, V.white);
	Varwibetween(T = 120, &V, readbuf);
	printf("@@between %f\n", V.vbetween);*/

	// �Ӱ谪�� ���ϱ�
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
	// <���>
	// min_withhin: -2147483648
	// min_withhin_t : 122
	// max_between : -1610612736
	// max_between_t : 256
	
	// T�� ����Ͽ� ��������ȭ
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			writebuf[i] = 0;
		}
		else {
			writebuf[i] = 255;
		}
	} 

	// �л갪, T�� ���
	printf("\nmin_withhin(b+w): %f\n", min_withhin);
	printf("min_withhin_t: %d\n", min_withhin_t);
	printf("max_between: %f\n", max_between);
	printf("max_between_t: %d\n", max_between_t);

	// ���� ����
	fp = fopen("LENA_256x256_8bit_t_Otsu_2.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	fwrite(writebuf, 1, W * H, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
	
	// ���� �ݱ�
	fclose(fp); 

	free(readbuf);  // ���� �Ҵ� ����
	free(writebuf); // ���� �Ҵ� ����

	return 0; // ���α׷� ����
}