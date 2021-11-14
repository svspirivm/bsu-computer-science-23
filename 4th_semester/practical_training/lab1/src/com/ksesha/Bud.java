package com.ksesha;

import com.sun.javaws.exceptions.InvalidArgumentException;

import java.util.Arrays;

public class Bud {
    protected Petal[] petals;

    public Bud() { }

    public Bud(String color, int petals) {
        if (petals < 1)
            throw new IllegalArgumentException("Number of petals can't be less than 1");
        this.petals = new Petal[petals];
        for (int i = 0; i < petals; i++) {
            Petal petal = new Petal(color);
            this.petals[i] = petal;
        }
    }

    @Override
    public String toString() {
        return "Color of bud is " + petals[0].toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Bud bud = (Bud) o;
        return Arrays.equals(petals, bud.petals);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(petals);
    }
}
