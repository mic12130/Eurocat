#include "pch.h"

#include "hmi/track/tag/alert/WarningSelector.h"

namespace Eurocat::Hmi::Track
{
	class WarningSelectorTest : public ::testing::Test
	{
	protected:
		WarningSelector selector;
	};

	TEST_F(WarningSelectorTest, NoWarning)
	{
		auto warningList = std::vector<WarningType>();
		auto selected = selector.SelectWarning(warningList);
		EXPECT_EQ(selected, std::nullopt);
	}

	TEST_F(WarningSelectorTest, OneWarning)
	{
		auto warningList = std::vector{ WarningType::Stca };

		auto selected = selector.SelectWarning(warningList);

		ASSERT_TRUE(selected.has_value());
		EXPECT_EQ(selected.value(), WarningType::Stca);
	}

	// Warning priority: STCA > DAIW > MSAW > CLAM > RAM > DUPE
	TEST_F(WarningSelectorTest, SelectsHighestPriorityWarning)
	{
		auto warningList = std::vector{ WarningType::Ram, WarningType::Stca, WarningType::Dupe };

		auto selected = selector.SelectWarning(warningList);

		ASSERT_TRUE(selected.has_value());
		EXPECT_EQ(selected.value(), WarningType::Stca);
	}

	TEST_F(WarningSelectorTest, FiltersWarnings)
	{
		// We only allow DUPE because it has the lowest priority
		// This can avoid the result that made by priority sorting
		selector.allowedWarnings = std::vector{ WarningType::Dupe };
		auto warningList = std::vector{ WarningType::Stca, WarningType::Dupe };

		auto selected = selector.SelectWarning(warningList);

		ASSERT_TRUE(selected.has_value());
		EXPECT_EQ(selected.value(), WarningType::Dupe);
	}

	TEST_F(WarningSelectorTest, FiltersWarningsWithNoWarningLeft)
	{
		selector.allowedWarnings = std::vector{ WarningType::Dupe };
		auto warningList = std::vector{ WarningType::Stca, WarningType::Daiw };

		auto selected = selector.SelectWarning(warningList);

		EXPECT_EQ(selected, std::nullopt);
	}
}
