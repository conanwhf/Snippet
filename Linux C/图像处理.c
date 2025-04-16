/* 腐蚀 Erosion*/
static int erosion(Mat &src, Mat &dst, int type, int size)
{
    Mat ele = getStructuringElement(type, Size(2 * size + 1, 2 * size + 1), Point(size, size));
    erode(src, dst, ele);
    return 0;
}

/* 膨胀 dilation*/
static int dilation(Mat &src, Mat &dst, int type, int size)
{
    Mat ele = getStructuringElement(type, Size(2 * size + 1, 2 * size + 1), Point(size, size));
    dilate(src, dst, ele);
    return 0;
}

/* 图像二值化 binary*/
static int binary(Mat &src, Mat &dst, int blockSize, int constValue)
{
    /* 普通阈值化
    double normal_threshold = 150;
    threshold(src, dst, normal_threshold, PIXEL_MAX_VAL , CV_THRESH_BINARY);
    */

    /* 调用OTSU算法的参数设置阈值化
    threshold(src, dst, 0, PIXEL_MAX_VAL, CV_THRESH_OTSU);
    */

    /* 自适应局部邻域块的均值方法
    adaptiveThreshold(src, dst, PIXEL_MAX_VAL, CV_ADAPTIVE_THRESH_MEAN_C, \
        CV_THRESH_BINARY, blockSize, constValue);
    */

    /* 自适应局部邻域块的高斯加权和方法 */
    adaptiveThreshold(src, dst, PIXEL_MAX_VAL, CV_ADAPTIVE_THRESH_GAUSSIAN_C,
                      CV_THRESH_BINARY, blockSize, constValue);

    return 0;
}

/* 滤波 filter */
static int filter(Mat &src, Mat &dst, int kernel_win_size)
{
    int i;
    /* Homogeneous blur 归一化滤波器
        for (i=1; i<kernel_win_size; i+=2) {
        blur(src, dst, Size(i, i), Point(-1,-1));
    }*/

    /* Guassian blur 高斯滤波器, 后两个参数为x方向和y方向的δ
    for (i=1; i<kernel_win_size; i+=2) {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
    }*/

    /* Median blur 中值滤波器, 滤波器的窗口为正方形*/
    for (i = 1; i < kernel_win_size; i += 2)
    {
        medianBlur(src, dst, i);
    }

    /* Bilatrial blur 双边滤波器
    for (i=1; i<kernel_win_size; i+=2) {
        bilateralFilter(src, dst, i, i*2, i/2);
    }*/
    return 0;
}

/* 轮廓/边缘检测 line*/
static int line(Mat &src, Mat &dst, int arg1, int arg2)
{
    /*
    int a,b,c;
    char buf[100];
    int f=open("config.txt", O_RDONLY);
    read(f, buf, 100);
    close(f);
    sscanf(buf, "%d %d %d", &a, &b, &c);
    dbg("buf=%s, a=%d, b=%d, c=%d\n", buf, a, b, c);
    */
    Canny(src, dst, arg1, arg2, LINE_SOBEL_SIZE);
    return 0;
}

/* 旋转 rotate*/
static int rotate(Mat &src, Mat &dst, int angle)
{
    switch (angle)
    {
    case 90:
        transpose(src, dst);
        flip(dst, dst, 1); // flip by y axis
        break;
    case 180:
        flip(src, dst, -1); // flip by both axises
        break;
    case 270:
        transpose(src, dst);
        flip(dst, dst, 0); // flip by x axis
        break;
    default:
        break;
    }
    return 0;
}