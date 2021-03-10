package ru.itmo.wp.web.page;

import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.exception.ValidationException;
import ru.itmo.wp.web.annotation.Json;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

/** @noinspection unused*/
public class UsersPage extends Page {
    @Json
    private void findAll(HttpServletRequest request, Map<String, Object> view) {
        view.put("users", getUserService().findAll());
    }

    @Json
    private void findUser(HttpServletRequest request, Map<String, Object> view) {
        long userId = Long.parseLong(request.getParameter("userId"));
        view.put("user", getUserService().find(userId));
    }

    @Json
    private void changePrivileges(HttpServletRequest request, Map<String, Object> view) throws ValidationException {
        String stringId = request.getParameter("id");
        String stringAdmin = request.getParameter("admin");
        User currentUser = getUserService().find(getUser(request).getId());
        getUserService().validatePrivilegesChange(currentUser, stringId, stringAdmin);

        long id = Long.parseLong(stringId);
        boolean admin = Boolean.parseBoolean(stringAdmin);
        getUserService().changePrivileges(id, admin);
    }
}
