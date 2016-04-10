#include <faudef.h>

int 
dot_init(fau_dot* dot)
{
	dot->posX = 100;
	dot->posY = 100;

	dot->velX = 0;
	dot->velY = 0;

	dot->w = 20;
	dot->h = 20;

	dot->v = 10;
	return 0;
}

int 
dot_handle_events(fau_dot* dot, s_event* event)
{
	if( event->type == SDL_KEYDOWN && event->key.repeat == 0 )
	{
		// printf("down\n");
		switch( event->key.keysym.sym )
		{
			case SDLK_UP: 
				dot->velY -= dot->v; break;
            case SDLK_DOWN: 
            	dot->velY += dot->v; break;
            case SDLK_LEFT: 
            	dot->velX -= dot->v; break;
            case SDLK_RIGHT: 
            	dot->velX += dot->v; break;
		}
	} 
	else if( event->type == SDL_KEYUP && event->key.repeat == 0 )
	{
		// printf("realease\n");
		// switch( event->key.keysym.sym )
		// {
		// 	case SDLK_UP: 
		// 		dot->velY += dot->v; 
		// 		break;
  //           case SDLK_DOWN: 
  //           	dot->velY -= dot->v; 
  //           	break;
  //           case SDLK_LEFT: 
  //           	dot->velX += dot->v; 
  //           	break;
  //           case SDLK_RIGHT: 
  //           	dot->velX -= dot->v; 
  //           	break;
		// }
	}

	// printf("dot->velY: %d\n", dot->velY);
	// printf("dot->velX: %d\n", dot->velX);
	// printf("dot->vel: %d\n", dot->v);
	return 0;
}

int dot_move(fau_dot* dot)
{
	// dot->posX += dot->velX;

	// if( ( dot->posX < 0 ) || ( dot->posX + dot->w > SCREEN_WIDTH ) )
	// {
	// 	dot->posX -= dot->velX;
	// }

	// dot->posY += dot->velY;

	// if( ( dot->posY < 0 ) || ( dot->posY + dot->h > SCREEN_HEIGHT ) )
	// {
	// 	dot->posY -= dot->velY;
	// }

	dot->posX += dot->velX;

	if( dot->posX < 0 )
	{
		dot->velX += dot->v;
	}
	else if ( dot->posX > (SCREEN_WIDTH - dot->w) )
	{
		dot->velX -= dot->v;
	}


	dot->posY += dot->velY;

	if( dot->posY < 0 )
	{
		dot->velY += dot->v;
	}
	else if ( dot->posY > (SCREEN_HEIGHT - dot->h) )
	{
		dot->velY -= dot->v;
	}

	// dot->v = (int)(dot->v * 0.99999999);
	return 0;
}

int dot_render(fau_dot* dot, texture* dot_texture)
{
	texture_render(dot_texture, dot->posX, dot->posY);
	return 0;
}
