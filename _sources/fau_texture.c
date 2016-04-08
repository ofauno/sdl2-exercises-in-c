#include <faudef.h>

int 
texture_set_blend_mode(texture* img, SDL_BlendMode blending) {
	
	if (SDL_SetTextureBlendMode(img->ref, blending) < 0) {
		printf("texture_set_blend_mode: blending err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_set_alpha(texture* img, Uint8 alpha) {
	
	if (SDL_SetTextureAlphaMod(img->ref, alpha) < 0) {
		printf("texture_set_alpha: alpha err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue) {
	
	// http://wiki.libsdl.org/SDL_SetTextureColorMod
	if ( SDL_SetTextureColorMod(img->ref, red, green, blue) < 0 ) {
		printf("texture_set_color: color modulation err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render_with_clip_and_rotation(
	texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
																						
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) 
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
	if ( SDL_RenderCopyEx(g_render, img->ref, clip, &renderQuad, angle, center, flip) < 0 ) 
	{
		printf("texture_render_with_clip_and_rotation: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render_with_clip(texture* img, int x, int y, s_rect* clip) {
	
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) 
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
  if ( SDL_RenderCopy(g_render, img->ref, clip, &renderQuad) < 0 ) 
	{
		printf("texture_render_with_clip: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render(texture* img, int x, int y) {
	
	s_rect renderQuad = { x, y, img->w, img->h };	
	
  if ( SDL_RenderCopy(g_render, img->ref, 0, &renderQuad) < 0 ) 
	{
		printf("texture_render: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_free(texture* img) {
	
	if ( img->ref != 0 ) 
	{
		SDL_DestroyTexture(img->ref);
		img->ref = 0;
		img->w = 0;
		img->h = 0;
	}
	
	return 0;
}

int 
texture_load(texture* img, char* path) {
	
	// The final texture
	s_texture* newTexture = 0;

	// Load image at specified path
	s_surface* loadedSurface = IMG_Load(path);
	
	if ( !loadedSurface ) 
	{
		printf("texture_load: Unable to load %s! Error: %s\n", path, IMG_GetError());
	} 
	else 
	{
		printf("texture_load: color keying cyan\n");
		// color key cyan 0, 255, 255
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_render, loadedSurface);
		
		if ( !newTexture ) 
		{
			printf("texture_load: texture %s! Error: %s\n", path, SDL_GetError());
		} 
		else 
		{
			img->w = loadedSurface->w;
			img->h = loadedSurface->h;
			img->path = path;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	
	img->ref = newTexture;
	return img->ref != 0;
}


#ifdef _SDL_TTF_H
bool 
texture_load_font_string(texture* img, char* text, SDL_Color text_color) {
	
	// rm preexisting texture
	texture_free(img);
	
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_43.html
	s_surface* text_surface = TTF_RenderText_Solid(g_font, text, text_color);
	
	if ( text_surface != 0 ) 
	{
		// create texture
		img->ref = SDL_CreateTextureFromSurface(g_render, text_surface);
		
		if ( !img->ref ) 
		{
			printf("texture_load_font_string: unable to create text texture, err: %s\n", SDL_GetError());
		} 
		else 
		{	
			// get image dimensions
			img->w = text_surface->w;
			img->h = text_surface->h;
		}
		
		// flush surface
		SDL_FreeSurface(text_surface);
	} 
	else 
	{
				printf("texture_load_font_string: unable to render text, ttf err: %s\n", TTF_GetError());
	}
	
	return img->ref != 0;
}
#endif
