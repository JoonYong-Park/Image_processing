#include <stdio.h>
#include <windows.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

#define W 256
#define H 256

int main_5() {
	/////// ���� ���� ����� ///////

	FILE* fp; // ���� ������ ����

	unsigned char* readbuf = NULL; 
	unsigned char* writebuf = NULL;
	readbuf = (unsigned char*)malloc(W * H);  // ���� ���� �迭 ����
	writebuf = (unsigned char*)malloc(W * H); // ���� �� �迭 ����

	// ���� �б�
	fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit.raw" ������ �б� ���� ����
	fread(readbuf, 1, W * H, fp);
	fclose(fp); // ���� �ݱ�

	// �Ӱ谪 ���� : �� �ȼ��� ��� ���� �� �Ӱ谪���� ũ�� 1(�Ǵ� ���), ������ 0(�Ǵ� ������)���� ��ȯ
	int T = 200;

	// ��������ȭ : 0�� 1 �Ǵ� �������� ������� ������ ����
	for (int i = 0; i < W * H; i++) {
		if (readbuf[i] < T) {
			writebuf[i] = 0;
		}
		else {
			writebuf[i] = 255;
		}
	} 

	// ���� ����
	fp = fopen("LENA_256x256_8bit_t_200.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	fwrite(writebuf, 1, W*H, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
	
	// ���� �ݱ�
	fclose(fp); 

	free(readbuf);  // ���� �Ҵ� ����
	free(writebuf); // ���� �Ҵ� ����

	return 0; // ���α׷� ����
}
