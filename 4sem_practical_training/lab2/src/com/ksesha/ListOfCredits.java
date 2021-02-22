package com.ksesha;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public class ListOfCredits {
    public ListOfCredits() { }
    public ListOfCredits(ArrayList<Credit> all_credits) {
        this.all_credits = all_credits;
    }

    private ArrayList<Credit> all_credits
            = new ArrayList<> (Arrays.asList(
                                    new Credit(Banks.PRIORBANK, Purpose.MORTGAGE, 180, 80000, 15.50),
                                    new Credit(Banks.PRIORBANK, Purpose.BUSINESS, 60, 100000, 20.10),
                                    new Credit(Banks.PRIORBANK, Purpose.AUTOMOBILE, 36, 20000, 18.99),
                                    new Credit(Banks.PRIORBANK, Purpose.MICROLOAN, 3, 1000, 35.00),
                                    new Credit(Banks.PRIORBANK, Purpose.LEASING, 120, 50000, 24.99),
                                    new Credit(Banks.BPS_SBERBANK, Purpose.MORTGAGE, 150, 90000, 14.20),
                                    new Credit(Banks.BPS_SBERBANK, Purpose.BUSINESS, 72, 80000, 23.18),
                                    new Credit(Banks.BPS_SBERBANK, Purpose.AUTOMOBILE, 60, 20000, 13.33),
                                    new Credit(Banks.BPS_SBERBANK, Purpose.MICROLOAN, 1, 2000, 30.11),
                                    new Credit(Banks.BELGAZPROMBANK, Purpose.MORTGAGE, 240, 90000, 16.65),
                                    new Credit(Banks.BELGAZPROMBANK, Purpose.BUSINESS, 120, 150000, 19.99),
                                    new Credit(Banks.BELGAZPROMBANK, Purpose.AUTOMOBILE, 60, 70000, 21.15),
                                    new Credit(Banks.BELGAZPROMBANK, Purpose.MICROLOAN, 3, 1500, 30.30),
                                    new Credit(Banks.BELGAZPROMBANK, Purpose.LEASING, 120, 60000, 25.99),
                                    new Credit(Banks.BELARUSBANK, Purpose.MORTGAGE, 240, 120000, 25.55),
                                    new Credit(Banks.BELARUSBANK, Purpose.BUSINESS, 108, 120000, 21.18),
                                    new Credit(Banks.BELARUSBANK, Purpose.AUTOMOBILE, 60, 30000, 23.35),
                                    new Credit(Banks.BELARUSBANK, Purpose.LEASING, 120, 85000, 28.99)
            ));


    public Credit getCredit(Credit selected) {
        if (!all_credits.contains(selected)) throw new IllegalArgumentException("There's no such credit!");
        return all_credits.stream().findFirst().get();
    }

    public List<Credit> findCredit(Banks bank) {
        return all_credits.stream().filter((p)-> p.getBank().equals(bank)).collect(Collectors.toList());
    }

    public List<Credit> findCredit(Purpose purpose) {
        return all_credits.stream().filter((p)-> p.getPurpose().equals(purpose)).collect(Collectors.toList());
    }

    public List<Credit> findCredit(Purpose purpose, double max_percentage) {
        return all_credits.stream().filter((p)-> p.getPurpose().equals(purpose) &&
                                                 p.getPercentageRate() <= max_percentage).collect(Collectors.toList());
    }

    public List<Credit> findCredit(Purpose purpose, int min_loan) {
        return all_credits.stream().filter((p)-> p.getPurpose().equals(purpose) &&
                                                 p.getLoanCeiling() >= min_loan).collect(Collectors.toList());
    }


    @Override
    public String toString() {
        return "ListOfCredits:\n" + all_credits + '\n';
    }
}

