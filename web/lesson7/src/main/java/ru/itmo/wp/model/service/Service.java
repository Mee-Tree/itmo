package ru.itmo.wp.model.service;

@SuppressWarnings("BooleanMethodIsAlwaysInverted")
public abstract class Service {

    protected static boolean isLong(String stringLong) {
        try {
            Long.parseLong(stringLong);
            return true;
        } catch (NumberFormatException ignored) {
            return false;
        }
    }

    protected static boolean isBoolean(String stringBool) {
        return "true".equalsIgnoreCase(stringBool) || "false".equalsIgnoreCase(stringBool);
    }
}
