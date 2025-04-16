/*需要libjpeg,编译时-ljpeg，安装包libjpeg-dev*/
#include <jpeglib.h>
#define JPEG_QUALITY 100 // 图片质量

int savejpg(uint8_t *pdata, char *jpg_file, int width, int height)
{ // 分别为RGB数据,要保存的jpg文件名,图片长宽
    int depth = 3;
    JSAMPROW row_pointer[1]; // 指向一行图像数据的指针
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile;

    cinfo.err = jpeg_std_error(&jerr); // 要首先初始化错误信息
    //* Now we can initialize the JPEG compression object.
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(jpg_file, "wb")) == NULL)
    {
        printf("can not open %s\n", jpg_file);
        return -1;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width; //* image width and height, in pixels
    cinfo.image_height = height;
    cinfo.input_components = depth; //* # of color components per pixel
    cinfo.in_color_space = JCS_RGB; //* colorspace of input image
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, JPEG_QUALITY, TRUE); //* limit to baseline-JPEG values
    jpeg_start_compress(&cinfo, TRUE);

    int row_stride = width * depth;
    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = (JSAMPROW)(pdata + cinfo.next_scanline * row_stride); // 一行一行数据的传&#xff0c;jpeg为大端数据格式
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo); // 这几个函数都是固定流程
    fclose(outfile);

    return 0;
}
