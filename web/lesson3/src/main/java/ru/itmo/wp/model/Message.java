package ru.itmo.wp.model;

public class Message {
    private final String user;
    private final String text;

    public Message(String user, String text) {
        this.user = user;
        this.text = text;
    }

    public String getUser() {
        return user;
    }

    public String getText() {
        return text;
    }
}