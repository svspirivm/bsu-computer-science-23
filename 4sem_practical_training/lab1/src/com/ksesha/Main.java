package com.ksesha;

//16 variant
//Создать объект класса Цветок, используя классы Лепесток, Бутон.
//Методы: расцвести, завять, вывести на консоль цвет бутона.

public class Main {

    public static void main(String[] args) {
	    Flower rose = new Flower("rose", "red", 5);

	    rose.printBudsColor();
        System.out.println(rose.toString());

	    rose.blossom();
	    rose.wilt();
    }
}
