/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   idTest.cpp
 * Author: scott
 *
 * Created on 30/07/2017, 12:16:52 AM
 */

#include "idTest.h"
#include "idGenerator.h"


CPPUNIT_TEST_SUITE_REGISTRATION(idTest);

idTest::idTest() {
}

idTest::~idTest() {
}

void idTest::setUp() {
}

void idTest::tearDown() {
}

void idTest::testGenerateIdentity() {
    std::string continent;
    idGenerator _idGenerator;
    id result = _idGenerator.generateIdentity(continent);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

