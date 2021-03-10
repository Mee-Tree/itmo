package ru.itmo.wp.web.page;

import ru.itmo.wp.model.domain.Article;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.web.annotation.Json;

import javax.servlet.http.HttpServletRequest;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/** @noinspection unused*/
public class IndexPage extends Page {

    @Override
    protected void action(HttpServletRequest request, Map<String, Object> view) {
        putMessage(request, view);
    }

    @Json
    private void findAll(HttpServletRequest request, Map<String, Object> view) {
        List<Article> articles = getArticleService().findAllNonHidden();
        Map<Long, User> userById = new HashMap<>();

        for (Article article : articles) {
            long userId = article.getUserId();
            User user = getUserService().find(userId);
            userById.put(userId, user);
        }

        view.put("articles", articles);
        view.put("userById", userById);
    }
}
