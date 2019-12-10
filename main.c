#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 900
#define HEIGHT 700
#define FIELDS 11
#define IMG_PATH "D:\\Aplikacje\\DynaBlaster\\bin\\Debug\\a.bmp"
#define TEXTURE_PATH "D:\\Aplikacje\\DynaBlaster\\bin\\Debug\\texture.png"

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

int main (int argc, char *argv[]) {
    // Inicjalizacja SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Rozmiar jednego pola
    float WidthField = WIDTH/(float)(FIELDS+2);
    float HeightField = HEIGHT/(float)(FIELDS+2);

    // Utworzenie okienka
    SDL_Window *window = SDL_CreateWindow("Dyna Blaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderClear(renderer);

    // INICJALIZACJA WSPOMAGANIA OBRAZOW TYPU JPG ORAZ PNG
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    ///START GENEROWANIA MAPY///
    SDL_Texture * image_texture;
    SDL_Texture * SpriteImage;
    image_texture = initialize_texture_from_file( TEXTURE_PATH, renderer);
    SpriteImage = initialize_texture_from_file( IMG_PATH, renderer);

    SDL_Rect texture_destination[FIELDS];
    SDL_Rect character;

    character.x = WidthField;
    character.y = HeightField;
    character.w = WidthField;
    character.h = HeightField;

    // Utworzenie mapy. Częsc gorna
    for(int i = 0; i <FIELDS; i ++){
        texture_destination[i].x = WidthField+(WidthField*i);
        texture_destination[i].y = 0;
        texture_destination[i].w = WidthField;
        texture_destination[i].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[i]);
    }

    // Utworzenie mapy. Częsc lewa
    for(int i = 0; i <FIELDS; i ++){
        texture_destination[i].x = 0;
        texture_destination[i].y = HeightField+(HeightField*i);
        texture_destination[i].w = WidthField;
        texture_destination[i].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[i]);
    }

    // Utworzenie mapy. Częsc dolna
    for(int i = 0; i <FIELDS; i ++){
        texture_destination[i].x = WidthField+(WidthField*i);
        texture_destination[i].y = HeightField+(HeightField*FIELDS);
        texture_destination[i].w = WidthField;
        texture_destination[i].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[i]);
    }

    // Utworzenie mapy. Częsc prawa
    for(int i = 0; i <FIELDS; i ++){
        texture_destination[i].x = WidthField+(WidthField*FIELDS);
        texture_destination[i].y = HeightField+(HeightField*i);
        texture_destination[i].w = WidthField;
        texture_destination[i].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[i]);
    }

    // Utworzenie mapy. Przeszkody nie zniszczalne
    for(int j = (FIELDS/2)-1; j >= 0; j--){
        for(int i = (FIELDS/2)-1; i >= 0; i--){
            texture_destination[i].x = (WidthField*2)+(WidthField*(i*2));
            texture_destination[i].y = (HeightField*2)+(HeightField*(j*2));
            texture_destination[i].w = WidthField;
            texture_destination[i].h = HeightField;
            SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[i]);
        }
    }
        //LEWY GORNY ROG
        texture_destination[0].x = 0;
        texture_destination[0].y = 0;
        texture_destination[0].w = WidthField;
        texture_destination[0].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[0]);
        //PRAWY GORNY ROG
        texture_destination[0].x = WidthField*FIELDS+WidthField;
        texture_destination[0].y = 0;
        texture_destination[0].w = WidthField;
        texture_destination[0].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[0]);
        //LEWY DOLNY ROG
        texture_destination[0].x = 0;
        texture_destination[0].y = HeightField*FIELDS+HeightField;
        texture_destination[0].w = WidthField;
        texture_destination[0].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[0]);
        //PRAWY DOLNY ROG
        texture_destination[0].x = WidthField*FIELDS+WidthField;
        texture_destination[0].y = HeightField*FIELDS+HeightField;
        texture_destination[0].w = WidthField;
        texture_destination[0].h = HeightField;
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination[0]);
    ///KONIEC GENREROWANIA MAPY//

    //SDL_RenderCopy(renderer, SpriteImage, NULL, &character);
    //SDL_RenderCopy(renderer, SpriteImage, NULL, &character);
    SDL_RenderCopy(renderer, SpriteImage, NULL, &character);
    SDL_RenderPresent(renderer);

    int running = 1;
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT){
                running = 0;
            } else if(event.key.keysym.sym == SDLK_RIGHT){
                character.x = character.x + 5;
            } else if(event.key.keysym.sym == SDLK_LEFT){
                character.x = character.x - 5;
            } else if(event.key.keysym.sym == SDLK_DOWN){
                character.y = character.y + 5;
            } else if(event.key.keysym.sym == SDLK_UP){
                character.y = character.y - 5;
            }

        }
        //SDL_BlitSurface(Background, NULL, Backbuffer, NULL);
        //SDL_UpdateWindowSurface(window);
            //SDL_RenderClear( renderer );
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, SpriteImage, NULL, &character);
            SDL_RenderPresent(renderer);
    }


    // Release resources
    SDL_DestroyTexture(image_texture);
    SDL_DestroyTexture(SpriteImage);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}
