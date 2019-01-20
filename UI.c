#include <stdio.h>

#include "UI.h"

#define FOR(a, b, c) for(int a = b; a < c; ++a)

void UpdateLayer(UI_layer* layer)
{
	FOR(i, 0, layer->elementCount) //Update each element
	{
		UpdateElement(&layer->elements[i]);
	}
}

void DrawLayer(UI_layer* layer)
{
	FOR(i, 0, layer->elementCount) //Draw each element
	{
		DrawElement(&layer->elements[i]);
	}
}

void DestroyLayer(UI_layer* layer)
{

}

void UpdateElement(UI_element* element)
{
	printf("WORKS!\n");

	/* NOT READY YET
	FOR(i, 0, element->componentCount)
	{
		switch(element->componentTypes[i])
		{
			case 0: //button

				(((UI_button*)(element->components[i]))->Update)((UI_button*)(element->components[i]));
				break;

			case 1: //image

				(((UI_image*)(element->components[i]))->Update)((UI_image*)(element->components[i]));
				break;

			case 2: //text
				
				(((UI_text*)(element->components[i]))->Update)((UI_text*)(element->components[i]));
				break;
		}
	}
	*/
}

void DrawElement(UI_element* element)
{
		FOR(i, 0, element->componentCount)
	{
		switch(element->componentTypes[i])
		{
			case 0: //button

				(((UI_button*)(element->components[i]))->Draw)((UI_button*)(element->components[i]));
				break;

			case 1: //image

				(((UI_image*)(element->components[i]))->Draw)((UI_image*)(element->components[i]));
				break;

			case 2: //text
				
				(((UI_text*)(element->components[i]))->Draw)((UI_text*)(element->components[i]));
				break;
		}
	}
}

void DestroyElement(UI_element* element)
{

}