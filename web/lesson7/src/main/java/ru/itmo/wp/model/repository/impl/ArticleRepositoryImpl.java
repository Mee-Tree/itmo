package ru.itmo.wp.model.repository.impl;

import com.google.common.collect.ImmutableMap;
import ru.itmo.wp.model.domain.Article;
import ru.itmo.wp.model.repository.ArticleRepository;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.List;

public class ArticleRepositoryImpl extends BasicRepositoryImpl<Article> implements ArticleRepository {
    @Override
    public List<Article> findAllByHidden(boolean hidden) {
        return findAllBy("hidden", hidden);
    }

    @Override
    public List<Article> findAllByUserId(long userId) {
        return findAllBy("userId", userId);
    }

    @Override
    public void save(Article article) {
        save(article, ImmutableMap.of(
                "userId", article.getUserId(),
                "title", article.getTitle(),
                "text", article.getText(),
                "hidden", article.isHidden()
        ));
    }

    @Override
    public void update(Article article) {
        update(article, ImmutableMap.of(
                "title", article.getTitle(),
                "text", article.getText(),
                "hidden", article.isHidden()
        ));
    }

    @Override
    protected Article toEntity(ResultSetMetaData metaData, ResultSet resultSet) throws SQLException {
        if (!resultSet.next()) {
            return null;
        }

        Article article = new Article();
        for (int i = 1; i <= metaData.getColumnCount(); i++) {
            switch (metaData.getColumnName(i)) {
                case "id":
                    article.setId(resultSet.getLong(i));
                    break;
                case "userId":
                    article.setUserId(resultSet.getLong(i));
                    break;
                case "title":
                    article.setTitle(resultSet.getString(i));
                    break;
                case "text":
                    article.setText(resultSet.getString(i));
                    break;
                case "hidden":
                    article.setHidden(resultSet.getBoolean(i));
                    break;
                case "creationTime":
                    article.setCreationTime(resultSet.getTimestamp(i));
                    break;
                default:
                    // No operations.
            }
        }

        return article;
    }
}
