package ru.itmo.wp.model.repository;

import ru.itmo.wp.model.domain.Article;

import java.util.List;

public interface ArticleRepository {
    Article find(long id);
    List<Article> findAllByHidden(boolean hidden);
    List<Article> findAllByUserId(long userId);
    void save(Article article);
    void update(Article article);

}
