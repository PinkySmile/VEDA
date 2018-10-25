#include <stdbool.h>
#include <structs.h>
#include <loading.h>
#include <configParser.h>
#include <context.h>
#include <memory.h>
#include <stdio.h>

void	performLongJump(Context *context, contextIssue issue)
{
	longjmp(context->jumpBuffer, issue);
}

bool	getObjectElement(Context *context)
{
	ParserObj	*result = ParserObj_getElement(context->object, context->index);
	char		buffer[sizeof(context->error)];

	memset(context->error, 0, ERROR_BUFFER_SIZE);
	if (result) {
		if (context->expectedType & (1 << result->type)) {
			if (context->useElement(result, context->data, context->error))
				return true;
			else if (context->onUseFail == DISPLAY_WARNING)
				printf(
					"%s: The use callback for field \"%s\" failed (%s)\n",
					WARNING_BEG,
					context->index,
					context->error
				);
			else if (context->onUseFail == LONG_JUMP) {
				strcpy(buffer, context->error);
				sprintf(
					context->error,
					"The use callback for field \"%s\" failed:\n%s",
					context->index,
					buffer
				);
				longjmp(context->jumpBuffer, USAGE_FAILED);
			} else if (context->onUseFail == CALLBACK)
				context->callback(context, USAGE_FAILED);

		} else if (context->onInvalidType == DISPLAY_WARNING)
			printf("%s: Field \"%s\" has an invalid type\n", WARNING_BEG, context->index);
		else if (context->onInvalidType == LONG_JUMP) {
			sprintf(
				context->error,
				"Field '%s' has an invalid type (Got: %s)",
				context->index,
				typeToString(result->type)
			);
			longjmp(context->jumpBuffer, INVALID_TYPE);
		} else if (context->onInvalidType == CALLBACK)
			context->callback(context, INVALID_TYPE);

	} else if (context->onMissing == DISPLAY_WARNING)
		printf("%s: Field \"%s\" is missing\n", WARNING_BEG, context->index);
	else if (context->onMissing == LONG_JUMP) {
		sprintf(
			context->error,
			"The field \"%s\" is missing",
			context->index
		);
		longjmp(context->jumpBuffer, MISSING_PARAMETER);
	} else if (context->onMissing == CALLBACK)
		context->callback(context, MISSING_PARAMETER);

	return (false);
}

bool	createProjectileSprite(ParserObj *obj, void *data, char *err_buffer)
{
	Projectile	*projBuffer = data;

	(void)err_buffer;
	if (obj->type == ParserStringType) {
		projBuffer->sprite = createSprite(
			(Sprite_config) {
				ParserString_toCharStar(obj->data),
				(sfVector2f){1, 1},
				(sfVector2i){0, 0},
				(sfVector2i){0, 0},
			}
		);
		projBuffer->needToDestroySprite = true;
	} else if (obj->type == ParserIntType)
		projBuffer->sprite = *getSprite((game.resources.sprites.length + ParserInt_toInt(obj->data)) % game.resources.sprites.length);
	return (true);
}

bool	getPositiveInteger(ParserObj *obj, void *data, char *err_buffer)
{
	int	*nbr = data;

	if (obj->type == ParserIntType)
		*nbr = ParserInt_toInt(obj->data);
	else if (obj->type == ParserFloatType)
		*nbr = ParserFloat_toFloat(obj->data);
	else
		return (false);
	if (*nbr < 0) {
		sprintf(err_buffer, "%i isn ot a positive number", *nbr);
		return (false);
	}
	return (true);
}

bool	getPositiveFloatingNumber(ParserObj *obj, void *data, char *err_buffer)
{
	float	*nbr = data;

	if (obj->type == ParserIntType)
		*nbr = ParserInt_toInt(obj->data);
	else if (obj->type == ParserFloatType)
		*nbr = ParserFloat_toFloat(obj->data);
	else
		return (false);
	if (*nbr < 0) {
		sprintf(err_buffer, "%.2f isn ot a positive number", *nbr);
		return (false);
	}
	return (true);
}

bool	getInteger(ParserObj *obj, void *data, char *err_buffer)
{
	int	*nbr = data;

	(void)err_buffer;
	if (obj->type == ParserIntType)
		*nbr = ParserInt_toInt(obj->data);
	else if (obj->type == ParserFloatType)
		*nbr = ParserFloat_toFloat(obj->data);
	else
		return (false);
	return (true);
}

bool	getFloatingNumber(ParserObj *obj, void *data, char *err_buffer)
{
	float	*nbr = data;

	(void)err_buffer;
	if (obj->type == ParserIntType)
		*nbr = ParserInt_toInt(obj->data);
	else if (obj->type == ParserFloatType)
		*nbr = ParserFloat_toFloat(obj->data);
	else
		return (false);
	return (true);
}

bool	getUintVector(ParserObj *obj, void *data, char *err_buffer)
{
	Context		context;
	sfVector2u	vector;

	memset(&context, 0, sizeof(context));

	if (setjmp(context.jumpBuffer)) {
		strcpy(err_buffer, context.error);
		return false;
	}

	context.onMissing = LONG_JUMP;
	context.onInvalidType = LONG_JUMP;
	context.onUseFail = LONG_JUMP;

	context.expectedType = ContextIntType | ContextFloatType;
	context.object = obj->data;

	context.data = &vector.x;
	context.index = "x";
	context.useElement = getPositiveInteger;
	getObjectElement(&context);

	context.data = &vector.y;
	context.index = "y";
	context.useElement = getPositiveInteger;
	getObjectElement(&context);

	*(sfVector2u *)data = vector;
	return (true);
}