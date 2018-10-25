#include <stdio.h>
#include <structs.h>
#include <concatf.h>
#include <setjmp.h>
#include <utils.h>
#include <memory.h>
#include <malloc.h>
#include <loading.h>
#include <context.h>

Array	loadProjectiles(char *path)
{
	ParserResult	result = Parser_parseFile(path, JSON_TO_ARRAY);
	int		i = 0;
	char		*buffer;
	ParserObj	*currProjectile;
	sfVector2f	scaling = game.settings.baseScale;
	sfVector2u	buf;
	Projectile	projBuffer;
	Array		array;
	Context		context;

	memset(&context, 0, sizeof(context));
	printf("%s: Loading projectiles in file %s\n", INFO_BEG, path);

	if (result.error) {
		printf("%s: %s\n", ERROR_BEG, result.error);
		result.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, result.error);
		dispMsg("Battle Error", result.error, 0);
		free(result.error);
		return (Array){NULL, -1};

	} else if (result.type != ParserArrayType) {
		printf("%s: %s: Invalid type\n", ERROR_BEG, path);
		buffer = concatf("Error: %s: Invalid type found in the file\n", path);
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};

	} else if (((ParserArray *)result.data)->type != ParserObjType) {
		printf("%s: %s: Invalid type\n", ERROR_BEG, path);
		buffer = concatf("Error: %s: Array contains invalid data\n", path);
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	}

	if (setjmp(context.jumpBuffer)) {
		Parser_destroyData(result.data, result.type);
		printf("%s: %s: %s\n", ERROR_BEG, path, context.error);
		buffer = concatf(
			"Error: File '%s' contains invalid battle data:\nProjectile number %i\n%s\n",
			path,
			i + 1,
			context.error
		);
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		return (Array){NULL, -1};
	}

	context.onMissing = DISPLAY_WARNING;
	context.onInvalidType = LONG_JUMP;
	context.onUseFail = LONG_JUMP;
	array.length = ((ParserArray *)result.data)->length;
	array.content = malloc(array.length * sizeof(Projectile));
	memset(array.content, 0, array.length * sizeof(Projectile));
	for (; i < array.length; i++) {
		currProjectile = ParserArray_getElement(result.data, i);
		memset(&projBuffer, 0, sizeof(projBuffer));
		context.object = currProjectile;

		context.data = &projBuffer;
		context.index = "sprite_sheet";
		context.useElement = loadSprite;
		context.expectedType = ContextIntType | ContextStringType;
		getObjectElement(&context);

		context.data = &projBuffer.sprite.rect.width;
		context.index = "sprite_size";
		context.useElement = getUintVector;
		context.expectedType = ContextObjType;
		getObjectElement(&context);

		context.data = &buf;
		context.index = "bullet_size";
		context.useElement = getUintVector;
		context.expectedType = ContextObjType;
		if (getObjectElement(&context)) {
			scaling.x = game.settings.baseScale.x * buf.x / (float)projBuffer.sprite.rect.width;
			scaling.y = game.settings.baseScale.y * buf.y / (float)projBuffer.sprite.rect.height;
			if (projBuffer.sprite.sprite)
				sfSprite_setScale(projBuffer.sprite.sprite, scaling);
		}

		context.data = &projBuffer.hitbox;
		context.index = "hitbox_size";
		context.useElement = getUintVector;
		context.expectedType = ContextObjType;
		getObjectElement(&context);

		context.data = &projBuffer.speed;
		context.index = "base_speed";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		getObjectElement(&context);

		context.data = &projBuffer.minSpeed;
		context.index = "min_speed";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		if (!getObjectElement(&context))
			projBuffer.minSpeed = -1000;

		context.data = &projBuffer.maxSpeed;
		context.index = "max_speed";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		if (!getObjectElement(&context))
			projBuffer.maxSpeed = 1000;

		if (projBuffer.maxSpeed < projBuffer.minSpeed) {
			sprintf(
				context.error,
				"Maximum speed is lower than minimum speed (%f < %f)",
				projBuffer.maxSpeed,
				projBuffer.minSpeed
			);
			longjmp(context.jumpBuffer, 4);
		}

		context.data = &projBuffer.acceleration;
		context.index = "base_acceleration";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		getObjectElement(&context);

		context.data = &projBuffer.rotaSpeed;
		context.index = "rotation_speed";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		getObjectElement(&context);

		context.data = &projBuffer.angle;
		context.index = "base_angle";
		context.useElement = getFloatingNumber;
		context.expectedType = ContextFloatType | ContextIntType;
		getObjectElement(&context);

		context.data = &projBuffer.animSpeed;
		context.index = "animation_speed";
		context.useElement = getInteger;
		context.expectedType = ContextFloatType | ContextIntType;
		getObjectElement(&context);

		projBuffer.bankID = i;
		if (projBuffer.sprite.sprite)
			sfSprite_setOrigin(
				projBuffer.sprite.sprite,
				(sfVector2f) {
					(float)projBuffer.sprite.rect.width / 2,
					(float)projBuffer.sprite.rect.height / 2
				}
			);

		((Projectile *)array.content)[i] = projBuffer;
	}
	Parser_destroyData(result.data, result.type);
	return array;
}
