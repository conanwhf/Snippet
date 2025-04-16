#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/* Config the serical */
static int serialConfig(int bitrate, int bits, int stop, char parity, int flow)
{
    int br_arr[] = {B38400, B19200, B9600, B4800, B2400, B1200, B300};
    struct termios options;

    if (tcgetattr(fd, &options) != 0)
    {
        err("Serial device error!\n");
        return -1;
    }

    options.c_cflag |= CLOCAL;                          // Won't block the port busy
    options.c_cflag |= CREAD;                           // Make sure can read
    options.c_oflag &= ~OPOST;                          // Raw data output
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/

    // Bitrate setting
    cfsetispeed(&options, br_arr[bitrate]);
    cfsetospeed(&options, br_arr[bitrate]);

    // Data flow contorl mode
    switch (flow)
    {
    case NO_FLOW_CTL: // No flow control
        options.c_cflag &= ~CRTSCTS;
        break;
    case HW_FLOW_CTL: // Flow control by hardware
        options.c_cflag |= CRTSCTS;
        break;
    case SW_FLOW_CTL: // Flow control by software
        options.c_cflag |= IXON | IXOFF | IXANY;
        break;
    default:
        err("Unsupported data flow mode setting\n");
        return -1;
    }

    // Data Bits setting
    options.c_cflag &= ~CSIZE;
    switch (bits)
    {
    case DATABITS_5:
        options.c_cflag |= CS5;
        break;
    case DATABITS_6:
        options.c_cflag |= CS6;
        break;
    case DATABITS_7:
        options.c_cflag |= CS7;
        break;
    case DATABITS_8:
        options.c_cflag |= CS8;
        break;
    default:
        err("Unsupported data size\n");
        return -1;
    }

    // Parity bit setting
    switch (toupper(parity))
    {
    case CHECK_BIT_NONE: // 无奇偶校验位。
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~INPCK;
        break;
    case CHECK_BIT_ODD: // 设置为奇校验
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag |= INPCK;
        break;
    case CHECK_BIT_EVEN: // 设置为偶校验
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_iflag |= INPCK;
        break;
    case CHECK_BIT_SPACE: // 设置为空格
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;
    default:
        err("Unsupported parity\n");
        return -1;
    }

    // Stop Bits
    switch (stop)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        err("Unsupported stop bits\n");
        return -1;
    }

    // Timeout setting
    options.c_cc[VTIME] = 5; /* 读取一个字符等待0.5s */
    options.c_cc[VMIN] = 0;  /* 读取字符的最少个数为1 */
    tcflush(fd, TCIFLUSH);   // 如果发生数据溢出，接收数据，但是不再读取

    // Enable the settings
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        err("set serial error!\n");
        return -1;
    }

    return 0;
}

/* Init the serial device by configs */
int serialInit(int bitrate, int bits, int stop, char parity, int flow)
{

    fd = open(SERIAL_DEV, O_RDWR, S_IRUSR | S_IWUSR);
    if (fd <= 0)
    {
        err("Init serial device fail\n");
        return -1;
    }
    return serialConfig(BR_9600, DATABITS_8, 1, CHECK_BIT_NONE, NO_FLOW_CTL);
}