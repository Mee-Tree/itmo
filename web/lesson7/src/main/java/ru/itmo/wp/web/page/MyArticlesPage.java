package ru.itmo.wp.web.page;

import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.exception.ValidationException;
import ru.itmo.wp.web.annotation.Json;
import ru.itmo.wp.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

/** @noinspection unused*/
public class MyArticlesPage extends Page {
    @Override
    protected void action(HttpServletRequest request, Map<String, Object> view) {
        User user = getUser(request);
        if (user == null) {
            setMessage(request,"You have to be authorised to view your articles");
            throw new RedirectException("/index");
        }
        view.put("myArticles", getArticleService().findAllByUserId(user.getId()));
    }

    @Json
    private void changeVisibility(HttpServletRequest request, Map<String, Object> view) throws ValidationException {
        String stringId = request.getParameter("id");
        String stringHidden = request.getParameter("hidden");
        getArticleService().validateVisibilityChange(getUser(request), stringId, stringHidden);

        long id = Long.parseLong(stringId);
        boolean hidden = Boolean.parseBoolean(stringHidden);
        getArticleService().changeVisibility(id, hidden);
    }
}