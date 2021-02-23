package com.ksesha;

public class Context {
    private Strategy strategy;

    public Context () { }

    public void setStrategy(Strategy strategy) {
        this.strategy = strategy;
    }

    public Credit executeStrategy(Credit old_credit, int term) {
        return strategy.changeCreditLine(old_credit, term);
    }
}
