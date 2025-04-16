/*
 * capturing from cam
 * iNova, conanwang, 08/2021
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <asm/types.h> /* for videodev2.h */
#include <linux/videodev2.h>
#include "inova_ai_cam.h"

#include <assert.h>
#include <getopt.h> /* getopt_long() */
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

// for Log
#if ERROR_INFO
#define err(fmt, args...) printf("[%s(%d)] err: " fmt, __FUNCTION__, __LINE__, ##args) /*debug function */
#else
#define err(fmt, args...)
#endif
#if DEBUG_INFO
#define dbg(fmt, args...) printf("[%s(%d)] dbg: " fmt, __FUNCTION__, __LINE__, ##args) /*debug function */
#else
#define dbg(fmt, args...)
#endif

#define DEV_NAME "/dev/video0"

#define FREE_LINE(fp) \
    while (fp)        \
    {                 \
        free(fp);     \
        fp = NULL;    \
    }
#define CLEAR(x) memset(&(x), 0, sizeof(x))

// dev info
static struct v4l2_capability cap;
static int devfd = -1;
static uint8_t *databuf = NULL;
static uint32_t buffer_size = 0;

/*
Do the ioctl to the cam device
*/
static int _ioctl(int request, void *arg)
{
    int ret;

    if (devfd < 0)
    {
        err("device node %s not init it!\n", DEV_NAME);
        return RET_CAM_NOT_INIT;
    }
    ret = ioctl(devfd, request, arg);
    if (ret < 0)
        dbg("ioctl error, the cmd=%d, return=%d\n", request, ret);
    return ret;
}

/*
 */
int init_cam(int width, int height, int format)
{
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    uint32_t min = 0;

    devfd = open(DEV_NAME, O_RDWR | O_NONBLOCK, 0);
    if (devfd < 0)
    {
        err("Open device node %s fail\n", DEV_NAME);
        return RET_CAM_OPEN_FAIL;
    }

    if (_ioctl(VIDIOC_QUERYCAP, &cap) < 0)
    {
        err("This device is not a v4l2 device\n");
        close(devfd);
        devfd = -1;
        return RET_CAM_NOT_SUPPORT;
    }
    else
    {
        // 打印摄像头驱动名字
        dbg("Device name: %s\n", cap.driver);
        dbg("cap.capabilities=0x%X\n", cap.capabilities);
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        err("This device can not support video capture!\n");
        close(devfd);
        devfd = -1;
        return RET_CAM_NOT_SUPPORT;
    }

    if (!(cap.capabilities & V4L2_CAP_READWRITE))
        dbg("This video device can not support the i/o mode!\n");

    /* Select video input, video standard and tune here. */
    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (_ioctl(VIDIOC_CROPCAP, &cropcap) == RET_CAM_SUCCESS)
    {
        /* reset to default */
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;
        if (_ioctl(VIDIOC_S_CROP, &crop) != RET_CAM_SUCCESS)
            dbg("crop set fail, maybe cropping not supported\n");
    }

    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    switch (format)
    {
    case IMG_FMT_YUV422:
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        break;
    case IMG_FMT_RGB565:
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB565;
        break;
    case IMG_FMT_RGB24:
    default:
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
        break;
    }
    dbg("You want set: size=%d*%d, format=%d\n", width, height, format);
    if (_ioctl(VIDIOC_S_FMT, &fmt) != RET_CAM_SUCCESS)
        dbg("Image format & size set error, may not support\n");
    dbg("Now the setting: size=%d*%d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);
    /*if (_ioctl(VIDIOC_TRY_FMT, &fmt) != RET_CAM_SUCCESS)
        dbg("try RGB fail\n");*/

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * ((format == IMG_FMT_RGB24) ? 3 : 2);
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    // Init the buffer
    buffer_size = min;
    databuf = malloc(buffer_size);
    if (!databuf)
    {
        err("Out of memory!\n");
        close(devfd);
        devfd = -1;
        return RET_CAM_MEMORY_ERR;
    }
    dbg("buf=%p, buffer size=%d\n", databuf, buffer_size);

    return RET_CAM_SUCCESS;
}

/*
 */
int release_cam(void)
{
    if (devfd < 0)
    {
        err("Not init it!\n");
        return RET_CAM_NOT_INIT;
    }

    close(devfd);
    dbg("release the deivce...done\n");

    free(databuf);
    databuf = NULL;

    return RET_CAM_SUCCESS;
}

#if 0
static int
read_frame(void)
{
    struct v4l2_buffer buf;
    unsigned int i;

    switch (io)
    {
    case IO_METHOD_READ:
        if (-1 == read(fd, buffers[0].start, buffers[0].length))
        {
            switch (errno)
            {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("read");
            }
        }

        process_image(buffers[0].start);

        break;
        }

        for (i = 0; i < n_buffers; ++i)
            if (buf.m.userptr == (unsigned long)buffers[i].start && buf.length == buffers[i].length)
                break;

        assert(i < n_buffers);

        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");

        break;
    }

    return 1;
}
#endif

/*
 */
int print_support_format()
{
    struct v4l2_fmtdesc fmt;
    struct v4l2_frmsizeenum frmsize;

    if (devfd < 0)
    {
        err("Not init it!");
        return RET_CAM_NOT_INIT;
    }
    // memset(&fmt, 0, sizeof(fmt));
    CLEAR(fmt);
    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 指定需要枚举的类型
    /* 查询摄像头可捕捉的图片类型，VIDIOC_ENUM_FMT: 枚举摄像头帧格式 */
    while (_ioctl(VIDIOC_ENUM_FMT, &fmt) == RET_CAM_SUCCESS)
    {
        fmt.index++;
        /* 打印摄像头图像格式 */
        printf("++ pixelformat = ''%c%c%c%c'', description = ''%s'' ++\n",
               fmt.pixelformat & 0xFF, (fmt.pixelformat >> 8) & 0xFF,
               (fmt.pixelformat >> 16) & 0xFF, (fmt.pixelformat >> 24) & 0xFF,
               fmt.description);
        /* 查询该图像格式所支持的分辨率 */
        // memset(&frmsize, 0, sizeof(frmsize));
        CLEAR(frmsize);
        frmsize.index = 0;
        frmsize.pixel_format = fmt.pixelformat;
        while (_ioctl(VIDIOC_ENUM_FRAMESIZES, &frmsize) == RET_CAM_SUCCESS)
        {
            frmsize.index++;
            /* 打印图片分辨率 */
            printf("- width: %d height: %d\n",
                   frmsize.discrete.width, frmsize.discrete.height);
        }
    }
    return RET_CAM_SUCCESS;
}
