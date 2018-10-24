#ifndef __PARSING_HEADER_
#define __PARSING_HEADER_

#include <stdbool.h>

typedef enum {
	ParserBooleanType,
	ParserStringType,
	ParserFloatType,
	ParserArrayType,
	ParserObjType,
	ParserListType,
	ParserIntType,
	ParserNullType,
	NbOfParserTypes,
} ParserTypes;

typedef bool    ParserBoolean;
typedef float   ParserFloat;
typedef int     ParserInt;

typedef struct {
	char	*content;
	int	length;
} ParserString;	//String

typedef struct StructParserObj ParserObj;
struct StructParserObj {
	char		*index;
	void		*data;
	ParserTypes	type;
	ParserObj	*next;
	ParserObj	*prev;
};

typedef struct StructParserList ParserList;
struct StructParserList {
	void		*data;
	ParserTypes	type;
	ParserList	*next;
	ParserList	*prev;
};		//Double linked list

typedef struct {
	void		*content;
	int		length;
	ParserTypes	type;
	ParserList	*list;
} ParserArray;	//An array

typedef struct {
	void		*data;	//This is NULL when something went wrong
	ParserTypes	type;
	char		*error;	/*This is NULL if everything went good
				  (So if data is NULL, error shouldn't be)
				  This is the error found when parsing the file or string*/
} ParserResult;

typedef struct {
	char	objOpen;              //The obj opening character    (by default it's '{')
	char	objClose;             //The obj closing character    (by default it's '}')
	char	arrOpen;              //The array opening character   (by default it's '[')
	char	arrClose;             //The array opening character   (by default it's ']')
	char	separator;            //The separator character       (by default it's ',')
	char	eqChar;               //The equal char                (by default it's ':')
	char	*strChar;             //The string chars              (by default it's '"' and ''')
	char	*singLineComment;     //Single line comments
	char	*multLineCommentStart;//Multi line comments start.
	char	*multLineCommentEnd;  //Multi line comments end.
	bool	listToArray;          /*By default, arrays are converted to linked lists.
                                        You can make lists become arrays. This is not recommended
                                        since lists containing different types will not be converted.
                                        You can still try to convert a list to an array later with
                                        ParserList_convertToArray(list)*/
	bool	compact;              //If true, will take the least space as possible (no spaces, \n, ...)
} ParserInfos;

//This is a default configuration to parse some json files
#define JSON_COMPACT		((ParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", false, true}})
#define JSON_NOT_COMPACT	((ParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", false, false}})
#define JSON_TO_ARRAY		((ParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", true, false}})

/////////////////////
//Parsing functions//
/////////////////////

//////////////////////////////////////////////////////////
//              Parse a file with it's path             //
//If NULL is passed instead of an info structure, takes //
//The default structure info.                           //
//                                                      //
//So a call to  Parser_parseFile(path, NULL) is like    //
//a call to     Parser_parseFile(path, JSON_COMPACT)    //
//////////////////////////////////////////////////////////
ParserResult	Parser_parseFile(char *path, ParserInfos *infos);

//////////////////////////////////////////////////////////
//           Parse a NULL terminated string             //
//If NULL is passed instead of an info structure, takes //
//the default structure info.                           //
//                                                      //
//So a call to  Parser_parseString(path, NULL) is like  //
//a call to     Parser_parseString(path, JSON_COMPACT)  //
//////////////////////////////////////////////////////////
ParserResult	Parser_parseString(char *string, ParserInfos *infos);

//////////////////////////////////////////////////////////
//            Dumps the structure to a file             //
//If NULL is passed instead of an info structure, takes //
//The default structure info.                           //
//                                                      //
//So a call to  Parser_parseFile(path, NULL) is like    //
//a call to     Parser_parseFile(path, JSON_COMPACT)    //
//////////////////////////////////////////////////////////
bool	Parser_createFile(char *path, void *data, ParserTypes type, ParserInfos *infos);

//////////////////////////////////////////////////////////
//           Create a NULL terminated string            //
//If NULL is passed instead of an info structure, takes //
//the default structure info.                           //
//                                                      //
//So a call to  Parser_createString(path, NULL) is like //
//a call to     Parser_createString(path, JSON_COMPACT) //
//         If an error occurred, returns NULL           //
//////////////////////////////////////////////////////////
char	*Parser_createString(void *data, ParserTypes type, ParserInfos *infos);



/////////////////////////////
//Data management functions//
/////////////////////////////

//////////////////////////////////////////////////////////
//        Destroys a data according to its type         //
//////////////////////////////////////////////////////////
void	Parser_destroyData(void *data, ParserTypes type);

//////////////////////////////////////////////////////////
//            Gets the size of a given type             //
//////////////////////////////////////////////////////////
int	getSizeOf(ParserTypes type);

//////////////////////////////////////////////////////////
//Copy bytes of data and create a new buffer to store it//
//////////////////////////////////////////////////////////
void	*copyData(void *data, ParserTypes type);

//////////////////////////////////////////////////////////
//Returns a string describing the type. Don't free it ! //
//////////////////////////////////////////////////////////
char	*typeToString(ParserTypes type);

//////////////////////////////////////////////////////////
//                   Displays a data                    //
//////////////////////////////////////////////////////////
void	Parser_printElement(void *data, ParserTypes type, ParserInfos *infos);



/////////////////////////////////////////////////////
//          Array management functions             //
// /!\ These arrays are not NULL terminated !  /!\ //
//A 0 length array will see his pointer set to NULL//
//TLDR: Don't try to access < 1 length arrays      //
/////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//Returns a pointer to the element at the index in the  //
//array. If not in the array range, returns NULL.       //
//////////////////////////////////////////////////////////
void	*ParserArray_getElement(ParserArray *array, int index);

//////////////////////////////////////////////////////////
//             Destroys the given array                 //
//////////////////////////////////////////////////////////
void	ParserArray_destroy(ParserArray *array);



/////////////////////////////
//List management functions//
/////////////////////////////

//////////////////////////////////////////////////////////
//Transforms a ParserList into a ParserArray.           //
//This will fail if all elements doesn't have the same  //
//type. Returns an array of length -1 on failure.       //
//////////////////////////////////////////////////////////
ParserArray	ParserList_toArray(ParserList *list);

//////////////////////////////////////////////////////////
//Returns a pointer to the link at the index or NULL    //
//if not found                                          //
//////////////////////////////////////////////////////////
ParserList	*ParserList_getElement(ParserList *list, int index);

//////////////////////////////////////////////////////////
// Add the given list to the index in the list. Returns //
//     true if added successfully and false if not      //
//////////////////////////////////////////////////////////
bool	ParserList_addElement(ParserList *list, void *data, ParserTypes type, int index);

//////////////////////////////////////////////////////////
//       Deletes the given index in the list.           //
//////////////////////////////////////////////////////////
void	ParserList_delElement(ParserList *list, int index);

//////////////////////////////////////////////////////////
//              Destroys the given list                 //
//////////////////////////////////////////////////////////
void	ParserList_destroy(ParserList *list);



////////////////////////////
//Obj management functions//
////////////////////////////

//////////////////////////////////////////////////////////
//Returns a pointer to the link at the index or NULL    //
//if not found                                          //
//////////////////////////////////////////////////////////
ParserObj	*ParserObj_getElement(ParserObj *list, char *index);

//////////////////////////////////////////////////////////
// Add the given list to the index in the list. Returns //
//     true if added successfully and false if not      //
//////////////////////////////////////////////////////////
bool	ParserObj_addElement(ParserObj *list, void *data, ParserTypes type, char *index);

//////////////////////////////////////////////////////////
//       Deletes the given index in the list.           //
//////////////////////////////////////////////////////////
void	ParserObj_delElement(ParserObj *list, char *index);

//////////////////////////////////////////////////////////
//               Destroys the given obj                 //
//////////////////////////////////////////////////////////
void	ParserObj_destroy(ParserObj *list);



//////////////////////////////
//Float management functions//
//////////////////////////////

//////////////////////////////////////////////////////////
//   Transform a ParserFloat type to a classic float    //
//////////////////////////////////////////////////////////
float	ParserFloat_toFloat(ParserFloat *value);

//////////////////////////////////////////////////////////
//             Destroys the given float                 //
//////////////////////////////////////////////////////////
void	ParserFloat_destroy(ParserFloat *value);



///////////////////////////////
//String management functions//
///////////////////////////////

//////////////////////////////////////////////////////////
//  Transform a ParserString type to a classic char *   //
//////////////////////////////////////////////////////////
char	*ParserString_toCharStar(ParserString *value);

//////////////////////////////////////////////////////////
//              Destroys the given int                  //
//////////////////////////////////////////////////////////
void	ParserString_destroy(ParserString *value);



/////////////////////////////////
//Integers management functions//
/////////////////////////////////

//////////////////////////////////////////////////////////
//     Transform a ParserInt type to a classic int      //
//////////////////////////////////////////////////////////
int	ParserInt_toInt(ParserInt *value);

//////////////////////////////////////////////////////////
//              Destroys the given int                  //
//////////////////////////////////////////////////////////
void	ParserInt_destroy(ParserInt *value);



////////////////////////////////
//Boolean management functions//
////////////////////////////////

//////////////////////////////////////////////////////////
//   Transform a ParserBoolean type to a classic bool   //
//////////////////////////////////////////////////////////
bool	ParserBoolean_toBool(ParserBoolean *value);

//////////////////////////////////////////////////////////
//             Destroys the given float                 //
//////////////////////////////////////////////////////////
void	ParserBoolean_destroy(ParserBoolean *value);

#endif
