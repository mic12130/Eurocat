#include "pch.h"

#include "warning/DupeSquawkChecker.h"

#include "warning/MockDupeSquawkCheckDataProvider.h"

using ::testing::Return;

namespace Eurocat::Warning
{
	class DupeSquawkCheckerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			dataProvider = std::make_shared<MockDupeSquawkCheckDataProvider>();
			checker = std::make_unique<DupeSquawkChecker>(dataProvider);
		}

		std::shared_ptr<MockDupeSquawkCheckDataProvider> dataProvider;
		std::unique_ptr<DupeSquawkChecker> checker;
	};

	TEST_F(DupeSquawkCheckerTest, NoWarningByDefault)
	{
		EXPECT_CALL(*dataProvider, GetSquawkDataCollection)
			.WillOnce(Return(std::vector<SquawkData>()));

		checker->Check();

		EXPECT_EQ(checker->GetWarningTargetIds().size(), 0);
	}

	TEST_F(DupeSquawkCheckerTest, NoWarningWhenNoDupeSquawk)
	{
		EXPECT_CALL(*dataProvider, GetSquawkDataCollection)
			.WillOnce(Return(std::vector
				{
					SquawkData("111", "1200"),
					SquawkData("222", "2000"),
					SquawkData("333", "3000")
				}));

		checker->Check();

		EXPECT_EQ(checker->GetWarningTargetIds().size(), 0);
	}

	TEST_F(DupeSquawkCheckerTest, DetectsTwoDupeSquawks)
	{
		EXPECT_CALL(*dataProvider, GetSquawkDataCollection)
			.WillOnce(Return(std::vector
				{
					SquawkData("111", "1200"),
					SquawkData("222", "3500"),
					SquawkData("333", "3500")
				}));

		checker->Check();

		auto expected = std::vector<CString>{ "222", "333" };
		EXPECT_EQ(checker->GetWarningTargetIds(), expected);
	}

	TEST_F(DupeSquawkCheckerTest, DetectsMultipleDupeSquawks)
	{
		EXPECT_CALL(*dataProvider, GetSquawkDataCollection)
			.WillOnce(Return(std::vector
				{
					SquawkData("111", "4200"),
					SquawkData("222", "4200"),
					SquawkData("333", "4200"),
					SquawkData("625", "4201")
				}));

		checker->Check();

		auto expected = std::vector<CString>{ "111", "222", "333" };
		EXPECT_EQ(checker->GetWarningTargetIds(), expected);
	}
}
