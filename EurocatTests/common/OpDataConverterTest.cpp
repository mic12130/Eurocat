#include "pch.h"

#include "plugin/extension/OpDataConverter.h"

namespace Eurocat::Plugin
{
	TEST(OpDataConverterTest, ConvertsEmptyStringFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat(""), "");
	}

	TEST(OpDataConverterTest, ConvertsSingleSlashFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat("/"), "");
	}

	TEST(OpDataConverterTest, ConvertsStringWithSlashFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat("/AAA"), "AAA");
	}

	TEST(OpDataConverterTest, ConvertsStringWithoutSlashFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat("AAA"), "AAA");
	}

	TEST(OpDataConverterTest, MakesUpperWhenConvertFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat("ab-cd"), "AB-CD");
	}

	TEST(OpDataConverterTest, CanClipLongStringFromEs)
	{
		EXPECT_STREQ(OpDataConverter::FromEsFormat("123123123123"), "1231231231");
	}

	TEST(OpDataConverterTest, CanClipLongStringWithSlashFromEs)
	{
		// Slash shall be ignored in this test case
		EXPECT_STREQ(OpDataConverter::FromEsFormat("/123123123123"), "1231231231");
	}

	TEST(OpDataConverterTest, ConvertsEmptyOpDataToEs)
	{
		EXPECT_STREQ(OpDataConverter::ToEsFormat(""), "");
	}

	TEST(OpDataConverterTest, ConvertsNonEmptyOpDataToEs)
	{
		EXPECT_STREQ(OpDataConverter::ToEsFormat("2333"), "/2333");
	}
}
