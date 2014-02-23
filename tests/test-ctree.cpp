#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <exception>

using namespace std;

#include "sassert.h"
#include "ctree.h"
#include "test-ctree.h"
#include "ast.h"

using namespace CppUnit;
using ecc::ast::enumdef;


namespace test {

    /** @{ @name Unit Tests */

    void ctree::create_root()
    {
	::ctree<enumdef> root;
	CPPUNIT_ASSERT_MESSAGE("Name is not empty",root.name().empty());
	CPPUNIT_ASSERT_MESSAGE("Parent is not NULL",NULL==root.parent());
    }

    void ctree::add_member_to_root()
    {
	::ctree<enumdef> root;
	enumdef e;
	root.insert_member(&e);
	CPPUNIT_ASSERT_MESSAGE("Member count is wrong",1==root.members().size());
	CPPUNIT_ASSERT_MESSAGE("Member identity is wrong",&e==root.members()[0]);
    }
    
    void ctree::add_subnode_to_root()
    {
	::ctree<enumdef> root;
	::ctree<enumdef>& newnode = root.create_node("std");
	::ctree<enumdef>& lookupnode = root.find_local_node("std");
        CPPUNIT_ASSERT_MESSAGE("Node value not preserved",newnode==lookupnode);
        CPPUNIT_ASSERT_MESSAGE("Node identity not preserved",&newnode==&lookupnode);
    }

    void ctree::create_path()
    {
	::ctree<enumdef> root;
	root.create_path("std::hello::there");

        CPPUNIT_ASSERT_MESSAGE("root name corruption",root.name().empty());

	::ctree<enumdef>& std = root.find_local_node("std");
	::ctree<enumdef>& hello = std.find_local_node("hello");


	hello.create_node("other");
	::ctree<enumdef>& there = hello.find_local_node("there");
	::ctree<enumdef>& other = hello.find_local_node("other");

        CPPUNIT_ASSERT_MESSAGE("std not found",std.name()=="std");
        CPPUNIT_ASSERT_MESSAGE("hello not found",hello.name()=="hello");
        CPPUNIT_ASSERT_MESSAGE("there not found",there.name()=="there");
        CPPUNIT_ASSERT_MESSAGE("other not found",other.name()=="other");

        CPPUNIT_ASSERT_MESSAGE("Unexpected fqn",there.fqn()=="std::hello::there");

    }

    void ctree::lookup()
    {
	::ctree<enumdef> root;
	root.create_path("std::hello::there");
	::ctree<enumdef>& there = root.lookup("std::hello::there");
	::ctree<enumdef>& another = there.create_node("another");

        CPPUNIT_ASSERT_MESSAGE("Unexpected fqn",there.fqn()=="std::hello::there");
        CPPUNIT_ASSERT_MESSAGE("Unexpected fqn",another.fqn()=="std::hello::there::another");
	
	CPPUNIT_ASSERT_MESSAGE("there has bad parent",
			       there.parent()->name() == "hello" );

	CPPUNIT_ASSERT_MESSAGE("another has bad parent",
			       (another.parent())==&there);
    }
    
    /** @} */
  

}
