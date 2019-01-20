#ifndef UI_H
#define UI_H

typedef struct _ui_element
{
	int locked; //is updating
	int hidden; //is drawing
	int type;
	
	int componentCount;
	int * componentTypes;
	void * (*components);
} UI_element;

typedef struct _ui_layer
{
	int elementCount;
	
	int locked; //is updating
	int hidden; //is drawing
	
	UI_element * elements;

} UI_layer;

typedef struct _ui_button
{
	int x; //x position of left top
	int y; //y position of left top
	int length;
	int width;
	int clicked;

	void (*Update)(struct _ui_button*);
	void (*Draw)(struct _ui_button*);
} UI_button;

typedef struct _ui_image
{
	//image in bmp? - TBD
	int x; //x position of left top
	int y; //y position of left top
	int width;
	int length;


	void (*Update)(struct _ui_image*);
	void (*Draw)(struct _ui_image*);
} UI_image;

typedef struct _ui_text
{
	//TBD
	void (*Update)(struct _ui_text*);
	void (*Draw)(struct _ui_text*);
} UI_text;

void UpdateLayer(UI_layer*);
void DrawLayer(UI_layer*);
void DestroyLayer(UI_layer*);
void UpdateElement(UI_element*);
void DrawElement(UI_element*);
void DestroyElement(UI_element*);


#endif