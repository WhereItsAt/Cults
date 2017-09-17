/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   idTest.h
 * Author: scott
 *
 * Created on 30/07/2017, 12:16:52 AM
 */

#ifndef IDTEST_H
#define IDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class idTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(idTest);

    CPPUNIT_TEST(testGenerateIdentity);

    CPPUNIT_TEST_SUITE_END();

public:
    idTest();
    virtual ~idTest();
    void setUp();
    void tearDown();

private:
    void testGenerateIdentity();

};

#endif /* IDTEST_H */

