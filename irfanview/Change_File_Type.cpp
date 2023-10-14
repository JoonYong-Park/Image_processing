//#include <stdio.h>
//#include <stdlib.h>
//#include <jpeglib.h>
// 
//int main() {
//    // raw 사진 파일 읽기
//    FILE* fp;
//    unsigned char Readbuf[256][256];
//
//    fp = fopen("image.raw", "rb");
//    if (fp == NULL) {
//        printf("파일을 열 수 없습니다.\n");
//        return -1;
//    }
//
//    fread(Readbuf, 1, 65536, fp);
//    fclose(fp);
//
//    // jpeg 이미지 파일 생성
//    struct jpeg_compress_struct cinfo;
//    struct jpeg_error_mgr jerr;
//
//    cinfo.err = jpeg_std_error(&jerr);
//    jpeg_create_compress(&cinfo);
//
//    FILE* outfp;
//    outfp = fopen("image.jpg", "wb");
//
//    jpeg_stdio_dest(&cinfo, outfp);
//
//    cinfo.image_width = 256;
//    cinfo.image_height = 256;
//    cinfo.input_components = 1;
//    cinfo.in_color_space = JCS_GRAYSCALE;
//
//    jpeg_set_defaults(&cinfo);
//    jpeg_start_compress(&cinfo, TRUE);
//
//    // raw 사진 파일의 데이터를 jpeg 이미지 파일에 저장
//    for (int i = 0; i < 256; i++) {
//        for (int j = 0; j < 256; j++) {
//            jpeg_write_scanline(&cinfo, Readbuf[i], j);
//        }
//    }
//
//    jpeg_finish_compress(&cinfo);
//
//    fclose(outfp);
//
//    return 0;
//}
