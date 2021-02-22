package com.ksesha;

public class AnticipatedRepayment implements Strategy {
    @Override
    public Credit changeCreditLine(Credit old_credit, int term) {
        return new Credit(old_credit.getBank(), old_credit.getPurpose(),
                old_credit.getTerm() - term, old_credit.getLoanCeiling(), old_credit.getPercentageRate());
    }
}
