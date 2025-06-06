#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined (NULL)
#define NULL 0
#endif

/*
** 
** assumptions:
** 1 Assume sufficient space in the SQL string for the string replacement.
** The requirement states only 2 parameters to pass to the function, 
** query string and DBMS, so not checking for sufficient space in the 
** SQL string by passing size of SQL string array.
** 2 Assume substring function in source SQL statement is "subs" 
** 3 Assume no DBMS will use a substring function name longer than 10 characters 
** including NULL.  Using 10 for max length.
** 4 Would have used switch if the database type was passed as an int but
** understood the requirements to say database type would be passed as string.
** 5 For simplicity, assume length of SQL statement and target substring function 
** name plus NULL is less than 1000 characters.  
** 6 Assume RebuildQuery function is called from main() within this file.  Otherwise
** would define the function with extern and create header file with function definition
** and RS_* define statements to include in this file and the file with main().
**
*/

#define RS_DBMS1            "DBMS1"
#define RS_DBMS2            "DBMS2"
#define RS_DBMS3            "DBMS3"
#define RS_DBMSSOURCE       "subs"
#define RS_SUCCESS          0
#define RS_UNKNOWNDBTYPE    1
#define RS_STRNOTFOUND      2
#define RS_DBMS1STR         "substr"
#define RS_DBMS2STR         "substring"
#define RS_DBMS3STR         "sbstr"
#define RS_MAXSUBLEN        10      // max length + 1 for null of new substring function name
#define RS_MAXSQLLEN        1000

/*
** function: RebuildQuery
**
** Purpose: Substitute substring function in passed SQL with substring function
** name based on dbtype parameter passed
**
** Arguments: char *sqlstring - pointer to source SQL string
** const char *dbtype - string indicating target DBMS 
**
** Returns: int
** 0 - success
** 1 - unknown DBMS type
** 2 - substring function name not found in source SQL string
**
*/
extern int RebuildQuery(char *sqlstring,const char *dbtype)
{
    char    *pos;     // pointer to substring function in sqlstring
    char    newsubstr[RS_MAXSUBLEN];
    char    saveSQL[RS_MAXSQLLEN];
    int     i;

// Find the occurence of the substring function

    pos = strstr(sqlstring, RS_DBMSSOURCE);
    if (pos == NULL)
        return(RS_STRNOTFOUND);

// Based on the dbtype passed, determine the new substring function name

    for (i=0;i<RS_MAXSUBLEN;++i)
        newsubstr[i]='\0';

    if (strcmp(dbtype,RS_DBMS1) == 0)
        strcpy(newsubstr, RS_DBMS1STR);
else if (strcmp(dbtype,RS_DBMS2) == 0)
        strcpy(newsubstr, RS_DBMS2STR);
    else if (strcmp(dbtype,RS_DBMS3) == 0)
        strcpy(newsubstr,RS_DBMS3STR);
    else 
        return(RS_UNKNOWNDBTYPE);

// Save the source SQL after the substring function

    strcpy(saveSQL,pos+strlen(RS_DBMSSOURCE));

// put the new substring function into the original SQL string

    strcpy(pos,newsubstr);

// add the saved SQL to the original SQL string

    strcpy(pos+strlen(newsubstr),saveSQL);
    return(RS_SUCCESS);
    
}

