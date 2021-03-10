package ru.itmo.wp.web.page;

import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.exception.ValidationException;
import ru.itmo.wp.web.annotation.Json;
import ru.itmo.wp.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

/** @noinspection unused*/
public class ArticlePage extends Page {

    protected void action(HttpServletRequest request, Map<String, Object> view) {
        if (getUser(request) == null) {
            setMessage(request, "You have to be authorised to write an article");
            throw new RedirectException("/index");
        }
    }

    @Json
    private void addArticle(HttpServletRequest request, Map<String, Object> view) throws ValidationException {
        User user = getUser(request);
        String title = request.getParameter("title");
        String text = request.getParameter("text");
        boolean hidden = Boolean.parseBoolean(request.getParameter("hidden"));

        getArticleService().validateCreation(title, text);
        getArticleService().addArticle(user, title, text, hidden);

        throw new RedirectException("/article");
    }
}
