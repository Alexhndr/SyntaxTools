#ifndef SYNTAX_TOOLS_TESTS_H
#define SYNTAX_TOOLS_TESTS_H

#include <QObject>
#include <QtTest/QtTest>

#include "Lexer/LTests.h"
#include "Parser/PTests.h"

class Tests: public QObject {
    Q_OBJECT

private slots:
    void TestLexer() const;
    void TestParser() const;
};

#endif
