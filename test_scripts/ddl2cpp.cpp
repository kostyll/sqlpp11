#include "ddl2cpp_util.h"

int ddl2cpp(int, char* [])
{

#ifndef __MACH__
  std::ifstream file("../scripts/ddl2cpp");
  if (!file)
  {
    std::cout << "script tests should be started from the top level sqlpp11 directory. Where scripts/ dir is found\n";
    exit(1);
  }

  assert(testSqlFile ("../test_scripts/ddl2cpp_sample_good.sql") == 0);
  assert(testSqlFile ("../test_scripts/ddl2cpp_sample_bad.sql") > 0);

  /* maybe todo 1: test compile / use db_mock, for now we're just checking that ddl2cpp generates header without errors
   */
  /*
  MockDb db = {};
  MockDb::_serializer_context_t printer = {};

  const auto f = test::TabFoo{};
  const auto t = test::TabBar{};
  const auto tab_a = f.as(sqlpp::alias::a);

  getColumn(db, t._epsilon); //underscore bug check
  */
#endif
  return 0;
}

