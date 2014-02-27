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
    extern ctree<ast::enumdef> NsTree;
    extern ctree<ast::enumdef>* CurrentNamespace;

}

#endif
