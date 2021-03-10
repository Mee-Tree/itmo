package ru.itmo.wp.form;

import javax.validation.constraints.AssertTrue;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;

@SuppressWarnings("unused")
public class ToggleForm {
    @NotNull
    @NotEmpty
    private String state;

    @AssertTrue
    private boolean isValidState() {
        return "Disable".equals(state) || "Enable".equals(state);
    }

    private long id;

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }
}
