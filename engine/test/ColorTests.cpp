
#include "ColorTests.h"
#include "Color.h"

using namespace Checkers::Engine;

CPPUNIT_TEST_SUITE_REGISTRATION( ColorTests );


void ColorTests::setUp()
{
}

void ColorTests::tearDown()
{
}

void ColorTests::equalToEnum()
{
  Color c(Color::EBlack);
  CPPUNIT_ASSERT(c == Color::EBlack);
  CPPUNIT_ASSERT(Color::EBlack == c);
}

void ColorTests::notEqualToEnum()
{
  Color c(Color::EWhite);
  CPPUNIT_ASSERT(c != Color::EBlack);
  CPPUNIT_ASSERT(Color::EBlack != c);
}

void ColorTests::equalToColor()
{
  Color c1(Color::EWhite);
  Color c2(c1);
  CPPUNIT_ASSERT(c1 == c2);
}

void ColorTests::notEqualToColor()
{
  Color c1(Color::EWhite);
  Color c2(Color::EBlack);
  CPPUNIT_ASSERT(c1 != c2);
}
