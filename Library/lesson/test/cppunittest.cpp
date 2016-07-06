#include <string>
// CPP Unit includes used in this example
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>

using namespace CppUnit;


// Class of several tests
class SampleUnitTest : public TestCase
{
public:
    SampleUnitTest() : TestCase("Sample Unit Test") {}

    // Actual test case functions and code
    void testObviousOne() {
        CPPUNIT_ASSERT( 1 == 1);
    }

    void testObviousTwo() {
        CPPUNIT_ASSERT( 2 == 2);
    }

    void testObviousThree() {
        CPPUNIT_ASSERT( 3 == 3);
    }

    void testObviousFour() {
        CPPUNIT_ASSERT( 3 == 4);  // Oh no! This test will fail.
    }

    // Within the test class, a static method which loads all tests into an aggregate test object
    static Test *suite()
    {
        TestSuite *suiteOfTests = new TestSuite("Sample Unit Test");
        suiteOfTests->addTest(new TestCaller<SampleUnitTest>("testObviousOne",   &SampleUnitTest::testObviousOne));
        suiteOfTests->addTest(new TestCaller<SampleUnitTest>("testObviousTwo",   &SampleUnitTest::testObviousTwo));
        suiteOfTests->addTest(new TestCaller<SampleUnitTest>("testObviousThree", &SampleUnitTest::testObviousThree));
        suiteOfTests->addTest(new TestCaller<SampleUnitTest>("testObviousFour",  &SampleUnitTest::testObviousFour));
        return suiteOfTests;
    }
};

// Sample main
int main(int argc, char **argv)
{
    TextUi::TestRunner runner;
    runner.addTest( SampleUnitTest::suite() );
    runner.run();
    return 0;
}
/*
g++ --static -o main cppunittest.cpp -I/usr/local/include -L/usr/local/lib -lcppunit
*/