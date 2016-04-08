#ifndef FAU_TEXTURE_H
#define FAU_TEXTURE_H

	#include <fau_common.h>
	
	typedef struct
	{
		char* path;
		bool is_allocated; // not sure if this make sense by now
		int x;
		int y;
		int w;
		int h;
		s_texture* ref;
	} texture;
	
	int texture_load(texture* img, char* path);
	int texture_free(texture* img);
	int texture_render(texture* img, int x, int y);
	int texture_render_with_clip(texture* img, int x, int y, s_rect* clip);
	int texture_render_with_clip_and_rotation(
		texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
	int texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue); // color modulation

	// BlendModes { SDL_BLENDMODE_NONE, SDL_BLENDMODE_BLEND, SDL_BLENDMODE_ADD, SDL_BLENDMODE_MOD }
	int texture_set_blend_mode(texture* img, SDL_BlendMode blending);
	int texture_set_alpha(texture* img, Uint8 alpha);

	#ifdef _SDL_TTF_H
	bool texture_load_font_string(texture* img, char* text, SDL_Color text_color);
	#endif

#endif
