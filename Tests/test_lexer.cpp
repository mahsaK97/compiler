#include <gtest/gtest.h>
#include "Lexer.h"

TEST(LexerTest, TokenizerSimpleAssignment)
{
    Lexer lexer("int x = 54;");
    auto tokens= lexer.scanTokens();
    ASSERT_FALSE(tokens.empty());
}

