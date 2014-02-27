#ifndef ACTIONS_H_
#define ACTIONS_H_

namespace ecc
{
    class warning;

    void ac_begin_enumdef();
    void ac_push_enumdef( string* pName );
    void ac_insert_member(string* pMember, int val, string* pLongStr);
    void ac_register_attribute( ast::enumattr attr);

    void ac_set_namespace(string* pNamespace);
    void ac_register_warning(const warning& wn);

}
#endif
