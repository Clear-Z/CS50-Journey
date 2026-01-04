#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    {
        if (card == NULL)
        {
            printf("Cloud not open %s", argv[1]); // 刚刚这里报错：format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘FILE’ [-Wformat=] printf("Cloud not open %s", *card);
            return 2;
        }
    }
    
    uint8_t buffer[512];

    char filename[8];
    int counter = 0;
    FILE *img = NULL; // 我还是有点不完全明白FILE的意思，它只是一个指针定义吗？应该是文件专用的吧？

    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (img != NULL) // 这里是不是可以写成if coueter！=0？
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, sizeof(uint8_t), 512, img);
            }
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    return 0;
}