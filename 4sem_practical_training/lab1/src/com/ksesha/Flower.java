package com.ksesha;

public class Flower extends Bud {
    private String name;

    public Flower(String name, String color, int petals) {
        super(color, petals);
        this.name = name;
    }

    public void blossom() {
        System.out.println("Wow! " + this.toString() + " is blossoming!");
    }

    public void wilt() {
        System.out.println("Oh, no! " + this.toString() + " has wilted :( ");
    }

    public void printBudsColor() {
        System.out.println(super.toString());
    }

    @Override
    public String toString() {
        return "Flower name is " + name +
                ", amount of petals is " + petals.length;
    }
}
