#include <SFML/Graphics.h>
#include <malloc.h>
#include "concatf.h"
#include "structs.h"
#include "graphic.h"

void	displayObject(Object *obj)
{
	sfIntRect	rec = {0, 0, 16, 16};
	char		*buffer = NULL;
	sfVector2i	cam = game.state.cameraPos;

	if (!getSprite(OBJECTS)->sprite) {
		sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(
			game.resources.rectangle,
			(sfColor){
				((obj->id * 10) >> 16) * 20 % 256,
				((obj->id * 10) >> 8) * 10 % 256,
				obj->id * 10 % 256,
				255
			}
		);
		rect(obj->pos.x + cam.x, obj->pos.y + cam.y, 16, 16);
	} else {
		rec.left = (obj->id - 1) * 16 % 640;
		rec.top = (obj->id - 1) * 16 / 640;
		sfSprite_setTextureRect(getSprite(OBJECTS)->sprite, rec);
		image(getSprite(OBJECTS)->sprite, obj->pos.x + cam.x, obj->pos.y + cam.y, 16, 16);
	}
	if (game.debug) {
		sfText_setCharacterSize(game.resources.text, 15);
		sfText_setColor(game.resources.text,
			(sfColor){
				obj->layer % 2 == 0 ? 255 : 0,
				obj->layer % 3 == 0 ? 255 : 0,
				obj->layer % 4 == 0 ? 255 : 0,
				200
			}
		);
		buffer = concatf("%i", obj->id);
		text(buffer, obj->pos.x + cam.x, obj->pos.y + cam.y, false);
		free(buffer);
	}	
}

void	displayLowerLayer()
{
	Object		*objects = game.state.loadedMap.objects;
	sfVector2i	cam = game.state.cameraPos;

	if (!objects)
		return;
	for (int i = 0; objects[i].layer; i++) {
		//Check if the object is inside the window and on the good layer
		for (int j = 0; j < game.state.characters.length; j++)
			execAction(objects[i], getCharacter(j));
		if (objects[i].layer == 1 && isObjectInWindow(objects[i]))
			displayObject(&objects[i]);
	}
}

void	displayUpperLayer()
{
	Object		*map = game.state.loadedMap.objects;
	sfVector2i	cam = game.state.cameraPos;
	bool		newLayer = true;

	if (!map)
		return;
	for (int nextLayer, layer = 2; newLayer; layer = nextLayer) {
		newLayer = false;
		nextLayer = map->layer;
		for (int i = 0; map[i].layer; i++) {
			//Check if the object is inside the window and on the good layer
			if (map[i].layer == layer && isObjectInWindow(map[i]))
				displayObject(&map[i]);

			/*Select the current layer if it is lower than the currently selected layer
			 *This is here to skip all the empty layers*/
			nextLayer = map[i].layer > layer && map[i].layer < nextLayer ? map[i].layer : nextLayer;

			//This boolean represent whether there are still objects to render
			newLayer = newLayer || map[i].layer > layer;
		}
	}
	for (int i = 0; game.debug && map[i].layer; i++) {
		if (isObjectInWindow(map[i])) {
			if (map[i].solid) {
				sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor) {255, 0, 255, 125});
				rect(map[i].pos.x + cam.x + 1, map[i].pos.y + cam.y + 1, 14, 14);
			} else if (getSprite(MUSICS)->sprite && map[i].action == CHANGE_MUSIC) {
				image(getSprite(MUSICS)->sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			} else if (map[i].action == DEAL_DAMAGES) {
				sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor) {0, 0, 255, 155});
				rect(map[i].pos.x + cam.x + 3, map[i].pos.y + cam.y + 3, 10, 10);
			} else if (getSprite(CUTSCENE)->sprite && map[i].action == LAUNCH_CUTSCENE)
				image(getSprite(CUTSCENE)->sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
		}
	}
}
