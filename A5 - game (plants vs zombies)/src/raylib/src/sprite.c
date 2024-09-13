#include "sprite.h"

Rectangle GetSpriteBounds(Texture2D texture, Rectangle rect) {
    // Create an image from the texture
    Image image = LoadImageFromTexture(texture);

    // Calculate the actual rectangle coordinates within the image
    Rectangle imageRect = {rect.x * image.width / texture.width,
                           rect.y * image.height / texture.height,
                           rect.width * image.width / texture.width,
                           rect.height * image.height / texture.height};

    // Get the alpha border of the image rectangle
    Rectangle alphaBorder =
        GetImageAlphaBorder(ImageFromImage(image, imageRect), 128);

    // Calculate the normalized texture coordinates of the alpha border
    Rectangle textureBounds = {
        (imageRect.x + alphaBorder.x) * texture.width / image.width,
        (imageRect.y + alphaBorder.y) * texture.height / image.height,
        alphaBorder.width * texture.width / image.width,
        alphaBorder.height * texture.height / image.height};

    // Unload the image
    UnloadImage(image);

    return textureBounds;
}
