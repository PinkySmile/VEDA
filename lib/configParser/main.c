#include "configParser.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

int	main()
{/*
	ParserDict	*buff = malloc(sizeof(*buff));
	ParserDict	*buffs = malloc(sizeof(*buffs));
	ParserArray	arr = {(int[]){10, 89, 48, 10, 0}, 5, ParserIntType};
	float		f = 100;
	
	memset(buff, 0, sizeof(*buff));
	memset(buffs, 0, sizeof(*buffs));
	ParserDict_addElement(buffs, &f, ParserFloatType, "Bidule");
	ParserDict_addElement(buffs, &arr, ParserArrayType, "wesh");
	f = 230;
	ParserDict_addElement(buff, buffs, ParserDictType, "Testt");
	ParserDict_addElement(buff, &f, ParserFloatType, "Test");
	f = 0;
	ParserDict_addElement(buff, &f, ParserFloatType, "Test2");
	f = 10;
	ParserDict_addElement(buff, &f, ParserFloatType, "Test3");
	f = 120;
	ParserDict_addElement(buff, &f, ParserFloatType, "Test4");
	Parser_printElement(buff, ParserDictType, &infos);
	ParserDict_destroy(buff);*/
	ParserInfos	infos = {
		'{',
		'}',
		'{',
		'}',
		',',
		'=',
		"'\"",
		"//",
		"/*",
		"*/",
		false,
		false,
	};
	ParserResult r = Parser_parseFile("test.json", &infos);
	
	if (r.data) {
		Parser_printElement(r.data, r.type, &infos);
		Parser_createFile("test_new.json", r.data, r.type, &infos);
		Parser_destroyData(r.data, r.type);
	} else
		printf("Error: %s\n", r.error);
}