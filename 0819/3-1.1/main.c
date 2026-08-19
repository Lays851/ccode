#include "image.h"

enum IMAGE_FMT {BMP, JPG, PNG};

enum IMAGE_FMT get_fmt(const char *p)
{
    if(strstr(p, ".jpg") || strstr(p, ".jpeg"))
        return JPG;
    else if(strstr(p, ".bmp"))
        return BMP;
    else if(strstr(p, ".png"))
        return PNG;
}

int main(int argc , char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage : ./a.out <imagefile>\n");
        exit(1);
    }

    //准备lcd
    struct lcdinfo *lcd = calloc(1, sizeof(struct lcdinfo));
    if(lcd == NULL)
    {
        perror("calloc lcd failed\n");
        exit(1);
    }
    if( !lcd_init(lcd, "/dev/fb0") )
    {
        fprintf(stderr, "init lcd failed\n");
        exit(1);
    }

    //判断图片类型
    enum IMAGE_FMT fmt = get_fmt(argv[1]);

    //根据选择打印方式
    void *handle = NULL;
    void (*imageshow)(struct lcdinfo *, const char *) = NULL;
    switch(fmt)
    {
    case JPG:
        handle = dlopen("libjpg.so", RTLD_LAZY);
        break;
    case BMP:
        handle = dlopen("libbmp.so", RTLD_LAZY);
        break;
    case PNG:
        // handle = dlopen("libpng.so", RTLD_LAZY);
        break;
    }

    imageshow = dlsym(handle , "imageshow");
    
    imageshow(lcd, argv[1]);
    lcd_release(lcd);
    free(lcd);

    return 0;
    //
}