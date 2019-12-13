#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 900
#define HEIGHT 700
#define FIELDS 11
#define IMG_PATH "D:\\Aplikacje\\DynaBlaster\\bin\\Debug\\a.bmp"
#define TEXTURE_PATH "D:\\Aplikacje\\DynaBlaster\\bin\\Debug\\game.png"

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);
float WidthField = WIDTH/(float)(FIELDS+2);
float HeightField = HEIGHT/(float)(FIELDS+2);

int main (int argc, char *argv[]) {
    // Inicjalizacja SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Utworzenie okienka
    SDL_Window *window = SDL_CreateWindow("Dyna Blaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // INICJALIZACJA WSPOMAGANIA OBRAZOW TYPU JPG ORAZ PNG
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture * image_texture;
    SDL_Texture * SpriteImage;
    image_texture = initialize_texture_from_file( TEXTURE_PATH, renderer);
    SpriteImage = initialize_texture_from_file( IMG_PATH, renderer);

    SDL_Rect character;
    character.x = WidthField+5;
    character.y = HeightField+5;
    character.w = WidthField*0.8;
    character.h = HeightField*0.8;

    int running = 1;
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }

            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:  character.x-=4; break;
                case SDLK_RIGHT: character.x+=5; break;
                case SDLK_UP:    character.y-=5; break;
                case SDLK_DOWN:  character.y+=5; break;
            }
        }
        // Background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, NULL, NULL);
        int coll = detect_collision(character);
        if(coll)
        {
            printf("KOLIZJA!!!");
        }
        // Player
        SDL_RenderCopyEx(renderer, SpriteImage, NULL, &character, 0, NULL, 1);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }


    // Release resources
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int detect_collision(SDL_Rect rect){
    if(detect_collision_point(rect.x, rect.y)) //left up corner
        return 1;
    if(detect_collision_point(rect.x+rect.w, rect.y)) // right up corner
        return 1;
    if(detect_collision_point(rect.x, rect.y+rect.h)) // left bottom corner
        return 1;
    if(detect_collision_point(rect.x+rect.w, rect.y+rect.h)) // right bottom corner
        return 1;

    return 0;
}

int detect_collision_point(int x, int y){
    int current_field_horizontally = (x/WidthField);
    int current_field_vertical = (y/HeightField);

    if(current_field_horizontally%2==0 && current_field_vertical%2 == 0)
        return 1;
    if(current_field_horizontally == 0 || current_field_horizontally == (FIELDS+1))
        return 1;
    if(current_field_vertical == 0 || current_field_vertical == (FIELDS+1))
        return 1;

    return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}
