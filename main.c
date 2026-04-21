#include "ssd1306_i2c.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>
#include <stdio.h>

#define SDA_PIN 4
#define SCL_PIN 5

int main(void)
{
    // initialize
    stdio_init_all();
    i2c_init(i2c0, 100000);

    // set functions for gpio pins
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // pull up power for pins
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // initialize screen
    SSD1306_init();

    // render the area of the screen
    struct render_area screen = 
    {
        .start_col = 0,
        .end_col = SSD1306_WIDTH -1,
        .start_page = 0,
        .end_page = SSD1306_NUM_PAGES - 1
    };
    calc_render_area_buflen(&screen);

    // create the buffer and 0 it
    uint8_t buf[SSD1306_BUF_LEN];
    memset(buf, 0, SSD1306_BUF_LEN);

    // render nothing on screen to be safe
    render(buf, &screen);

    // create variable for storing data
    char stats[100];
    float CPU_temp;
    float CPU_usage;
    float GPU_temp;
    float GPU_usage;
    char line_1[20];
    char line_2[20];
    char line_3[20];
    char line_4[20];
    while(1)
    {
        memset(buf, 0, SSD1306_BUF_LEN);

        fgets(stats, sizeof(stats), stdin);
        sscanf(stats, "CPU:%f,USAGE:%f,GPU:%f,GUSAGE:%f", &CPU_temp, &CPU_usage, &GPU_temp, &GPU_usage);

        sprintf(line_1, "CPU %.1f *", CPU_temp);
        sprintf(line_2, "USAGE %.1f%%", CPU_usage);
        sprintf(line_3, "GPU %.1f * %.1f%%", GPU_temp, GPU_usage);
        sprintf(line_4, "~ *!!");
        
        WriteString(buf, 0, 0, "PC STATS");
        WriteString(buf, 0, 8, line_1);
        WriteString(buf, 0, 16, line_2);
        WriteString(buf, 0, 24, line_3);
        if (CPU_temp >= 80 || GPU_temp >= 85)
        {
            WriteString(buf, 80, 0, line_4);
        }

        render(buf, &screen);

    }
}