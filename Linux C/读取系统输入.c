#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <linux/input.h>

const char *ev_name[] = {"EV_SYN", "EV_KEY", "EV_REL", "EV_ABS", "EV_MSC", "EV_SW",
                         "EV_LED", "EV_SND", "EV_REP", "EV_FF", "EV_PWR", "EV_FF_STATUS", "EV_MAX", "EV_CNT"};

int main(int argc, char *argv[])
{
    int keys_fd;
    char ret[2];
    struct input_event t;
    char dev_name[255];

    sprintf(dev_name, "/dev/input/%s", argc > 1 ? argv[1] : "event0");
    keys_fd = open(dev_name, O_RDONLY);
    if (keys_fd <= 0)
    {
        printf("open device %s error!\n", dev_name);
        return 0;
    }

    while (1)
    {
        if (read(keys_fd, &t, sizeof(t)) == sizeof(t))
        {
            if (t.type == EV_KEY)
            { // Keyborad input
                printf("KEY 0x%02X %s\n", t.code, (t.value) ? "Pressed" : "Released");
                if (t.code == KEY_ESC)
                    break;
            }
            if (t.type == EV_REL)
            { // Mouse input
                printf("REL 0x%02X value=%d\n", t.code, t.value);
            }
            if (t.type == EV_ABS)
            { // Single Touch input
                printf("ABS 0x%02X value=%d\n", t.code, t.value);
            }
        }
        else
        {
            printf("event type = %s, code=0x%02X, value=%d\n", ev_name[t.type], t.code, t.value);
        }
    }
    close(keys_fd);

    return 0;
}

// 等待输入
while ((ch = getchar()))
{
    printf("get %d\n", i);
    if (ch == 10)
    { // enter key
        count++;
        // if (captureImage(0)==0) imgSave("img", count, MatFrame[0]);
    }
    if (ch == 113)
    { // q key
        printf("quit now\n");
        return 0;
    }
}