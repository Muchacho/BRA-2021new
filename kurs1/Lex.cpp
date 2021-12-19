#include "stdafx.h"
#include "Lex.h"
#include "LT.h"
#include "In.h"
#include "REGS.h"
#include "Log.h"

char Lex::GetToken(std::string str) {
	std::array<std::string, 36> regexps = {
		REG_CREATE, REG_SYMBOL, REG_STRING, REG_NUMBER, REG_FUNCTION,REG_CICLE_DO, REG_CICLE_WHILE,REG_CICLE_LKOV, REG_CICLE_RKOV, REG_RETURN, REG_SHOW,
		REG_MAIN, REG_NUMBER_LIT, REG_SYMBOL_LIT, REG_STRING_LIT, REG_SEMICOLON, REG_COMMA,
		REG_MREQUAL, REG_LSEQUAL, REG_LEFTTHESIS, REG_RIGHTTHESIS, REG_PLUS, REG_MINUS,
		REG_STAR, REG_DIRSLASH, REF_PROCENT, REG_EQUAL,REG_IF, REG_ELSE, REG_MORE, REG_LESS, REG_LESS_OR_EQUALS,
		REG_MORE_OR_EQUALS, REG_FULL_EQUALS, REG_NOT_FULL_EQUALS, REG_ID
	};
	std::array<char, 38> tokens = {
		LEX_CREATE, LEX_SYMBOL, LEX_STRING, LEX_NUMBER, LEX_FUNCTION,LEX_CICLE_DO,LEX_CICLE_WHILE, LEX_CICLE_LKOV, LEX_CICLE_RKOV, LEX_RETURN, LEX_SHOW,
		LEX_MAIN, LEX_NUMBER_LIT, LEX_SYMBOL_LIT, LEX_STRING_LIT, LEX_SEMICOLON, LEX_COMMA,
		LEX_MREQUAL, LEX_LSEQUAL, LEX_LEFTTHESIS, LEX_RIGHTTHESIS, LEX_PLUS, LEX_MINUS,
		LEX_STAR, LEX_DIRSLASH, LEX_PROCENT, LEX_EQUAL, LEX_IF, LEX_ELSE, LEX_MORE, LEX_LESS, LEX_LESS_OR_EQUALS,
		LEX_MORE_OR_EQUALS, LEX_FULL_EQUALS, LEX_NOT_FULL_EQUALS, LEX_ID
	};
	for (int i = 0; i < sizeof(regexps) / sizeof(regexps[0]); ++i) {
		if (std::regex_match(str, std::regex(regexps[i]))) {
			return tokens[i];
		}
	}
	return EOF;
}


void Lex::Scan(LT::LexTable& lextable, IT::IdTable& idtable, In::IN& in, Parm::PARM& parm, Log::LOG& log) {
	std::ofstream outfile(parm.out);
	outfile << in.text << std::endl;
	outfile << "0001 ";

	std::string word = "";
	std::string cur_scope = "";
	std::vector<std::string> ti_scope = { TI_SCOPE_DEFAULT };

	int counter = 0, doublekov = 0;
	bool findStringLit = false;
	bool inLineFunction = false;
	int isMain = 0;
	bool charlex = 0;
	int scopeCounter = 0;
	for (int i = 0, line = 1; i < in.text.size(); ++i)
	{
		IT::IDDATATYPE iddatatype;

		auto fillTable = [&] {
			char token = Lex::GetToken(word);
			int ti_idx = TI_NULLIDX;

			iddatatype = (token == LEX_NUMBER || token == LEX_NUMBER_LIT) ? IT::IDDATATYPE::NUM :
				(token == LEX_SYMBOL || token == LEX_SYMBOL_LIT) ? IT::IDDATATYPE::SYM :
				(token == LEX_STRING || token == LEX_STRING_LIT) ? IT::IDDATATYPE::STR : iddatatype;

			switch (token)
			{
			case LEX_SEMICOLON:charlex = 0; break;
				case LEX_MAIN:
					IT::Add(idtable, { lextable.size + 1, word, ti_scope.back(), IT::IDDATATYPE::NUM, IT::IDTYPE::F });
					cur_scope = "main";
					isMain == 0 ? ++isMain : throw ERROR_THROW(128);
					break;
				case LEX_ID:
					if (lextable.size >= 3 && lextable.table[lextable.size - 2].lexema != LEX_CREATE && lextable.table[lextable.size - 3].lexema != LEX_CREATE) {		
						ti_idx = IT::IsId(idtable, word, ti_scope);
					}
					if (ti_idx == TI_NULLIDX)
					{
						if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexema == LEX_FUNCTION)
						{
							IT::Add(idtable, { lextable.size, word, ti_scope.back(), iddatatype, IT::IDTYPE::F });
							cur_scope = word;
							if (lextable.size >= 3 && lextable.table[lextable.size - 3].lexema == LEX_CREATE) {
								inLineFunction = true;
								lextable.table[lextable.size].isFunc = 1;
							}

						}
						else if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexema == LEX_CREATE && lextable.table[lextable.size - 1].lexema == LEX_DATATYPE) {
							IT::Add(idtable, { lextable.size, word, ti_scope.back(), iddatatype, IT::IDTYPE::V });
						}
						else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexema == LEX_DATATYPE) {
							IT::Add(idtable, { lextable.size, word, ti_scope.back(), iddatatype, IT::IDTYPE::P });
						}
						else {
							throw ERROR_THROW_IN(307, line, -1);
						}
						ti_idx = idtable.size  - 1;
					}
					break;
				case LEX_LEFTTHESIS:
					if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexema == LEX_FUNCTION) {
						ti_scope.push_back(cur_scope);
					}
					break;
				case LEX_MREQUAL:
					if (cur_scope.empty()) {
						cur_scope = "scope_" + std::to_string(scopeCounter);
						++scopeCounter;
						ti_scope.push_back(cur_scope);
					}
					if (ti_scope.back() != cur_scope) {
						ti_scope.push_back(cur_scope);
					}
					cur_scope = "";
					break;
				case LEX_RIGHTTHESIS:
					if (inLineFunction) {
						ti_scope.pop_back();
						inLineFunction = false;
						cur_scope = "";
					}
					break;
				case LEX_LSEQUAL: 
					ti_scope.pop_back();
					break;
				case LEX_SYMBOL_LIT:
					/*word = word.substr(1, word.length() - 2);
					if (word.length() > 1) throw ERROR_THROW_IN(131, line, -1);
					ti_idx = IT::isLit(idtable, word);
					if (ti_idx == TI_NULLIDX) {
						IT::Add(idtable, { lextable.size, "L" + std::to_string(counter), ti_scope.back(), IT::IDTYPE::L, word.c_str() });
						++counter;
						ti_idx = idtable.size - 1;
					}
					token = LEX_LITERAL;*/
					word = word.substr(1, word.length() - 2);
					if (word.length() > TI_STR_MAXSIZE) throw ERROR_THROW_IN(124, line, -1);
					ti_idx = IT::isLit(idtable, word);
					if (ti_idx == TI_NULLIDX) {
						IT::Add(idtable, { lextable.size, "L" + std::to_string(counter), ti_scope.back(), IT::IDTYPE::L, word[0] });
						++counter;
						ti_idx = idtable.size - 1;
					}

					token = LEX_LITERAL;
					break;
				case LEX_STRING_LIT:
					word = word.substr(1, word.length() - 2);
					if(charlex && word.length() > 1)throw ERROR_THROW_IN(131, line, -1);
					if (word.length() > TI_STR_MAXSIZE) throw ERROR_THROW_IN(124, line, -1);
					ti_idx = IT::isLit(idtable, word);
					if (ti_idx == TI_NULLIDX) {
						IT::Add(idtable, { lextable.size, "L" + std::to_string(counter), ti_scope.back(), IT::IDTYPE::L, word.c_str() });
						++counter;
						ti_idx = idtable.size - 1;
					}
					token = LEX_LITERAL;
					break;
				case LEX_NUMBER_LIT:
					if (lextable.size >= 2 && lextable.table[lextable.size - 1].lexema == LEX_MINUS && lextable.table[lextable.size - 2].idxTI == -1)
					{
						word = "-" + word;
						--lextable.size;
					}
					if (word[word.length() - 1] == 'e') {
						word = std::to_string(std::stoll(word, 0, 8));
					}
					else if (word[word.length() - 1] == 'd') {
						word = std::to_string(std::stoll(word, 0, 2));
					}
					if (std::stoll(word) > INT_MAX || std::stoll(word) < INT_MIN)
						throw ERROR_THROW_IN(131, line, -1);
					ti_idx = IT::isLit(idtable, word);
					if (ti_idx == TI_NULLIDX) {
						IT::Add(idtable, { lextable.size, "L" + std::to_string(counter), ti_scope.back(), IT::IDTYPE::L, std::stoi(word) });
						++counter;
						ti_idx = idtable.size - 1;
					}
					token = LEX_LITERAL;
					break;
				case LEX_SYMBOL:
					charlex = 1;
					token = LEX_DATATYPE;
					break;
				case LEX_STRING:
				case LEX_NUMBER:
					token = LEX_DATATYPE;
					break;
				case EOF:
					throw ERROR_THROW_WORD(122, line, word);
				default:
					break;
			}
			LT::Add(lextable, { token, line, ti_idx });
			outfile << token;
			word.clear();
		};

		unsigned char ch = in.text[i];
		if (ch == '\'') {
			findStringLit = !findStringLit; doublekov++;
		}
		if (doublekov % 2 != 0 && ch == '|')
			throw ERROR_THROW_WORD(122, line, word);

		if ((In::IN::LX == in.code[ch] || In::IN::SPC == in.code[ch] || (int)ch == (int)IN_CODE_SEP) && !findStringLit)
		{
			if (!word.empty())
			{
				fillTable();
			}
			if (in.code[ch] == In::IN::LX) {
				word = ch;
				fillTable();
			}
			if ((int)ch == (int)IN_CODE_SEP) {
				if (in.text[i + 1]) {
					outfile << "\n" << std::setw(4) << std::setfill('0') << ++line << " ";
				}
			}
		}
		else if (in.code[ch] == In::IN::T || findStringLit) {
			word += ch;
		}
	}
	if (isMain == 0) throw ERROR_THROW(129);
}