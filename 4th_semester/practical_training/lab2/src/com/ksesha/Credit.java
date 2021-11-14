package com.ksesha;

import java.util.Objects;

public class Credit {
    private Banks bank;
    private Purpose purpose;
    private int term;
    private int loan_ceiling;
    private double percentage_rate;

    public Credit(Banks bank, Purpose purpose, int term, int max_sum, double percentage_rate) {
        if (percentage_rate < 0.0)
            throw new IllegalArgumentException("Percentage rate can't be less than 0");
        else if (max_sum < 0)
            throw new IllegalArgumentException("Maximum loan sum can't be less than 0");
        this.bank = bank;
        this.purpose = purpose;
        this.term = term;
        this.loan_ceiling = max_sum;
        this.percentage_rate = percentage_rate;
    }

    @Override
    public String toString() {
        return "\nBank: " + bank.toString() + ", purpose: " + purpose.toString() +
               ", term: " + term + " months, " + "loan ceiling: " + loan_ceiling + " $, " +
               "percentage_rate: " + percentage_rate + "%";
    }

    public Banks getBank() {
        return bank;
    }

    public Purpose getPurpose() {
        return purpose;
    }

    public int getTerm() {
        return term;
    }

    public int getLoanCeiling() {
        return loan_ceiling;
    }

    public double getPercentageRate() {
        return percentage_rate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Credit)) return false;
        Credit credit = (Credit) o;
        return  getTerm() == credit.getTerm() &&
                loan_ceiling == credit.loan_ceiling &&
                Double.compare(credit.percentage_rate, percentage_rate) == 0 &&
                getBank() == credit.getBank() &&
                getPurpose() == credit.getPurpose();
    }

    @Override
    public int hashCode() {
        return Objects.hash(getBank(), getPurpose(), getTerm(), loan_ceiling, percentage_rate);
    }
}
