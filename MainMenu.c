#include "MainMenu.h"
#include "defines.h"

void CreateMainMenu(sfRenderWindow* window, Screen* screen)
{
	printf("In main menu\n");
	screen->window = window;

	screen->screenType = 0;

	screen->Update = &UpdateMainMenu;
	screen->Draw = &DrawMainMenu;
	screen->Close = &CloseMainMenu;

	//Load graphics
	screen->fontsCount = 1;
	screen->textCount = 2;
	screen->texturesCount = 1;
	screen->spritesCount = 1;

	screen->fonts = (sfFont**)(malloc(screen->fontsCount * sizeof(sfFont*)));
	screen->text = (sfText**)(malloc(screen->textCount * sizeof(sfText*)));
	screen->textures = (sfTexture**)(malloc(screen->texturesCount * sizeof(sfTexture*)));
	screen->sprites = (sfSprite**)(malloc(screen->spritesCount * sizeof(sfSprite*)));

	screen->textures[0] = sfTexture_createFromFile("Assets/Images/MainMenuBackground.png", NULL);
	screen->fonts[0] = sfFont_createFromFile("Assets/Fonts/SpaceAge.ttf");

	if(CheckLoadedResources(screen))
	{
		printf("FATAL ERROR: Failed loading Main Menu resources!\n");
		CloseMainMenu(screen);
		sfRenderWindow_close(screen->window);
		return;
	}

	FOR(i, 0, screen->textCount)
	{
		screen->text[i] = sfText_create();
	}

	FOR(i, 0, screen->spritesCount)
	{
		screen->sprites[i] = sfSprite_create();
	}

	//SETUP UI
	#define UI_LAYERS screen->UIlayers
	screen->UIlayersCount = 2;
	UI_LAYERS = (UI_layer*)(malloc(screen->UIlayersCount * sizeof(UI_layer)));
	
	SetupBackground(&(UI_LAYERS[0]), screen);
	SetupMenuButtons(&(UI_LAYERS[1]), screen);
}

void UpdateMainMenu(Screen* this)
{
	if(sfKeyboard_isKeyPressed(sfKeyEscape)) //Exit Game
	{
		ChangeScreen(this, -1); //Close App
	}

	if(sfKeyboard_isKeyPressed(sfKeyReturn)) //Enter pressed
	{
		ChangeScreen(this, 1); //Proceed to game screen
	}

	//UPDATE LAYERS
	UpdateMainMenuBackground(&(this->UIlayers[0]), this);
	UpdateMenuButtons(&(this->UIlayers[1]), this);
}

void DrawMainMenu(Screen* this)
{
	//DRAW LAYERS
	DrawMainMenuBackground(&(this->UIlayers[0]), this);
	DrawMenuButtons(&(this->UIlayers[1]), this);
}

void CloseMainMenu(Screen * this)
{
	FOR(i, 0, this->UIlayersCount)
	{
		DestroyLayer(&(this->UIlayers[i]));
	}

	free(this->UIlayers);

	DestroyResources(this);

	printf("closed\n");
}

//Background
void SetupBackground(UI_layer * ui, Screen * screen)
{
	ui->updating = 1; //is updating
	ui->drawing = 1; //is drawing
	
	ui->imageCount = 1;
	ui->buttonCount = 0;
	ui->textCount = 0;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->images[0].x = 0;
	ui->images[0].y = 0;
	ui->images[0].width = SCREEN_WIDTH;
	ui->images[0].height = SCREEN_HEIGHT;
	ui->images[0].sprite = screen->sprites[0];

	sfVector2f scale;
	scale.x = (float)(SCREEN_WIDTH) / 1920.f;
	scale.y = (float)(SCREEN_HEIGHT) / 1080.f;
	sfSprite_setTexture(ui->images[0].sprite, screen->textures[0], sfTrue);
	sfSprite_setScale(ui->images[0].sprite, scale);
}

void UpdateMainMenuBackground(UI_layer* ui, Screen* screen)
{
	if(ui->updating)
	{
		//DO NTH
	}
}

void DrawMainMenuBackground(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawSprite(screen->window, ui->images[0].sprite, NULL);
	}
}

//Buttons
void SetupMenuButtons(UI_layer * ui, Screen * screen)
{
	ui->updating = 1; //is updating
	ui->drawing = 1; //is drawing
	
	ui->imageCount = 0;
	ui->buttonCount = 0;
	ui->textCount = 2;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->text[0].txt = "Start game";
	ui->text[0].text = screen->text[0];
	ui->text[0].color = sfWhite;

	ui->text[1].txt = "exit";
	ui->text[1].text = screen->text[1];
	ui->text[1].color = sfWhite;

	sfText_setFont(ui->text[0].text, screen->fonts[0]);
	sfText_setFont(ui->text[1].text, screen->fonts[0]);

	sfText_setString(ui->text[0].text, ui->text[0].txt);
	sfText_setString(ui->text[1].text, ui->text[1].txt);

	sfText_setCharacterSize(ui->text[0].text, 50);
	sfText_setCharacterSize(ui->text[1].text, 50);

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f;
	sfText_setPosition(ui->text[0].text, newPos);

}

void UpdateMenuButtons(UI_layer* ui, Screen* screen)
{
	if(ui->updating)
	{
		//DO NTH
	}
}

void DrawMenuButtons(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawText(screen->window, ui->text[0].text, NULL);
	}
}
