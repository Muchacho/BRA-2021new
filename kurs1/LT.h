#pragma once
#include "stdafx.h"
#include "Parm.h"
#define LEXEMA_FIXSIZE	1			
#define LT_MAXSIZE		4096		
#define LT_TI_NULLIDX	0xfffffff	
#define LEX_NUMBER		'n'	
#define LEX_SYMBOL		'c'
#define LEX_STRING		's'
#define LEX_DATATYPE	't'
#define LEX_ID			'i'	
#define LEX_NUMBER_LIT	'2'
#define LEX_STRING_LIT	'3'
#define LEX_SYMBOL_LIT	'4'
#define LEX_LITERAL		'l'
#define LEX_FUNCTION	'f'	
#define LEX_CREATE		'd'	
#define LEX_RETURN		'r'	
#define LEX_SHOW		'p'	
#define LEX_MAIN		'm'	
#define LEX_SEMICOLON	';'	
#define LEX_COMMA		','	
#define LEX_MREQUAL		'{'	
#define LEX_LSEQUAL		'}'	
#define LEX_LEFTTHESIS	'('	
#define LEX_RIGHTTHESIS	')'	
#define LEX_PLUS		'+'	
#define LEX_MINUS		'-'	
#define LEX_STAR		'*'
#define LEX_DIRSLASH	'/'
#define LEX_PROCENT		'%'
#define LEX_EQUAL		'='
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_LESS_OR_EQUALS '$'
#define LEX_MORE_OR_EQUALS '#'
#define LEX_FULL_EQUALS '~'
#define LEX_NOT_FULL_EQUALS '&'
#define LEX_IF			'e'
#define LEX_ELSE		'y'
#define LEX_COMMERCIAL_AT '@'
#define LEX_CICLE_DO 'a'
#define LEX_CICLE_WHILE 'z'
#define LEX_CICLE_LKOV '\\['
#define LEX_CICLE_RKOV '\\]'



namespace LT {
	struct Entry {
		char lexema;
		int sn;
		int idxTI;
		bool isFunc = 0;
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	void ShowTable(LexTable& lextable, std::ofstream* stream);
}