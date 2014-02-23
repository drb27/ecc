
#ifndef TEST_CTREE__H_
#define TEST_CTREE__H_

#include "TestCase.h"
#include "TestSuite.h"
#include "TestCaller.h"
#include "TestRunner.h"

#include <extensions/TestFactoryRegistry.h>
#include <ui/text/TextTestRunner.h>
#include <extensions/HelperMacros.h>

using namespace CppUnit;

namespace test {

  class ctree : public TestCase
  {
    
  public:
    
    ctree() {}
    virtual ~ctree() {}
     
    void create_root();
    void add_member_to_root();
    void add_subnode_to_root();
    void create_path();
    void lookup();
 
    /** @cond internal */
    CPPUNIT_TEST_SUITE( ctree );
    CPPUNIT_TEST( create_root );
    CPPUNIT_TEST( add_member_to_root );
    CPPUNIT_TEST( add_subnode_to_root );
    CPPUNIT_TEST( create_path );
    CPPUNIT_TEST( lookup );
    CPPUNIT_TEST_SUITE_END();
    /** @endcond */
  };
  
}

#endif
