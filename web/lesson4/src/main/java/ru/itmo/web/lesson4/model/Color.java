package ru.itmo.web.lesson4.model;

public enum Color {
    RED,
    GREEN,
    BLUE;


    @Override
    public String toString() {
        return super.toString().toLowerCase();
    }
}
