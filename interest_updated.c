#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int valid_date(int date, int mon, int year);
int main() {
	// Given values
	int day1, mon1, year1;
	int day2, mon2, year2;
	int date_diff, mon_diff, year_diff;

	printf("Enter start date (DD/MM/YYYY) : ");
	scanf("%d/%d/%d",&day1, &mon1,  &year1);

	printf("Enter end date (DD/MM/YYYY) : ");
	scanf("%d/%d/%d", &day2, &mon2, &year2);

	if(!valid_date(day1, mon1, year1))
	{
		printf("First date is invalid.\n");
	}

	if(!valid_date(day2, mon2, year2))
	{
		printf("Second date is invalid.\n");
		exit(0);
	}

	if(day2 < day1)
	{
		if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
		{
			day2 += 30;
		}
		else
		{
			day2 += 30;
		}
		mon2 = mon2 - 1;
	}
	if (mon2 < mon1)
	{
		mon2 += 12;
		year2 -= 1;
	}

	date_diff = day2 - day1;
	mon_diff = mon2 - mon1;
	year_diff = year2 - year1;
	printf("\nDifference: %d years %02d months and %02d days.\n", year_diff, mon_diff, date_diff);
	double amount;
	double interest;
	printf("Enter the amount : ");
	scanf("%lf", &amount);  // Use %lf for double
	double amount1 = amount; // Change float to double to match `amount`
	printf("Enter the interest per 100 : ");
	scanf("%lf", &interest); // Use %lf for double

	// Step 1: Calculate whole_years
	double whole_years = (year_diff > 0) ? (amount * pow(1 + (interest * 12 / 100), year_diff)) - amount : 0;

	// Step 2: Calculate n_minus_1_yrs
	double n_minus_1_yrs = (year_diff > 0) ? (amount * pow(1 + (interest * 12 / 100), (year_diff - 1))) - amount : 0;

	// Step 3: Calculate less_3_months
	double less_3_months = 0;
	if (year_diff > 0) {
		if (mon_diff > 3) {
			less_3_months = ((amount + n_minus_1_yrs) * (1 + (interest * 12 / 100))) - amount - n_minus_1_yrs;
		} else {
			less_3_months = ((amount + n_minus_1_yrs) * (1 + (interest * (12 + mon_diff) / 100))) - amount - n_minus_1_yrs;
		}
	}

	// Step 4: Calculate days_interest_less3_months
	double days_interest_less3_months = (mon_diff < 3) ? ((less_3_months / (12 + mon_diff)) / 30) * date_diff : 0;

	// Step 5: Calculate less3_monthsAndDays
	double less3_monthsAndDays = (mon_diff < 3) ? n_minus_1_yrs + less_3_months + days_interest_less3_months + amount : 0;

	// Step 6: Calculate amountWithOnlyYearsInterest
	double amountWithOnlyYearsInterest = amount + whole_years;

	// Step 7: Calculate monthsInterest
	double monthsInterest = (mon_diff > 0) ? (amountWithOnlyYearsInterest / 100) * interest * mon_diff : 0;

	// Step 8: Calculate monthsYearsInterest
	double monthsYearsInterest = amountWithOnlyYearsInterest + monthsInterest;

	// Step 9: Calculate perDayInterest
	double perDayInterest = 0;
	if (mon_diff > 0) {
		perDayInterest = monthsInterest / (mon_diff * 30);
	} else if (monthsInterest > 0) {
		perDayInterest = monthsInterest / (30 * 12);
	} else {
		perDayInterest = ((amountWithOnlyYearsInterest * interest / 100) / 30);
	}

	// Step 10: Calculate daysInterest
	double daysInterest = perDayInterest * date_diff;

	// Step 11: Calculate totalAmountGT3
	double totalAmountGT3 = monthsYearsInterest + daysInterest;

	// Step 12: Calculate totalAmountLT3
	double totalAmountLT3 = (mon_diff < 3) ? ((year_diff == 0) ? totalAmountGT3 : less3_monthsAndDays) : totalAmountGT3;

	// Print the result
	printf("T2 = %.2f\n", totalAmountLT3);

	return 0;
}
int valid_date(int day, int mon, int year)
{
	int is_valid = 1;
	if (year >= 1800 && year <= 9999)
	{
		if(mon >= 1 && mon <= 12)
		{
			is_valid = 1;
		}
		else
		{
			is_valid = 0;
		}
	}
	else
	{
		is_valid = 0;
	}
	return is_valid;
}