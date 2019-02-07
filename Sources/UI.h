#ifndef UI_H
#define UI_H

#include <malloc.h>

typedef struct _ui_button
{
	int x; //x position of left top
	int y; //y position of left top
	int width;
	int height;
	int clicked;
	int highlighted;
} UI_button;

typedef struct _ui_image
{
	int x; //x position of left top
	int y; //y position of left top
	int width;
	int height;
	sfSprite * sprite;
} UI_image;

typedef struct _ui_text
{
	char * txt;
	sfText * text;
	sfColor color;
	//TBD
} UI_text;

typedef struct _ui_layer
{	
	int updating; //is updating
	int drawing; //is drawing

	int imageCount;
	int buttonCount;
	int textCount;

	UI_button * buttons;
	UI_image * images;
	UI_text * text;

} UI_layer;

void DestroyLayer(UI_layer*);
#endif