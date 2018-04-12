#include <cstdlib>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include "MyTestCAse.h"

using namespace std;
using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION(MyTestCAse);

int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    TestFactoryRegistry  &registry = TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();
    return (EXIT_SUCCESS);
}

