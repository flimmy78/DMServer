//=============================================================================
/* 
*  File: DMType.h
*
*  Author: bing
*
*  Date: 2016-09-01
*
*  Version: v2.0
*
*  Github/Mail: https://github.com/binchen-china    <563853086@qq.com>
*
*  Note:
*/
//=============================================================================

#pragma once

typedef char DM_INT8;
typedef short DM_INT16;
typedef int DM_INT32;
typedef int DM_INT;
typedef long long DM_INT64;

typedef unsigned char DM_UINT8;
typedef unsigned short DM_UINT16;
typedef unsigned int DM_UINT32;
typedef unsigned int DM_UINT;
typedef unsigned long long DM_UINT64;

typedef float DM_FLOAT;
typedef double DM_DOUBLE;

typedef bool DM_BOOL;
typedef bool BOOL;

typedef char DM_CHAR;
typedef unsigned char DM_UCHAR;

using namespace std;

#define INVALID_INT 0
#define INVALID_CHAR '\0'

#define TRUE true
#define FALSE false
#define True true
#define False false

#define DM_MAIN ACE_TMAIN
