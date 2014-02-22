#ifndef ACTIONS_H_
#define ACTIONS_H_

namespace ecc
{
    void ac_register_enumdef(enumdef*);
    void ac_push_enumdef( string* pName );
    void ac_insert_member(string* pMember, int val, string* pLongStr);
}
#endif
