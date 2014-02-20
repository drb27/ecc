#ifndef GLOBALS_H_
#define GLOBALS_H_

namespace ecc
{
    extern const string version;
    extern ast::elist_t MasterList;
    extern ast::enumdef* CurrentEnumDef;
    extern vector<ast::enumattr> CurrentAttributes;
    extern vector<warning> Warnings;
    extern int CurrentLine;
    void input(char*, int&, size_t);
}

#endif
