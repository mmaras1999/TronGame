#include <stdio.h>

#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#include "UI.h"
#include "defines.h"

void DestroyLayer(UI_layer* layer)
{
	free(layer->buttons);
	free(layer->images);
	free(layer->text);
}
