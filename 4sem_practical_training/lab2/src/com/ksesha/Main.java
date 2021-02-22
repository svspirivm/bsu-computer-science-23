package com.ksesha;

public class Main {

    public static void main(String[] args) {
        ListOfCredits list = new ListOfCredits();
        System.out.println(list.toString());



        Credit credit = new Credit(Banks.PRIORBANK, Purpose.MORTGAGE, 180, 80000, 15.50);
        System.out.println("You've selected: " +list.getCredit(credit).toString());

        System.out.println("Find by bank: " + list.findCredit(Banks.PRIORBANK).toString());
        System.out.println();
        System.out.println("Find by purpose: " + list.findCredit(Purpose.AUTOMOBILE).toString());
        System.out.println();
        System.out.println("Find by purpose and percentage: " + list.findCredit(Purpose.MORTGAGE,20.0).toString());
        System.out.println();
        System.out.println("Find by purpose and min loan: " + list.findCredit(Purpose.LEASING,75000).toString());

        System.out.println();
        System.out.println("You've selected: " +list.getCredit(credit).toString());
        Context context1 = new Context(new EnlargeCreditLine());
        Credit new_credit = context1.executeStrategy(credit, 3);
        System.out.println("Credit with new term is: " + new_credit.toString());
        Context context2 = new Context(new AnticipatedRepayment());
        System.out.println("Credit with new term is: " + context2.executeStrategy(new_credit, 10).toString());
    }
}
