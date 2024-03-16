#include <stdio.h>
#include <stdlib.h>

void dfs(int** image, int imageSize, int* imageColSize, int sr, int sc,
         int color, int old_color) {
    if (sr < 0 || sr >= imageSize || sc < 0 || sc >= *imageColSize ||
        image[sr][sc] == color || image[sr][sc] != old_color)
        return;
    image[sr][sc] = color;
    dfs(image, imageSize, imageColSize, sr - 1, sc, color, old_color);
    dfs(image, imageSize, imageColSize, sr + 1, sc, color, old_color);
    dfs(image, imageSize, imageColSize, sr, sc - 1, color, old_color);
    dfs(image, imageSize, imageColSize, sr, sc + 1, color, old_color);
}
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc,
                int color, int* returnSize, int** returnColumnSizes) {
    if (!image) return NULL;
    int old_color = image[sr][sc];
    dfs(image, imageSize, imageColSize, sr, sc, color, old_color);

    *returnSize = imageSize;
    *returnColumnSizes = imageColSize;
    return image;
}

int main() {
    int img[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    int imageSize = sizeof(img) / sizeof(img[0]);
    int imageColSize = sizeof(img[0]) / sizeof(img[0][0]);
    int** image = (int**)malloc(sizeof(int*) * imageSize);
    for (int i = 0; i < imageSize; i++) {
        image[i] = (int*)malloc(sizeof(int) * imageColSize);
        for (int j = 0; j < imageColSize; j++) {
            image[i][j] = img[i][j];
        }
    }
    int sr = 0;
    int sc = 0;
    int color = 2;
    int returnSize = 0;
    int* returnColumnSizes = &imageColSize;
    int** ans = floodFill(image, imageSize, &imageColSize, sr, sc, color,
                          &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < *returnColumnSizes; j++) {
            printf("%d,", ans[i][j]);
        }
        printf("\n");
    }
}