package ru.itmo.wp.model.service;

import com.google.common.base.Strings;
import ru.itmo.wp.model.domain.Article;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.exception.ValidationException;
import ru.itmo.wp.model.repository.ArticleRepository;
import ru.itmo.wp.model.repository.impl.ArticleRepositoryImpl;

import java.util.List;

public class ArticleService extends Service {
    private final ArticleRepository articleRepository = new ArticleRepositoryImpl();

    public void validateCreation(String title, String text) throws ValidationException {
        if (Strings.isNullOrEmpty(title)) {
            throw new ValidationException("Title is required");
        }
        if (title.length() > 255) {
            throw new ValidationException("Title can't be longer that 255 characters");
        }

        if (Strings.isNullOrEmpty(text)) {
            throw new ValidationException("Text is required");
        }
        if (text.length() > 2000) {
            throw new ValidationException("Text can't be longer that 2000 characters");
        }
    }

    public void validateVisibilityChange(User user, String stringId, String stringHidden) throws ValidationException {
        if (Strings.isNullOrEmpty(stringId)) {
            throw new ValidationException("Article id is required");
        }
        if (!isLong(stringId)) {
            throw new ValidationException("Article id must be a number");
        }

        if (Strings.isNullOrEmpty(stringHidden)) {
            throw new ValidationException("Parameter 'hidden' is required");
        }
        if (!isBoolean(stringHidden)) {
            throw new ValidationException("Hidden must be a boolean");
        }

        Article article = find(Long.parseLong(stringId));
        if (article == null) {
            throw new ValidationException("There's no such post");
        }
        if (user.getId() != article.getUserId()) {
            throw new ValidationException("You have no rights to change this post");
        }
    }

    public Article find(long id) {
        return articleRepository.find(id);
    }

    public void addArticle(User user, String title, String text, boolean hidden) {
        Article article = new Article();
        article.setUserId(user.getId());
        article.setTitle(title);
        article.setText(text);
        article.setHidden(hidden);
        articleRepository.save(article);
    }

    public List<Article> findAllByUserId(long userId) {
        return articleRepository.findAllByUserId(userId);
    }

    public List<Article> findAllNonHidden() {
        return articleRepository.findAllByHidden(false);
    }

    public void changeVisibility(long id, boolean hidden) {
        Article article = find(id);
        article.setHidden(hidden);
        articleRepository.update(article);
    }
}
