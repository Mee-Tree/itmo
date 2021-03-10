package ru.itmo.wp.web.page;

import com.google.common.base.Strings;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.service.ArticleService;
import ru.itmo.wp.model.service.UserService;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

@SuppressWarnings("unused")
public abstract class Page {
    private final UserService userService = new UserService();
    private final ArticleService articleService = new ArticleService();

    protected void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }

    private void checkAdmin(HttpServletRequest request, Map<String, Object> view) {
        User user = getUser(request);
        view.put("admin", user != null && userService.isAdmin(user.getId()));
    }

    public UserService getUserService() {
        return userService;
    }

    public ArticleService getArticleService() {
        return articleService;
    }

    protected void setMessage(HttpServletRequest request, String message) {
        request.getSession().setAttribute("message", message);
    }

    protected String getMessage(HttpServletRequest request) {
        return (String) request.getSession().getAttribute("message");
    }

    protected void removeMessage(HttpServletRequest request) {
        request.getSession().removeAttribute("message");
    }

    protected void setUser(HttpServletRequest request, User user) {
        request.getSession().setAttribute("user", user);
    }

    protected User getUser(HttpServletRequest request) {
        return (User) request.getSession().getAttribute("user");
    }

    protected void removeUser(HttpServletRequest request) {
        request.getSession().removeAttribute("user");
    }

    protected void putMessage(HttpServletRequest request, Map<String, Object> view) {
        String message = getMessage(request);
        if (!Strings.isNullOrEmpty(message)) {
            view.put("message", message);
            removeMessage(request);
        }
    }
}
