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
	screen->textCount = 2 + 27;
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
	screen->UIlayersCount = 3;
	UI_LAYERS = (UI_layer*)(malloc(screen->UIlayersCount * sizeof(UI_layer)));
	
	SetupBackground(&(UI_LAYERS[0]), screen);
	SetupMenuButtons(&(UI_LAYERS[1]), screen);
	SetupGameSettings(&(UI_LAYERS[2]), screen);
}

void UpdateMainMenu(Screen* this)
{
	//UPDATE LAYERS
	UpdateMainMenuBackground(&(this->UIlayers[0]), this);

	if(sfRenderWindow_isOpen(this->window))
	{
		UpdateMenuButtons(&(this->UIlayers[1]), this);
	}

	if(sfRenderWindow_isOpen(this->window))
	{
		UpdateGameSettings(&(this->UIlayers[2]), this);
	}
}

void DrawMainMenu(Screen* this)
{
	//DRAW LAYERS
	DrawMainMenuBackground(&(this->UIlayers[0]), this);
	DrawMenuButtons(&(this->UIlayers[1]), this);
	DrawGameSettings(&(this->UIlayers[2]), this);
}

void CloseMainMenu(Screen * this)
{
	printf("closing...\n");

	FOR(i, 0, this->UIlayersCount)
	{
		DestroyLayer(&(this->UIlayers[i]));
		printf("Layer %d closed\n", i);
	}

	free(this->UIlayers[2].text[26].txt);
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
	ui->buttonCount = 2;
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

	//START GAME text
	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f - 10;
	sfText_setPosition(ui->text[0].text, newPos);

	//EXIT text
	bounds = sfText_getLocalBounds(ui->text[1].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[1].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f + 90;
	sfText_setPosition(ui->text[1].text, newPos);

	//START GAME button
	bounds = sfText_getGlobalBounds(ui->text[0].text);
	ui->buttons[0].x = bounds.left; //x position of left top
	ui->buttons[0].y = bounds.top; //y position of left top
	ui->buttons[0].width = bounds.width;
	ui->buttons[0].height = bounds.height;
	ui->buttons[0].clicked = 0;
	ui->buttons[0].highlighted = 0;

	//EXIT button
	bounds = sfText_getGlobalBounds(ui->text[1].text);
	ui->buttons[1].x = bounds.left; //x position of left top
	ui->buttons[1].y = bounds.top; //y position of left top
	ui->buttons[1].width = bounds.width;
	ui->buttons[1].height = bounds.height;
	ui->buttons[1].clicked = 0;
	ui->buttons[1].highlighted = 0;
}

void UpdateMenuButtons(UI_layer* ui, Screen* screen)
{
	sfVector2i mousePos = sfMouse_getPositionRenderWindow(screen->window);

	//START GAME button
	#define START_B ui->buttons[0]

	if(sfKeyboard_isKeyPressed(sfKeyReturn)) //Enter pressed
	{
		ui->drawing = 0;
		ui->updating = 0;
		screen->UIlayers[0].drawing = 0;
		screen->UIlayers[0].updating = 0;
		screen->UIlayers[2].drawing = 1;
		screen->UIlayers[2].updating = 1;
		return;
	}

	if(START_B.highlighted)
	{
		if(START_B.x <= mousePos.x && mousePos.x <= START_B.x + START_B.width && START_B.y <= mousePos.y && mousePos.y <= START_B.y + START_B.height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft))
			{
				ui->drawing = 0;
				ui->updating = 0;
				screen->UIlayers[0].drawing = 0;
				screen->UIlayers[0].updating = 0;
				screen->UIlayers[2].drawing = 1;
				screen->UIlayers[2].updating = 1;
				return;
			}
		}
		else
		{
			START_B.highlighted = 0;
			sfText_setFillColor(ui->text[0].text, sfWhite);
		}
	}
	else
	{
		if(START_B.x <= mousePos.x && mousePos.x <= START_B.x + START_B.width && START_B.y <= mousePos.y && mousePos.y <= START_B.y + START_B.height)
		{
			START_B.highlighted = 1;
			sfColor highl = sfColor_fromRGB(200, 200, 200);
			sfText_setFillColor(ui->text[0].text, highl);
		}
	}

	//EXIT button
	#define EXIT_B ui->buttons[1]
	if(sfKeyboard_isKeyPressed(sfKeyEscape)) //Exit Game
	{
		ChangeScreen(screen, -1); //Close App
		return;
	}

	if(EXIT_B.highlighted)
	{
		if(EXIT_B.x <= mousePos.x && mousePos.x <= EXIT_B.x + EXIT_B.width && EXIT_B.y <= mousePos.y && mousePos.y <= EXIT_B.y + EXIT_B.height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft))
			{
				ChangeScreen(screen, -1);
				return;
			}
		}
		else
		{
			EXIT_B.highlighted = 0;
			sfText_setFillColor(ui->text[1].text, sfWhite);
		}
	}
	else
	{
		if(EXIT_B.x <= mousePos.x && mousePos.x <= EXIT_B.x + EXIT_B.width && EXIT_B.y <= mousePos.y && mousePos.y <= EXIT_B.y + EXIT_B.height)
		{
			EXIT_B.highlighted = 1;
			sfColor highl = sfColor_fromRGB(200, 200, 200);
			sfText_setFillColor(ui->text[1].text, highl);
		}
	}
}

void DrawMenuButtons(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawText(screen->window, ui->text[0].text, NULL);
		sfRenderWindow_drawText(screen->window, ui->text[1].text, NULL);
	}
}

//PlayerSettings
void SetupGameSettings(UI_layer* ui, Screen* screen)
{
	ui->mouseReleased = 0;

	screen->manager.paused = 0;
	screen->manager.totalRounds = 2;
	screen->manager.escDown = 1;

	screen->manager.players[0].isHuman = 1;
	screen->manager.players[0].score = 0;
	screen->manager.players[0].KeyRight = sfKeyRight;
	screen->manager.players[0].KeyLeft = sfKeyLeft;
	screen->manager.players[0].keyType = 0;
	screen->manager.players[0].AIlevel = 0;
	screen->manager.players[0].getInput = &getHumanInput;
	screen->manager.players[0].playerID = 0;
	screen->manager.players[0].color = sfBlue;
	screen->manager.players[0].colorID = 0;

	screen->manager.players[1].isHuman = 0;
	screen->manager.players[1].score = 0;
	screen->manager.players[1].KeyRight = sfKeyD;
	screen->manager.players[1].KeyLeft = sfKeyA;
	screen->manager.players[1].keyType = 1;
	screen->manager.players[1].AIlevel = 0;
	screen->manager.players[1].getInput = &getAIInputEasy;
	screen->manager.players[1].playerID = 1;
	screen->manager.players[1].color = sfRed;
	screen->manager.players[1].colorID = 1;

	int textID = 2;

	ui->updating = 0; //is updating
	ui->drawing = 0; //is drawing
	
	ui->imageCount = 0;
	ui->buttonCount = 16;
	ui->textCount = 27;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->text[0].txt = "Game Options";
	ui->text[1].txt = "Player 1";
	ui->text[2].txt = "Player 2";
	ui->text[3].txt = "<<";
	ui->text[4].txt = ">>";
	ui->text[5].txt = "<<";
	ui->text[6].txt = ">>";
	ui->text[7].txt = "Human";
	ui->text[8].txt = "AI";
	ui->text[9].txt = "<<";
	ui->text[10].txt = ">>";
	ui->text[11].txt = "Arrow\n Keys";
	ui->text[12].txt = "Easy";
	ui->text[13].txt = "<<";
	ui->text[14].txt = ">>";
	ui->text[15].txt = "color";
	ui->text[16].txt = "<<";
	ui->text[17].txt = ">>";
	ui->text[18].txt = "color";
	ui->text[19].txt = "<<";
	ui->text[20].txt = ">>";
	ui->text[21].txt = "Play";
	ui->text[22].txt = "Back";
	ui->text[23].txt = "Wins:";
	ui->text[24].txt = "<<";
	ui->text[25].txt = ">>";
	ui->text[26].txt = (char*)(malloc(12 * sizeof(char)));

	sprintf(ui->text[26].txt, "%d", screen->manager.totalRounds);

	FOR(i, 0, ui->textCount)
	{
		ui->text[i].text = screen->text[textID + i];
		ui->text[i].color = sfWhite;

		sfText_setFont(ui->text[i].text, screen->fonts[0]);
		sfText_setString(ui->text[i].text, ui->text[i].txt);
		sfText_setCharacterSize(ui->text[i].text, 35);
	}

	sfText_setCharacterSize(ui->text[0].text, 50);

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	///TEXT:
	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 10.0f;
	sfText_setPosition(ui->text[0].text, newPos);

	//Player 1 text
	bounds = sfText_getLocalBounds(ui->text[1].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[1].text, origin);
	newPos.x = SCREEN_WIDTH / 4.0f + 40;
	newPos.y = SCREEN_HEIGHT / 5.0f;
	sfText_setPosition(ui->text[1].text, newPos);

	//Player 2 text
	bounds = sfText_getLocalBounds(ui->text[2].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[2].text, origin);
	newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 40;
	newPos.y = SCREEN_HEIGHT / 5.0f;
	sfText_setPosition(ui->text[2].text, newPos);

	//Choice box1 text
	{
		bounds = sfText_getLocalBounds(ui->text[7].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[7].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[7].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[3].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[3].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f - 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[3].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[4].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[4].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[4].text, newPos);
	}

	//Choice box2 text
	{
		bounds = sfText_getLocalBounds(ui->text[8].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[8].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[8].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[5].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[5].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[5].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[6].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[6].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f + 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 20;
		sfText_setPosition(ui->text[6].text, newPos);
	}

	//Choice box3 text
	{
		bounds = sfText_getLocalBounds(ui->text[11].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[11].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[11].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[9].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[9].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f - 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[9].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[10].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[10].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[10].text, newPos);
	}

	//Choice box4 text
	{
		bounds = sfText_getLocalBounds(ui->text[12].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[12].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[12].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[13].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[13].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[13].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[14].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[14].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f + 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 100;
		sfText_setPosition(ui->text[14].text, newPos);
	}

	//Choice box5 text
	{
		bounds = sfText_getLocalBounds(ui->text[15].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[15].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[15].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[16].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[16].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f - 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[16].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[17].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[17].text, origin);
		newPos.x = SCREEN_WIDTH / 4.0f + 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[17].text, newPos);

		sfText_setFillColor(ui->text[15].text, sfBlue);
		sfText_setFillColor(ui->text[16].text, sfBlue);
		sfText_setFillColor(ui->text[17].text, sfBlue);
	}

	//Choice box6 text
	{
		bounds = sfText_getLocalBounds(ui->text[18].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[18].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[18].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[19].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[19].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 160;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[19].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[20].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[20].text, origin);
		newPos.x = 3.0f * SCREEN_WIDTH / 4.0f + 90;
		newPos.y = SCREEN_HEIGHT / 4.0f + 180;
		sfText_setPosition(ui->text[20].text, newPos);

		sfText_setFillColor(ui->text[18].text, sfRed);
		sfText_setFillColor(ui->text[19].text, sfRed);
		sfText_setFillColor(ui->text[20].text, sfRed);
	}

	//PLAY text
	bounds = sfText_getLocalBounds(ui->text[21].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[21].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f + 50;
	sfText_setPosition(ui->text[21].text, newPos);

	//BACK text
	bounds = sfText_getLocalBounds(ui->text[22].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[22].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f + 100;
	sfText_setPosition(ui->text[22].text, newPos);

	//ROUNDS text
	bounds = sfText_getLocalBounds(ui->text[23].text);
	origin.x = bounds.left + bounds.width / 2.0f;
	origin.y = bounds.top  + bounds.height / 2.0f;
	sfText_setOrigin(ui->text[23].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f - 150;
	newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
	sfText_setPosition(ui->text[23].text, newPos);

	//ROUND NO text
	{
		bounds = sfText_getLocalBounds(ui->text[26].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[26].text, origin);
		newPos.x = SCREEN_WIDTH / 2.0f + 75;
		newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
		sfText_setPosition(ui->text[26].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[24].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[24].text, origin);
		newPos.x = SCREEN_WIDTH / 2.0f;
		newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
		sfText_setPosition(ui->text[24].text, newPos);

		bounds = sfText_getLocalBounds(ui->text[25].text);
		origin.x = bounds.left + bounds.width / 2.0f;
		origin.y = bounds.top  + bounds.height / 2.0f;
		sfText_setOrigin(ui->text[25].text, origin);
		newPos.x = SCREEN_WIDTH / 2.0f + 150;
		newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
		sfText_setPosition(ui->text[25].text, newPos);
	}

	///BUTTONS:
	//CHOICEBOX 1 LEFT
	bounds = sfText_getGlobalBounds(ui->text[3].text);
	ui->buttons[0].x = bounds.left; //x position of left top
	ui->buttons[0].y = bounds.top; //y position of left top
	ui->buttons[0].width = bounds.width;
	ui->buttons[0].height = bounds.height;
	ui->buttons[0].clicked = 0;
	ui->buttons[0].highlighted = 0;

	//CHOICEBOX 1 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[4].text);
	ui->buttons[1].x = bounds.left; //x position of left top
	ui->buttons[1].y = bounds.top; //y position of left top
	ui->buttons[1].width = bounds.width;
	ui->buttons[1].height = bounds.height;
	ui->buttons[1].clicked = 0;
	ui->buttons[1].highlighted = 0;

	//CHOICEBOX 2 LEFT
	bounds = sfText_getGlobalBounds(ui->text[5].text);
	ui->buttons[2].x = bounds.left; //x position of left top
	ui->buttons[2].y = bounds.top; //y position of left top
	ui->buttons[2].width = bounds.width;
	ui->buttons[2].height = bounds.height;
	ui->buttons[2].clicked = 0;
	ui->buttons[2].highlighted = 0;

	//CHOICEBOX 2 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[6].text);
	ui->buttons[3].x = bounds.left; //x position of left top
	ui->buttons[3].y = bounds.top; //y position of left top
	ui->buttons[3].width = bounds.width;
	ui->buttons[3].height = bounds.height;
	ui->buttons[3].clicked = 0;
	ui->buttons[3].highlighted = 0;

	//CHOICEBOX 3 LEFT
	bounds = sfText_getGlobalBounds(ui->text[9].text);
	ui->buttons[4].x = bounds.left; //x position of left top
	ui->buttons[4].y = bounds.top; //y position of left top
	ui->buttons[4].width = bounds.width;
	ui->buttons[4].height = bounds.height;
	ui->buttons[4].clicked = 0;
	ui->buttons[4].highlighted = 0;

	//CHOICEBOX 3 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[10].text);
	ui->buttons[5].x = bounds.left; //x position of left top
	ui->buttons[5].y = bounds.top; //y position of left top
	ui->buttons[5].width = bounds.width;
	ui->buttons[5].height = bounds.height;
	ui->buttons[5].clicked = 0;
	ui->buttons[5].highlighted = 0;

	//CHOICEBOX 4 LEFT
	bounds = sfText_getGlobalBounds(ui->text[13].text);
	ui->buttons[6].x = bounds.left; //x position of left top
	ui->buttons[6].y = bounds.top; //y position of left top
	ui->buttons[6].width = bounds.width;
	ui->buttons[6].height = bounds.height;
	ui->buttons[6].clicked = 0;
	ui->buttons[6].highlighted = 0;

	//CHOICEBOX 4 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[14].text);
	ui->buttons[7].x = bounds.left; //x position of left top
	ui->buttons[7].y = bounds.top; //y position of left top
	ui->buttons[7].width = bounds.width;
	ui->buttons[7].height = bounds.height;
	ui->buttons[7].clicked = 0;
	ui->buttons[7].highlighted = 0;

	//CHOICEBOX 5 LEFT
	bounds = sfText_getGlobalBounds(ui->text[16].text);
	ui->buttons[8].x = bounds.left; //x position of left top
	ui->buttons[8].y = bounds.top; //y position of left top
	ui->buttons[8].width = bounds.width;
	ui->buttons[8].height = bounds.height;
	ui->buttons[8].clicked = 0;
	ui->buttons[8].highlighted = 0;

	//CHOICEBOX 5 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[17].text);
	ui->buttons[9].x = bounds.left; //x position of left top
	ui->buttons[9].y = bounds.top; //y position of left top
	ui->buttons[9].width = bounds.width;
	ui->buttons[9].height = bounds.height;
	ui->buttons[9].clicked = 0;
	ui->buttons[9].highlighted = 0;

	//CHOICEBOX 6 LEFT
	bounds = sfText_getGlobalBounds(ui->text[19].text);
	ui->buttons[10].x = bounds.left; //x position of left top
	ui->buttons[10].y = bounds.top; //y position of left top
	ui->buttons[10].width = bounds.width;
	ui->buttons[10].height = bounds.height;
	ui->buttons[10].clicked = 0;
	ui->buttons[10].highlighted = 0;

	//CHOICEBOX 6 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[20].text);
	ui->buttons[11].x = bounds.left; //x position of left top
	ui->buttons[11].y = bounds.top; //y position of left top
	ui->buttons[11].width = bounds.width;
	ui->buttons[11].height = bounds.height;
	ui->buttons[11].clicked = 0;
	ui->buttons[11].highlighted = 0;

	//PLAY BUTTON
	bounds = sfText_getGlobalBounds(ui->text[21].text);
	ui->buttons[12].x = bounds.left; //x position of left top
	ui->buttons[12].y = bounds.top; //y position of left top
	ui->buttons[12].width = bounds.width;
	ui->buttons[12].height = bounds.height;
	ui->buttons[12].clicked = 0;
	ui->buttons[12].highlighted = 0;

	//PLAY BUTTON
	bounds = sfText_getGlobalBounds(ui->text[22].text);
	ui->buttons[13].x = bounds.left; //x position of left top
	ui->buttons[13].y = bounds.top; //y position of left top
	ui->buttons[13].width = bounds.width;
	ui->buttons[13].height = bounds.height;
	ui->buttons[13].clicked = 0;
	ui->buttons[13].highlighted = 0;

	//CHECKBOX 7 LEFT
	bounds = sfText_getGlobalBounds(ui->text[24].text);
	ui->buttons[14].x = bounds.left; //x position of left top
	ui->buttons[14].y = bounds.top; //y position of left top
	ui->buttons[14].width = bounds.width;
	ui->buttons[14].height = bounds.height;
	ui->buttons[14].clicked = 0;
	ui->buttons[14].highlighted = 0;

	//CHECKBOX 7 RIGHT
	bounds = sfText_getGlobalBounds(ui->text[25].text);
	ui->buttons[15].x = bounds.left; //x position of left top
	ui->buttons[15].y = bounds.top; //y position of left top
	ui->buttons[15].width = bounds.width;
	ui->buttons[15].height = bounds.height;
	ui->buttons[15].clicked = 0;
	ui->buttons[15].highlighted = 0;
}

void UpdateGameSettings(UI_layer* ui, Screen* screen)
{
	//choices:
	char* opt1[2] = {"AI", "Human"};
	char* humanOpt2[2] = {"Arrow\n Keys", "A & D"};
	char* AIOpt2[2] = {"Easy", "Hard"};
	sfColor colors[6] = { sfBlue, sfRed, sfGreen, sfMagenta, sfCyan, sfYellow };

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	sfVector2i mousePos = sfMouse_getPositionRenderWindow(screen->window);

	if(!sfMouse_isButtonPressed(sfMouseLeft))
	{
		ui->mouseReleased = 1;
	}

	if(sfKeyboard_isKeyPressed(sfKeyEscape)) //Exit Game
	{
		ChangeScreen(screen, -1); //Close App
		return;
	}

	//SETTINGS
	{
		if(ui->buttons[0].x <= mousePos.x && mousePos.x <= ui->buttons[0].x + ui->buttons[0].width && ui->buttons[0].y <= mousePos.y && mousePos.y <= ui->buttons[0].y + ui->buttons[0].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;
			
				screen->manager.players[0].isHuman = (screen->manager.players[0].isHuman + 1) & 1;

				sfText_setString(ui->text[7].text, opt1[screen->manager.players[0].isHuman]);

				if(screen->manager.players[0].isHuman)
				{
					sfText_setString(ui->text[11].text, humanOpt2[screen->manager.players[0].keyType]);
					screen->manager.players[0].getInput = &getHumanInput;
				}
				else
				{
					sfText_setString(ui->text[11].text, AIOpt2[screen->manager.players[0].AIlevel]);

					if(screen->manager.players[0].AIlevel)
					{
						screen->manager.players[0].getInput = &getAIInputHard;
					}
					else
					{
						screen->manager.players[0].getInput = &getAIInputEasy;
					}
				}

				bounds = sfText_getLocalBounds(ui->text[7].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[7].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 20;
				sfText_setPosition(ui->text[7].text, newPos);

				bounds = sfText_getLocalBounds(ui->text[11].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[11].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[11].text, newPos);
			}
		}

		if(ui->buttons[1].x <= mousePos.x && mousePos.x <= ui->buttons[1].x + ui->buttons[1].width && ui->buttons[1].y <= mousePos.y && mousePos.y <= ui->buttons[1].y + ui->buttons[1].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;
			
				screen->manager.players[0].isHuman = (screen->manager.players[0].isHuman + 1) & 1;

				sfText_setString(ui->text[7].text, opt1[screen->manager.players[0].isHuman]);

				if(screen->manager.players[0].isHuman)
				{
					sfText_setString(ui->text[11].text, humanOpt2[screen->manager.players[0].keyType]);
					screen->manager.players[0].getInput = &getHumanInput;
				}
				else
				{
					sfText_setString(ui->text[11].text, AIOpt2[screen->manager.players[0].AIlevel]);

					if(screen->manager.players[0].AIlevel)
					{
						screen->manager.players[0].getInput = &getAIInputHard;
					}
					else
					{
						screen->manager.players[0].getInput = &getAIInputEasy;
					}
				}

				

				bounds = sfText_getLocalBounds(ui->text[7].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[7].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 20;
				sfText_setPosition(ui->text[7].text, newPos);

				bounds = sfText_getLocalBounds(ui->text[11].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[11].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[11].text, newPos);
			}
		}

		if(ui->buttons[2].x <= mousePos.x && mousePos.x <= ui->buttons[2].x + ui->buttons[2].width && ui->buttons[2].y <= mousePos.y && mousePos.y <= ui->buttons[2].y + ui->buttons[2].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;
			
				screen->manager.players[1].isHuman = (screen->manager.players[1].isHuman + 1) & 1;

				sfText_setString(ui->text[8].text, opt1[screen->manager.players[1].isHuman]);

				if(screen->manager.players[1].isHuman)
				{
					sfText_setString(ui->text[12].text, humanOpt2[screen->manager.players[1].keyType]);
					screen->manager.players[1].getInput = &getHumanInput;
				}
				else
				{
					sfText_setString(ui->text[12].text, AIOpt2[screen->manager.players[1].AIlevel]);

					if(screen->manager.players[1].AIlevel)
					{
						screen->manager.players[1].getInput = &getAIInputHard;
					}
					else
					{
						screen->manager.players[1].getInput = &getAIInputEasy;
					}
				}

				bounds = sfText_getLocalBounds(ui->text[8].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[8].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 20;
				sfText_setPosition(ui->text[8].text, newPos);

				bounds = sfText_getLocalBounds(ui->text[12].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[12].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[12].text, newPos);
			}
		}

		if(ui->buttons[3].x <= mousePos.x && mousePos.x <= ui->buttons[3].x + ui->buttons[3].width && ui->buttons[3].y <= mousePos.y && mousePos.y <= ui->buttons[3].y + ui->buttons[3].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;
			
				screen->manager.players[1].isHuman = (screen->manager.players[1].isHuman + 1) & 1;

				sfText_setString(ui->text[8].text, opt1[screen->manager.players[1].isHuman]);

				if(screen->manager.players[1].isHuman)
				{
					sfText_setString(ui->text[12].text, humanOpt2[screen->manager.players[1].keyType]);
					screen->manager.players[1].getInput = &getHumanInput;
				}
				else
				{
					sfText_setString(ui->text[12].text, AIOpt2[screen->manager.players[1].AIlevel]);

					if(screen->manager.players[1].AIlevel)
					{
						screen->manager.players[1].getInput = &getAIInputHard;
					}
					else
					{
						screen->manager.players[1].getInput = &getAIInputEasy;
					}
				}

				bounds = sfText_getLocalBounds(ui->text[8].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[8].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 20;
				sfText_setPosition(ui->text[8].text, newPos);

				bounds = sfText_getLocalBounds(ui->text[12].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[12].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[12].text, newPos);
			}
		}

		if(ui->buttons[4].x <= mousePos.x && mousePos.x <= ui->buttons[4].x + ui->buttons[4].width && ui->buttons[4].y <= mousePos.y && mousePos.y <= ui->buttons[4].y + ui->buttons[4].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				if(screen->manager.players[0].isHuman)
				{
					screen->manager.players[0].keyType = (screen->manager.players[0].keyType + 1) & 1;

					if(!screen->manager.players[0].keyType)
					{
						screen->manager.players[0].KeyLeft = sfKeyLeft;
						screen->manager.players[0].KeyRight = sfKeyRight;
					}
					else
					{
						screen->manager.players[0].KeyLeft = sfKeyA;
						screen->manager.players[0].KeyRight = sfKeyD;
					}

					sfText_setString(ui->text[11].text, humanOpt2[screen->manager.players[0].keyType]);
				}
				else
				{
					screen->manager.players[0].AIlevel = (screen->manager.players[0].AIlevel + 1) & 1;

					if(!screen->manager.players[0].AIlevel)
					{
						screen->manager.players[0].getInput = &getAIInputEasy;
					}
					else
					{
						screen->manager.players[0].getInput = &getAIInputHard;
					}

					sfText_setString(ui->text[11].text, AIOpt2[screen->manager.players[0].AIlevel]);
				}

				bounds = sfText_getLocalBounds(ui->text[11].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[11].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[11].text, newPos);
			}
		}

		if(ui->buttons[5].x <= mousePos.x && mousePos.x <= ui->buttons[5].x + ui->buttons[5].width && ui->buttons[5].y <= mousePos.y && mousePos.y <= ui->buttons[5].y + ui->buttons[5].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				if(screen->manager.players[0].isHuman)
				{
					screen->manager.players[0].keyType = (screen->manager.players[0].keyType + 1) & 1;

					if(!screen->manager.players[0].keyType)
					{
						screen->manager.players[0].KeyLeft = sfKeyLeft;
						screen->manager.players[0].KeyRight = sfKeyRight;
					}
					else
					{
						screen->manager.players[0].KeyLeft = sfKeyA;
						screen->manager.players[0].KeyRight = sfKeyD;
					}

					sfText_setString(ui->text[11].text, humanOpt2[screen->manager.players[0].keyType]);
				}
				else
				{
					screen->manager.players[0].AIlevel = (screen->manager.players[0].AIlevel + 1) & 1;

					if(!screen->manager.players[0].AIlevel)
					{
						screen->manager.players[0].getInput = &getAIInputEasy;
					}
					else
					{
						screen->manager.players[0].getInput = &getAIInputHard;
					}

					sfText_setString(ui->text[11].text, AIOpt2[screen->manager.players[0].AIlevel]);
				}

				bounds = sfText_getLocalBounds(ui->text[11].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[11].text, origin);
				newPos.x = SCREEN_WIDTH / 4.0f + 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[11].text, newPos);
			}
		}

		if(ui->buttons[6].x <= mousePos.x && mousePos.x <= ui->buttons[6].x + ui->buttons[6].width && ui->buttons[6].y <= mousePos.y && mousePos.y <= ui->buttons[6].y + ui->buttons[6].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				if(screen->manager.players[1].isHuman)
				{
					screen->manager.players[1].keyType = (screen->manager.players[1].keyType + 1) & 1;

					if(!screen->manager.players[1].keyType)
					{
						screen->manager.players[1].KeyLeft = sfKeyLeft;
						screen->manager.players[1].KeyRight = sfKeyRight;
					}
					else
					{
						screen->manager.players[1].KeyLeft = sfKeyA;
						screen->manager.players[1].KeyRight = sfKeyD;
					}

					sfText_setString(ui->text[12].text, humanOpt2[screen->manager.players[1].keyType]);
				}
				else
				{
					screen->manager.players[1].AIlevel = (screen->manager.players[1].AIlevel + 1) & 1;

					if(!screen->manager.players[1].AIlevel)
					{
						screen->manager.players[1].getInput = &getAIInputEasy;
					}
					else
					{
						screen->manager.players[1].getInput = &getAIInputHard;
					}

					sfText_setString(ui->text[12].text, AIOpt2[screen->manager.players[1].AIlevel]);
				}

				bounds = sfText_getLocalBounds(ui->text[12].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[12].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[12].text, newPos);
			}
		}

		if(ui->buttons[7].x <= mousePos.x && mousePos.x <= ui->buttons[7].x + ui->buttons[7].width && ui->buttons[7].y <= mousePos.y && mousePos.y <= ui->buttons[7].y + ui->buttons[7].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				if(screen->manager.players[1].isHuman)
				{
					screen->manager.players[1].keyType = (screen->manager.players[1].keyType + 1) & 1;

					if(!screen->manager.players[1].keyType)
					{
						screen->manager.players[1].KeyLeft = sfKeyLeft;
						screen->manager.players[1].KeyRight = sfKeyRight;
					}
					else
					{
						screen->manager.players[1].KeyLeft = sfKeyA;
						screen->manager.players[1].KeyRight = sfKeyD;
					}

					sfText_setString(ui->text[12].text, humanOpt2[screen->manager.players[1].keyType]);
				}
				else
				{
					screen->manager.players[1].AIlevel = (screen->manager.players[1].AIlevel + 1) & 1;

					if(!screen->manager.players[1].AIlevel)
					{
						screen->manager.players[1].getInput = &getAIInputEasy;
					}
					else
					{
						screen->manager.players[1].getInput = &getAIInputHard;
					}

					sfText_setString(ui->text[12].text, AIOpt2[screen->manager.players[1].AIlevel]);
				}
						
				bounds = sfText_getLocalBounds(ui->text[12].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[12].text, origin);
				newPos.x = 3.0f * SCREEN_WIDTH / 4.0f - 35;
				newPos.y = SCREEN_HEIGHT / 4.0f + 100;
				sfText_setPosition(ui->text[12].text, newPos);
			}
		}

		if(ui->buttons[8].x <= mousePos.x && mousePos.x <= ui->buttons[8].x + ui->buttons[8].width && ui->buttons[8].y <= mousePos.y && mousePos.y <= ui->buttons[8].y + ui->buttons[8].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				screen->manager.players[0].colorID = (screen->manager.players[0].colorID + 5) % 6;

				sfText_setFillColor(ui->text[15].text, colors[screen->manager.players[0].colorID]);
				sfText_setFillColor(ui->text[16].text, colors[screen->manager.players[0].colorID]);
				sfText_setFillColor(ui->text[17].text, colors[screen->manager.players[0].colorID]);

				screen->manager.players[0].color = colors[screen->manager.players[0].colorID];
			}
		}

		if(ui->buttons[9].x <= mousePos.x && mousePos.x <= ui->buttons[9].x + ui->buttons[9].width && ui->buttons[9].y <= mousePos.y && mousePos.y <= ui->buttons[9].y + ui->buttons[9].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;
			
				screen->manager.players[0].colorID = (screen->manager.players[0].colorID + 1) % 6;

				sfText_setFillColor(ui->text[15].text, colors[screen->manager.players[0].colorID]);
				sfText_setFillColor(ui->text[16].text, colors[screen->manager.players[0].colorID]);
				sfText_setFillColor(ui->text[17].text, colors[screen->manager.players[0].colorID]);

				screen->manager.players[0].color = colors[screen->manager.players[0].colorID];
			}
		}

		if(ui->buttons[10].x <= mousePos.x && mousePos.x <= ui->buttons[10].x + ui->buttons[10].width && ui->buttons[10].y <= mousePos.y && mousePos.y <= ui->buttons[10].y + ui->buttons[10].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				
				screen->manager.players[1].colorID = (screen->manager.players[1].colorID + 5) % 6;

				sfText_setFillColor(ui->text[18].text, colors[screen->manager.players[1].colorID]);
				sfText_setFillColor(ui->text[19].text, colors[screen->manager.players[1].colorID]);
				sfText_setFillColor(ui->text[20].text, colors[screen->manager.players[1].colorID]);

				screen->manager.players[1].color = colors[screen->manager.players[1].colorID];
			}
		}

		if(ui->buttons[11].x <= mousePos.x && mousePos.x <= ui->buttons[11].x + ui->buttons[11].width && ui->buttons[11].y <= mousePos.y && mousePos.y <= ui->buttons[11].y + ui->buttons[11].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				screen->manager.players[1].colorID = (screen->manager.players[1].colorID + 1) % 6;

				sfText_setFillColor(ui->text[18].text, colors[screen->manager.players[1].colorID]);
				sfText_setFillColor(ui->text[19].text, colors[screen->manager.players[1].colorID]);
				sfText_setFillColor(ui->text[20].text, colors[screen->manager.players[1].colorID]);

				screen->manager.players[1].color = colors[screen->manager.players[1].colorID];
			}
		}

		if(ui->buttons[14].x <= mousePos.x && mousePos.x <= ui->buttons[14].x + ui->buttons[14].width && ui->buttons[14].y <= mousePos.y && mousePos.y <= ui->buttons[14].y + ui->buttons[14].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				--screen->manager.totalRounds;

				if(screen->manager.totalRounds < 1)
				{
					screen->manager.totalRounds = 1;
				}

				sprintf(ui->text[26].txt, "%d", screen->manager.totalRounds);

				sfText_setString(ui->text[26].text, ui->text[26].txt);

				bounds = sfText_getLocalBounds(ui->text[26].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[26].text, origin);
				newPos.x = SCREEN_WIDTH / 2.0f + 75;
				newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
				sfText_setPosition(ui->text[26].text, newPos);
			}
		}

		if(ui->buttons[15].x <= mousePos.x && mousePos.x <= ui->buttons[15].x + ui->buttons[15].width && ui->buttons[15].y <= mousePos.y && mousePos.y <= ui->buttons[15].y + ui->buttons[15].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft) && ui->mouseReleased)
			{
				ui->mouseReleased = 0;

				++screen->manager.totalRounds;

				sprintf(ui->text[26].txt, "%d", screen->manager.totalRounds);

				sfText_setString(ui->text[26].text, ui->text[26].txt);

				bounds = sfText_getLocalBounds(ui->text[26].text);
				origin.x = bounds.left + bounds.width / 2.0f;
				origin.y = bounds.top  + bounds.height / 2.0f;
				sfText_setOrigin(ui->text[26].text, origin);
				newPos.x = SCREEN_WIDTH / 2.0f + 75;
				newPos.y = 4.0f * SCREEN_HEIGHT / 5.0f - 100;
				sfText_setPosition(ui->text[26].text, newPos);
			}
		}
	}

	if(ui->buttons[12].highlighted)
	{
		if(ui->buttons[12].x <= mousePos.x && mousePos.x <= ui->buttons[12].x + ui->buttons[12].width && ui->buttons[12].y <= mousePos.y && mousePos.y <= ui->buttons[12].y + ui->buttons[12].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft))
			{
				ChangeScreen(screen, 1);
				return;
			}
		}
		else
		{
			ui->buttons[12].highlighted = 0;
			sfText_setFillColor(ui->text[21].text, sfWhite);
		}
	}
	else
	{
		if(ui->buttons[12].x <= mousePos.x && mousePos.x <= ui->buttons[12].x + ui->buttons[12].width && ui->buttons[12].y <= mousePos.y && mousePos.y <= ui->buttons[12].y + ui->buttons[12].height)
		{
			ui->buttons[12].highlighted = 1;
			sfColor highl = sfColor_fromRGB(200, 200, 200);
			sfText_setFillColor(ui->text[21].text, highl);
		}
	}

	if(ui->buttons[13].highlighted)
	{
		if(ui->buttons[13].x <= mousePos.x && mousePos.x <= ui->buttons[13].x + ui->buttons[13].width && ui->buttons[13].y <= mousePos.y && mousePos.y <= ui->buttons[13].y + ui->buttons[13].height)
		{
			if(sfMouse_isButtonPressed(sfMouseLeft))
			{
				ui->updating = 0;
				ui->drawing = 0;
				screen->UIlayers[0].drawing = 1;
				screen->UIlayers[0].updating = 1;
				screen->UIlayers[1].drawing = 1;
				screen->UIlayers[1].updating = 1;
				return;
			}
		}
		else
		{
			ui->buttons[13].highlighted = 0;
			sfText_setFillColor(ui->text[22].text, sfWhite);
		}
	}
	else
	{
		if(ui->buttons[13].x <= mousePos.x && mousePos.x <= ui->buttons[13].x + ui->buttons[13].width && ui->buttons[13].y <= mousePos.y && mousePos.y <= ui->buttons[13].y + ui->buttons[13].height)
		{
			ui->buttons[13].highlighted = 1;
			sfColor highl = sfColor_fromRGB(200, 200, 200);
			sfText_setFillColor(ui->text[22].text, highl);
		}
	}
}

void DrawGameSettings(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		FOR(i, 0, ui->textCount)
		{
			sfRenderWindow_drawText(screen->window, ui->text[i].text, NULL);
		}
	}
}
