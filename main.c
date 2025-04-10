#include "rmath.h"

#define RGFW_BUFFER
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define WIDTH 600
#define HEIGHT 400

rmMat4 transformation(float centerX, float centerY) {
    rmMat4 matrix = rmLoadIdentity();
    static float angle = 0;
    angle += 0.0001;
    if (angle >= 360) angle = 0;   

    matrix = rmTranslate(matrix.m, centerX, centerY, 0);    
    matrix = rmRotate(matrix.m, angle * DEG2RAD, 0, 0, 1);
    matrix = rmTranslate(matrix.m, -centerX, -centerY, 0);
    
    return matrix;
}

void drawPoint(u8* buffer, size_t x, size_t y, float centerX, float centerY, u32 color) {
    rmVec2 vec = rmVec2MultiplyMat4(RM_VEC2((float)x, (float)y), transformation(centerX, centerY));

	int index = ((u32)vec.y) * (4 * WIDTH) + (u32)vec.x * 4;
    if (index > WIDTH * HEIGHT * 4 || index < 0)
        return;

    memcpy(&buffer[index], &color, sizeof(u32)); 
}

void drawRect(u8* buffer, size_t x, size_t y, size_t w, size_t h, u32 color) {
    float centerX = (float)x + ((float)w / 2.0f);
    float centerY = (float)y + ((float)h / 2.0f);

    for (size_t y2 = 0; y2 < h; y2++)
        for (size_t x2 = 0; x2 < w; x2++)
            drawPoint(buffer, x + x2, y + y2,centerX, centerY, color);
}



int main() {
    RGFW_window* window = RGFW_createWindow("math test", RGFW_RECT(500, 500, WIDTH, HEIGHT), RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowNoInitAPI);
    RGFW_window_initBufferSize(window, RGFW_AREA(WIDTH, HEIGHT));
    
    while (RGFW_window_shouldClose(window) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(window)) {

        }
        
        memset(window->buffer, 0x00, WIDTH * HEIGHT * 4);
        drawRect(window->buffer, (WIDTH / 2) - (WIDTH / 8), (HEIGHT / 2) - (HEIGHT / 4), (WIDTH / 4), (HEIGHT / 2), 0xFFFFFFFF);
        RGFW_window_swapBuffers(window);
    }

    RGFW_window_close(window);
}
