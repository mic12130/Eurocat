#include "pch.h"

#include "plugin/extension/OpDataConverter.h"

namespace Eurocat::Plugin
{
	const char leadingChar = '/';

	TEST(OpDataConverterTest, ConvertsEmptyContentFromEs)
	{
		OpDataExtraction extraction;
		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "");
	}

	TEST(OpDataConverterTest, ConvertsSingleSlashFromEs)
	{
		OpDataExtraction extraction;
		extraction.text = "/";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "");
	}

	TEST(OpDataConverterTest, ConvertsTextWithSlashFromEs)
	{
		OpDataExtraction extraction;
		extraction.text = "/AAA";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "AAA");
	}

	TEST(OpDataConverterTest, ConvertsTextWithoutSlashFromEs)
	{
		OpDataExtraction extraction;
		extraction.text = "AAA";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "AAA");
	}

	TEST(OpDataConverterTest, ConvertsLowerTextFromEs)
	{
		OpDataExtraction extraction;
		extraction.text = "ab-cd";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "AB-CD");
	}

	TEST(OpDataConverterTest, ConvertAssignedHeadingFromEs)
	{
		OpDataExtraction extraction;
		extraction.assignedHeading = 50; // Also test leading zero filling

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "H050");
	}

	TEST(OpDataConverterTest, ConvertAssignedSpeedFromEs)
	{
		OpDataExtraction extraction;
		extraction.assignedSpeed = 160;

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "S160");
	}

	TEST(OpDataConverterTest, ConvertsAssignedMachFromEs)
	{
		OpDataExtraction extraction;
		extraction.assignedMach = 75;

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "M75");
	}

	TEST(OpDataConverterTest, ConvertsDctPointFromEs)
	{
		OpDataExtraction extraction;
		extraction.dctPoint = "ATAGA";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "ATAGA");
	}

	TEST(OpDataConverterTest, ConnectsAssignedDataAndTextFromEs)
	{
		OpDataExtraction extraction;
		extraction.assignedHeading = 180;
		extraction.text = "/TEXT";

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "H180 TEXT");
	}

	TEST(OpDataConverterTest, ConnectsMultipleAssignedDataFromEs)
	{
		OpDataExtraction extraction;
		extraction.assignedHeading = 130;
		extraction.assignedMach = 82;

		EXPECT_STREQ(OpDataConverter::FromEsFormat(extraction, leadingChar), "H130 M82");
	}

	TEST(OpDataConverterTest, ConvertsEmptyContentInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("", leadingChar);

		EXPECT_EQ(result, OpDataExtraction());
	}

	TEST(OpDataConverterTest, ConvertsTextInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("TEXT", leadingChar);
		OpDataExtraction expected;
		expected.text = "/TEXT";

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, ConvertsLowerTextInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("text", leadingChar);
		OpDataExtraction expected;
		expected.text = "/TEXT";

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, ConvertsHeadingInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("H140", leadingChar);
		OpDataExtraction expected;
		expected.assignedHeading = 140;

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, ConvertsSpeedInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("S250", leadingChar);
		OpDataExtraction expected;
		expected.assignedSpeed = 250;

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, ConvertsMachInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("M78", leadingChar);
		OpDataExtraction expected;
		expected.assignedMach = 78;

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, ConvertsMultiDataTypesInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("H320 S180 TEXT", leadingChar);
		OpDataExtraction expected;
		expected.assignedHeading = 320;
		expected.assignedSpeed = 180;
		expected.text = "/TEXT";

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, HandlesSpacedTextInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("H320 SPACED TEXT", leadingChar);
		OpDataExtraction expected;
		expected.assignedHeading = 320;
		expected.text = "/SPACED TEXT";

		EXPECT_EQ(result, expected);
	}

	TEST(OpDataConverterTest, HandlesSeparatedTextInput)
	{
		OpDataExtraction result = OpDataConverter::ToEsFormat("SEP H320 TEXT", leadingChar);
		OpDataExtraction expected;
		expected.assignedHeading = 320;
		expected.text = "/SEP TEXT";

		EXPECT_EQ(result, expected);
	}
}
