//BEGIN HEAD
//BEGIN DESCRIPTION

/* This is a small SDL2 Demo
 * and it does demonstrate how...
 * load and use a Window Icon
 * to set up a window and a renderer
 * to load and render textures with dest rects
 * do conditional Rendering
 * check point in Rect intersection
 * check point in Circle intersection
 * to play a sound chunk and set it's volume
 * to play/pause/halt music, set it's volume
 * to open links
 * to ask for and respond to key/mouse events
 * to create tooltips
 */

/* DEFINED PROGRESS GOALS
 * 
 * None atm
 * TODO copy window surface to texture during idle
 * 	and move it like a flag in the wind
 * 
 * TODO open links on Windows
 * ShellExecute(NULL, "open", "http://url", NULL, NULL, SW_SHOWNORMAL);
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED   255,0,0,255
#define WW 540
#define WH 340
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;

//BEGIN TIMING
Uint32 frame_time  = 0;
Uint32 frame_start = 0;

Uint32 timer = 0;
//END TIMING

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;

TTF_Font       *font		= NULL;
SDL_Texture    *link1		= NULL;
SDL_Rect 	link1_dst;
SDL_Texture    *link1_tp	= NULL;
SDL_Rect 	link1_tp_dst;

SDL_Texture    *link2		= NULL;
SDL_Rect 	link2_dst;
SDL_Texture    *link2_tp	= NULL;
SDL_Rect 	link2_tp_dst;
SDL_Texture    *octoface	= NULL;
SDL_Rect 	octoface_dst;

SDL_Texture    *text1		= NULL;
SDL_Rect 	text1_dst;
SDL_Texture    *text1_tp	= NULL;
SDL_Rect 	text1_tp_dst;

SDL_Texture    *text2		= NULL;
SDL_Rect 	text2_dst;
SDL_Texture    *text2_tp	= NULL;
SDL_Rect 	text2_tp_dst;

SDL_Texture    *text3		= NULL;
SDL_Rect 	text3_dst;
SDL_Texture    *text3_tp	= NULL;
SDL_Rect 	text3_tp_dst;

SDL_Texture    *kdev		= NULL;
SDL_Rect 	kdev_dst;
SDL_Texture    *kdev_tp		= NULL;
SDL_Rect 	kdev_tp_dst;

SDL_Texture    *plus	= NULL;
SDL_Rect 	plus_dst;
//END 	VISIBLES

SDL_Point	mouse;

//Audio and State
Mix_Chunk *click   		= NULL;
int	   chunk_played_in	= 0;
SDL_bool   chunk_played		= SDL_FALSE;
Mix_Music *Music 		= NULL;
//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void assets_in	(void);
void assets_out	(void);
void play_click	(void);
void open_link	(void);
void show_tp	(void);
SDL_bool PointInCircle(SDL_Point *, SDL_Rect *);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "SDL2 enabled Demo 01");
SDL_ShowWindow(Window);
//END WINDOW

SDL_Event event;
Mix_PlayMusic(Music, -1);
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){
	frame_start=SDL_GetTicks();
	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			timer=0;
			SDL_GetMouseState(&mouse.x, &mouse.y);
			play_click();
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				;
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT && chunk_played_in!=0){
				open_link();
			}
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					Mix_HaltMusic();
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					if(!Mix_PlayingMusic()){
						Mix_PlayMusic(Music, -1);
					}
					else{
						if(Mix_PausedMusic()){
							Mix_ResumeMusic();
						}
						else{
							Mix_PauseMusic();
						}
					}
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);

	SDL_RenderCopy(Renderer, kdev, NULL, &kdev_dst);
	SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);
	SDL_RenderCopy(Renderer, link1, NULL, &link1_dst);
	SDL_RenderCopy(Renderer, link2, NULL, &link2_dst);
	SDL_RenderCopy(Renderer, text1, NULL, &text1_dst);
	SDL_RenderCopy(Renderer, text2, NULL, &text2_dst);
	SDL_RenderCopy(Renderer, text3, NULL, &text3_dst);
	SDL_RenderCopy(Renderer, plus, NULL, &plus_dst);

	if (chunk_played_in==2)
		SDL_RenderCopy(Renderer, octoface, NULL, &octoface_dst);

	if (chunk_played_in !=0 && timer>800)
		show_tp();

	SDL_RenderPresent(Renderer);
	//END   RENDERING

	frame_time = SDL_GetTicks()-frame_start;

	if (chunk_played_in>0)
		timer+=frame_time;
	else
		timer=0;
	}

//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{
	int w,h;
	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x=ww-logo_dst.w*1.5;
	logo_dst.y=(wh/2)-(logo_dst.h*1.5);
	//END 	LOGO
	
	//BEGIN LINK1
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 24);
	SDL_Color color={255,255,255,255}, bgcolor={255,0,0,255};
	temp_surface=TTF_RenderText_Shaded(font," SDL Website ",color,bgcolor);
	link1 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link1, NULL, NULL, &link1_dst.w, &link1_dst.h);
	link1_dst.x=logo_dst.x+6;
	link1_dst.y=logo_dst.y+logo_dst.h+4;
	//END 	LINK1
	
	//BEGIN TP1
	SDL_Color black={BLACK};
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," Link to SDL Website ",black);
	link1_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link1_tp, NULL, NULL, &link1_tp_dst.w, &link1_tp_dst.h);
	//END 	TP1
	
	//BEGIN LINK2
	font=TTF_OpenFont("./assets/fonts/fontawesome-webfont.ttf", 100);
	temp_surface=TTF_RenderGlyph_Blended(font, 0xf09b , black);
	link2 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link2, NULL, NULL, &link2_dst.w, &link2_dst.h);
	link2_dst.x=link2_dst.w;
	link2_dst.y=link1_dst.y+link2_dst.h*0.75;
	//END 	LINK2
	
	//BEGIN TP2
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," Link to Github ",black);
	link2_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link2_tp, NULL, NULL, &link2_tp_dst.w, &link2_tp_dst.h);
	//END 	TP2
	
	//BEGIN OCTOFACE
	temp_surface = IMG_Load("./assets/gfx/octoface.png");
	octoface = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(octoface, NULL, NULL, &w, &h);
	octoface_dst.w=w*0.16;
	octoface_dst.h=h*0.16;
	octoface_dst.x=link2_dst.x+20;
	octoface_dst.y=link2_dst.y+42;
	//END 	OCTOFACE
	
	//BEGIN TEXT1
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 22);
	temp_surface=TTF_RenderText_Blended(font,"Template Repository",black);
	text1 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text1, NULL, NULL, &text1_dst.w, &text1_dst.h);
	text1_dst.x=link2_dst.x+link2_dst.w+18;
	text1_dst.y=link2_dst.y+10;
	//END 	TEXT1
	
	//BEGIN TEXT1_TP
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," Link to this Repo ",black);
	text1_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text1_tp, NULL, NULL, &text1_tp_dst.w, &text1_tp_dst.h);
	//END 	TEXT1_TP
	
	//BEGIN TEXT2
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 22);
	temp_surface=TTF_RenderText_Blended(font,"SDL2-C-Tutorials",black);
	text2 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text2, NULL, NULL, &text2_dst.w, &text2_dst.h);
	text2_dst.x=text1_dst.x+2;
	text2_dst.y=text1_dst.y+text1_dst.h;
	//END 	TEXT2
	
	//BEGIN TEXT2_TP
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," SDL2-C-Tutorials ",black);
	text2_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text2_tp, NULL, NULL, &text2_tp_dst.w, &text2_tp_dst.h);
	//END 	TEXT2_TP
	
	//BEGIN TEXT3
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 22);
	temp_surface=TTF_RenderText_Blended(font,"Author on SDL Discourse",black);
	text3 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text3, NULL, NULL, &text3_dst.w, &text3_dst.h);
	text3_dst.x=text1_dst.x;
	text3_dst.y=text2_dst.y+text1_dst.h;
	//END 	TEXT3
	
	//BEGIN TEXT3_TP
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," Author on Discourse ",black);
	text3_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text3_tp, NULL, NULL, &text3_tp_dst.w, &text3_tp_dst.h);
	//END 	TEXT3_TP
	
	//BEGIN KDEV
	temp_surface = IMG_Load("./assets/gfx/kdev.png");
	kdev = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(kdev, NULL, NULL, &w, &h);
	kdev_dst.w=w;
	kdev_dst.h=h;
	kdev_dst.x=100;
	kdev_dst.y=70;
	//END 	KDEV
	
	//BEGIN KDEV_TP
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 15);
	temp_surface=TTF_RenderText_Blended(font," KDev Website ",black);
	kdev_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(kdev_tp, NULL, NULL, &kdev_tp_dst.w, &kdev_tp_dst.h);
	//END 	KDEV_TP
	
	//BEGIN PLUS
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 72);
	temp_surface=TTF_RenderText_Blended(font,"+",black);
	plus = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(plus, NULL, NULL, &plus_dst.w, &plus_dst.h);
	plus_dst.x=kdev_dst.x+kdev_dst.w+plus_dst.w/2;
	plus_dst.y=kdev_dst.y+kdev_dst.w-plus_dst.h;
	//END 	PLUS
	
	SDL_FreeSurface(temp_surface);
	
	click = Mix_LoadWAV("./assets/snd/click.wav" );
	Mix_VolumeChunk(click, 35);
	Music=Mix_LoadMUS("./assets/snd/The.madpix.project_-_Wish_You_Were_Here.mp3");
	Mix_VolumeMusic(35);
}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(link1);
	SDL_DestroyTexture(link1_tp);
	SDL_DestroyTexture(link2);
	SDL_DestroyTexture(link2_tp);
	SDL_DestroyTexture(text1);
	SDL_DestroyTexture(text2);
	SDL_DestroyTexture(text3);
	SDL_DestroyTexture(text1_tp);
	SDL_DestroyTexture(text2_tp);
	SDL_DestroyTexture(text3_tp);
	SDL_DestroyTexture(octoface);
	SDL_DestroyTexture(kdev);
	SDL_DestroyTexture(kdev_tp);
	SDL_DestroyTexture(plus);
	Mix_FreeChunk(click);
	Mix_FreeMusic(Music);
	TTF_CloseFont(font);
}

SDL_bool PointInCircle(SDL_Point *point, SDL_Rect *square)
{
	float x=square->x+square->w/2;
	float y=square->y+square->h/2;;
	float r=square->h/2;
	
	float dx=x-point->x;
	float dy=y-point->y;
	
	float distance=sqrtf(dx * dx + dy * dy);
	
	if (distance < r + 1)
		return SDL_TRUE;
	return SDL_FALSE;
}

void play_click(void)
{
	if (SDL_PointInRect(&mouse, &link1_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=1){
			chunk_played_in=1;
			chunk_played=SDL_TRUE;
		}
	} else if (PointInCircle(&mouse, &link2_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=2){
			chunk_played_in=2;
			chunk_played=SDL_TRUE;
		}
	} else if (SDL_PointInRect(&mouse, &text1_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=3){
			chunk_played_in=3;
			chunk_played=SDL_TRUE;
		}
	} else if (SDL_PointInRect(&mouse, &text2_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=4){
			chunk_played_in=4;
			chunk_played=SDL_TRUE;
		}
	} else if (SDL_PointInRect(&mouse, &text3_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=5){
			chunk_played_in=5;
			chunk_played=SDL_TRUE;
		}
	} else if (SDL_PointInRect(&mouse, &kdev_dst)){
		if (chunk_played==SDL_FALSE&&chunk_played_in!=6){
			chunk_played_in=6;
			chunk_played=SDL_TRUE;
		}
	} else {
		chunk_played_in=0;
	}

	if (chunk_played==SDL_TRUE && chunk_played_in!=0){
		Mix_PlayChannel(-1, click, 0);
		chunk_played=SDL_FALSE;
	}
}

void open_link(void)
{
	switch(chunk_played_in){
		case 1:
			system("xdg-open https://www.libsdl.org/");
			break;
		case 2:
			system("xdg-open https://github.com/");
			break;
		case 3:
			system("xdg-open https://github.com/Acry/SDL2-C-KDev_App_Template");
			break;
		case 4:
			system("xdg-open \"https://acry.github.io/\"");
			break;
		case 5:
			system("xdg-open https://discourse.libsdl.org/u/Acry/");
			break;
		case 6:
			system("xdg-open https://www.kdevelop.org/");
			break;
			
		default:
			break;
			//some statements to execute when default;
	}
}

void show_tp(void)
{
	switch(chunk_played_in){
		case 1:
			link1_tp_dst.x=mouse.x-link1_tp_dst.w/2;
			link1_tp_dst.y=mouse.y-link1_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &link1_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &link1_tp_dst);
			SDL_RenderCopy(Renderer, link1_tp, NULL, &link1_tp_dst);
			break;
		case 2:
			link2_tp_dst.x=mouse.x-link2_tp_dst.w/2;
			link2_tp_dst.y=mouse.y-link2_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &link2_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &link2_tp_dst);
			SDL_RenderCopy(Renderer, link2_tp, NULL, &link2_tp_dst);
			break;
		case 3:
			text1_tp_dst.x=mouse.x-text1_tp_dst.w/2;
			text1_tp_dst.y=mouse.y-text1_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &text1_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &text1_tp_dst);
			SDL_RenderCopy(Renderer, text1_tp, NULL, &text1_tp_dst);
			break;
		case 4:
			text2_tp_dst.x=mouse.x-text2_tp_dst.w/2;
			text2_tp_dst.y=mouse.y-text2_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &text2_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &text2_tp_dst);
			SDL_RenderCopy(Renderer, text2_tp, NULL, &text2_tp_dst);
			break;
		case 5:
			text3_tp_dst.x=mouse.x-text3_tp_dst.w/2;
			text3_tp_dst.y=mouse.y-text3_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &text3_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &text3_tp_dst);
			SDL_RenderCopy(Renderer, text3_tp, NULL, &text3_tp_dst);
			break;
		
		case 6:
			kdev_tp_dst.x=mouse.x-kdev_tp_dst.w/2;
			kdev_tp_dst.y=mouse.y-kdev_tp_dst.h;
			SDL_SetRenderDrawColor(Renderer,243,226,103,200);
			SDL_RenderFillRect(Renderer, &kdev_tp_dst);
			SDL_SetRenderDrawColor(Renderer,BLACK);
			SDL_RenderDrawRect(Renderer, &kdev_tp_dst);
			SDL_RenderCopy(Renderer, kdev_tp, NULL, &kdev_tp_dst);
			break;

		default:
			break;
			//some statements to execute when default;
	}
}
//END   FUNCTIONS
