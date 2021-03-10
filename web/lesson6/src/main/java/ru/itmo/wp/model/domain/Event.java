package ru.itmo.wp.model.domain;

import java.io.Serializable;
import java.util.Date;

public class Event extends Entity implements Serializable {
    private long userId;
    private Type type;

    public long getUserId() {
        return userId;
    }

    public void setUserId(long userId) {
        this.userId = userId;
    }

    public Type getType() {
        return type;
    }

    public void setType(Type type) {
        this.type = type;
    }

    public enum Type {
        ENTER,
        LOGOUT
    }
}