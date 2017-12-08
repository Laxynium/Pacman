/*

SDL2_gfxPrimitives.h: graphics primitives for SDL

Copyright (C) 2012  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/

#ifndef _SDL2_gfxPrimitives_h
#define _SDL2_gfxPrimitives_h

#include <math.h>
#ifndef M_PI
#define M_PI    3.1415926535897932384626433832795
#endif

#include "SDL.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

	/* ----- Versioning */

#define SDL2_GFXPRIMITIVES_MAJOR        1
#define SDL2_GFXPRIMITIVES_MINOR        0
#define SDL2_GFXPRIMITIVES_MICRO        1


	/* ---- Function Prototypes */

#ifdef _MSC_VER
#  if defined(DLL_EXPORT) && !defined(LIBSDL2_GFX_DLL_IMPORT)
#    define SDL2_GFXPRIMITIVES_SCOPE __declspec(dllexport)
#  else
#    ifdef LIBSDL2_GFX_DLL_IMPORT
#      define SDL2_GFXPRIMITIVES_SCOPE __declspec(dllimport)
#    endif
#  endif
#endif
#ifndef SDL2_GFXPRIMITIVES_SCOPE
#  define SDL2_GFXPRIMITIVES_SCOPE extern
#endif

	/* Note: all ___Color routines expect the color to be in format 0xRRGGBBAA */

	/* Pixel */

	SDL2_GFXPRIMITIVES_SCOPE int pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Horizontal line */


	/* Vertical line */


	/* Rectangle */


	/* Rounded-Corner Rectangle */


	/* Filled rectangle (Box) */


	/* Rounded-Corner Filled rectangle (Box) */

	

	/* Line */

	
	/* AA Line */



	/* Thick Line */
	

	/* Circle */

	/* Arc */


	/* AA Circle */



	/* Filled Circle */

	SDL2_GFXPRIMITIVES_SCOPE int filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y,
		Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Ellipse */



	/* AA Ellipse */



	/* Filled Ellipse */



	/* Pie */

	
	/* Filled Pie */

	

	/* Trigon */

	

	/* AA-Trigon */



	/* Filled Trigon */

	
	/* Polygon */

	

	/* AA-Polygon */


	/* Filled Polygon */


	/* Textured Polygon */


	/* Bezier */

	/* Characters/Strings */


	/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif                          /* _SDL2_gfxPrimitives_h */